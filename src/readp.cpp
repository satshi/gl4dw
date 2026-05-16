#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>
#include "vector3.h"

char* cfg_file=(char*)"gl4d.json";

extern int Width;
extern double ExtendRate;
extern double clip_plane[];
extern int Clip;
extern int hidePoly;
extern int FillType;
extern char data_dir[];
extern char *window_name;
extern char *name;

static bool has_key(const nlohmann::json& config, const char* key)
{
	return config.find(key) != config.end();
}

static void read_bool_or_int(const nlohmann::json& config, const char* key, int& value)
{
	if(!has_key(config, key)) return;
	const nlohmann::json& item = config.at(key);
	if(item.is_boolean())
	{
		value = item.get<bool>() ? 1 : 0;
	}
	else
	{
		value = item.get<int>();
	}
}

static void read_string_to_buffer(const nlohmann::json& config, const char* key, char* dest, size_t dest_size)
{
	if(!has_key(config, key) || dest_size == 0) return;
	std::string value = config.at(key).get<std::string>();
	strncpy(dest, value.c_str(), dest_size - 1);
	dest[dest_size - 1] = '\0';
}

void read_param()
{
	std::ifstream is(cfg_file);
	if(!is) return;

	try
	{
		nlohmann::json config;
		is >> config;

		if(has_key(config, "hidePoly")) hidePoly = config.at("hidePoly").get<int>();
		if(has_key(config, "width")) Width = config.at("width").get<int>();
		if(has_key(config, "extendRate")) ExtendRate = config.at("extendRate").get<double>();
		read_bool_or_int(config, "clip", Clip);
		if(has_key(config, "fillType")) FillType = config.at("fillType").get<int>();
		read_string_to_buffer(config, "dataDir", data_dir, 1024);

		if(has_key(config, "clipPlane"))
		{
			const nlohmann::json& plane = config.at("clipPlane");
			if(!plane.is_array() || plane.size() != 4)
			{
				throw std::runtime_error("clipPlane must be an array of four numbers");
			}
			for(int i=0;i<4;i++)
			{
				clip_plane[i] = plane.at(i).get<double>();
			}
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << "Cannot read config file " << cfg_file << ": " << e.what() << std::endl;
	}
}

void read_comandline(int argc, char** argv)
{
	int i;
	for(i=1;i<argc;i++)
	{
		if (argv[i][0]=='-')
		{
			switch(argv[i][1])
			{
			  case 'h':
				FillType=1;
			    break;
			  case 's':
				FillType=0;
			    break;
			  case 'c':
				Clip=1;
			    break;
			  case  'n':
				i++;
				window_name=argv[i];
			    break;
			  default:
			    break;
			}
		}
		else
		{
			name=argv[i];
		}
	}
}
