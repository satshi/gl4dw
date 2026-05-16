#include "dirutil.h"

#include <string.h>

std::string Directory(const char* FileName)
{
	const char* slash = strrchr(FileName, '\\');
	if(!slash) return std::string();

	return std::string(FileName, slash - FileName);
}

std::string filename(const char* FileName)
{
	const char* slash = strrchr(FileName, '\\');
	const char* start = slash ? slash + 1 : FileName;
	const char* dot = strrchr(start, '.');

	if(!dot) return std::string(start);
	return std::string(start, dot - start);
}
