#include <cstdio>
#include <cstring>

int Width = 640;
double ExtendRate = 0.06;
double clip_plane[] = {1.0, -1.0, -1.0, 0.0};
int Clip = 0;
int hidePoly = 0;
int FillType = 0;
char data_dir[1024] = "data";
char* window_name = (char*)"gl4dw";
char* name = (char*)"c8";

extern void read_param();

int main()
{
    FILE* fp = fopen("gl4d.json", "w");
    if(!fp) return 1;
    fputs("{\"dataDir\":\"data\",\"width\":800,\"extendRate\":0.12,\"clip\":true,"
          "\"clipPlane\":[1.0,2.0,3.0,4.0],\"hidePoly\":5,\"fillType\":1}", fp);
    fclose(fp);

    read_param();
    remove("gl4d.json");

    if(strcmp(data_dir, "data") != 0) return 2;
    if(Width != 800) return 3;
    if(ExtendRate != 0.12) return 4;
    if(Clip != 1) return 5;
    if(hidePoly != 5) return 6;
    if(FillType != 1) return 7;
    if(clip_plane[0] != 1.0 || clip_plane[1] != 2.0 || clip_plane[2] != 3.0 || clip_plane[3] != 4.0) return 8;
    return 0;
}
