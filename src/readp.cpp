#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vector3.h"
#include "string.h"

char* cfg_file=(char*)"gl4d.cfg";
char* delimita=(char*)" ,=\n";
#define MAXLINE 256

extern int Width;
extern double ExtendRate;
extern double clip_plane[];
extern int Clip;
extern int hidePoly;
extern int FillType;
extern char data_dir[];
extern char *window_name;
extern char *name;

void read_param()
{
	FILE* fp;
	char line[MAXLINE];
	fp=fopen(cfg_file, "r");
	if (!fp) return;
	while(NULL!=fgets(line, MAXLINE, fp))
	{
		char* keyword=strtok(line, delimita);
		if(!keyword || keyword[0]=='#') continue;
		if(!strcmp(keyword,"hidePoly") )
		{
			char* value=strtok(NULL, delimita);
			if(value) hidePoly=atoi(value);
		}
		else if(!strcmp(keyword,"Width"))
		{
			char* value=strtok(NULL, delimita);
			if(value) Width=atoi(value);
		}
		else if(!strcmp(keyword,"ExtendRate") )
		{
			char* value=strtok(NULL, delimita);
			if(value) ExtendRate=atof(value);
		}
		else if(!strcmp(keyword,"ClipPlane") )
		{
			for(int i=0;i<4;i++)
			{
				char* value=strtok(NULL, delimita);
				if(value) clip_plane[i]=atof(value);
			}
		}
		else if(!strcmp(keyword,"Clip") )
		{
			char* value=strtok(NULL, delimita);
			if(value) Clip=atoi(value);
		}
		else if(!strcmp(keyword,"FillType") )
		{
			char* value=strtok(NULL, delimita);
			if(value) FillType=atoi(value);
		}
		else if(!strcmp(keyword,"DataDir") )
		{
			char* value=strtok(NULL, delimita);
			if(value) strcpy(data_dir, value);
		}

	}
	fclose(fp);
}void read_comandline(int argc, char** argv)
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