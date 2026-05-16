#include "gl4d.h"
#include <gl/glut.h>
#include <fstream.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

polytope poly;

Ary<Vector3> vertices3;
projector proj;
Vector3 viewp(0.0, 0.0, 3.5);
char data_dir[1024]="data";
int hidePoly=0;
double ExtendRate=0.06;
static int open_data_file(ifstream& is, char* fname, const char* pattern, const char* name)
{
	if(is.is_open()) is.close();
	sprintf(fname, pattern, data_dir, name);
	is.open(fname, ios::in);
	if(!is && !strcmp(data_dir, "data"))
	{
		is.clear();
		sprintf(fname, pattern, "..\\data", name);
		is.open(fname, ios::in);
	}
	return !!is;
}

int ReadPolytope(char* pname)
{
	char fname[1024];
	char ccfname[1024];
	
	// 頂点の読み込み
	ifstream is;
	if(!open_data_file(is, fname, "%s\\%s.poi", pname))
	{
		cerr<<"Cannot open file"<<fname<<endl;
		return 0;
	}
	poly.read_vertices(is);
	is>>ccfname;
	// 面の読み込み
	if(!open_data_file(is, fname, "%s\\f%s.cel", pname))
	{
		cerr<<"Cannot open file"<<fname<<endl;
		return 0;
	}
	poly.read_faces(is);
	// 胞の中心の読み込み。
	if(!open_data_file(is, fname, "%s\\%s", ccfname))
	{
		cerr<<"Cannot open file"<<fname<<endl;
		return 0;
	}
	poly.read_Facet_nomals(is);
	// スケールの調整
	double l=1.0/(*poly.vertices)[0].norm();
	for(int i=0;i<poly.vertices->n;i++)
	{
		(*poly.vertices)[i]*=l;
	}
	vertices3.renew(poly.vertices->n);
	// データの作成
	poly.make__Facets();
	poly.make__Facets_to_faces();
	// 胞の中心の調整
	for(int i=0;i<poly.Facets->n;i++)
	{
		Vector4& cv=(*poly.Facet_nomals)[i];
		cv*=1.0/cv.norm();
	}
	
	return 1;
}

GLfloat mat_diffuse[11][3]={{1.0, 0.6, 1.0}, {0.87, 0.87, 0.3}, {0.3, 1.0, 1.0}
			,{1.0, 0.6, 0.4}, {0.5, 1.0, 0.5}, {0.7, 0.7, 1.0}
			,{1.0, 0.8, 0.4}, {0.4, 0.8, 1.0}, {0.85, 0.6, 1.0}
			,{1.0, 0.4, 0.8}, {0.4, 1.0, 0.8}};


void drawPolytopeSolid(void)
{
	register int i,j,k, prevn=0;
	points& vertices=*poly.vertices;
	cells& faces=*poly.faces;
	cells& ff=*poly.Facets_to_faces;
	
	for(i=0;i<vertices.n;i++)
		vertices3[i]=proj.projection(vertices[i]);
	
	for(k=0;k<ff.n;k++)
	if( dot(proj[3],(*poly.Facet_nomals)[k])>0
//	if( (*poly.Facet_nomals)[k][3]>=0.3		
		&& ff[k].n !=hidePoly)
	{
		if(ff[k].n!=prevn)
		{
			prevn=ff[k].n;
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_diffuse[prevn%11]);
		}
		Vector3 ext=proj.projection((*poly.Facet_nomals)[k])*ExtendRate;
		for (i = 0; i < ff[k].n; i++)
		{
			cell& cface=faces[ff[k][i]];
			Vector3& v0=vertices3[cface[0]];
			Vector3 v1=vertices3[cface[1]]-vertices3[cface[0]];
			Vector3 v2=vertices3[cface[2]]-vertices3[cface[0]];
			Vector3 nomal=cross(v1,v2);
			if(dot(nomal, (viewp-v0))>0)
			{
				nomal*=1.0/norm(nomal);
			}
			else
			{
				nomal*=-1.0/norm(nomal);
			}
			glNormal3dv(nomal.x);
			glBegin(GL_TRIANGLE_FAN);
				for(j=0;j<cface.n;j++)
				{
					register Vector3 v=vertices3[cface[j]]+ext;
					glVertex3dv(v.x);
				}
			glEnd();
		}
	}
}

void drawPolytopeFrame(void)
{
	register int i,j,k, prevn=0;
	points& vertices=*poly.vertices;
	cells& faces=*poly.faces;
	cells& ff=*poly.Facets_to_faces;
	
	for(i=0;i<vertices.n;i++)
		vertices3[i]=proj.projection(vertices[i]);
	
	for(k=0;k<ff.n;k++)
	if( dot((*poly.Facet_nomals)[k], proj[3])>0
		&& ff[k].n !=hidePoly)
	{
		if(ff[k].n!=prevn)
		{
			prevn=ff[k].n;
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_diffuse[prevn%11]);
		}
		Vector3 ext=proj.projection((*poly.Facet_nomals)[k])*ExtendRate;
		for (i = 0; i < ff[k].n; i++)
		{
			cell& cface=faces[ff[k][i]];
			Vector3& v0=vertices3[cface[0]];
			Vector3 v1=vertices3[cface[1]]-vertices3[cface[0]];
			Vector3 v2=vertices3[cface[2]]-vertices3[cface[0]];
			Vector3 nomal=cross(v1,v2);
			Vector3 center(0,0,0);
			for(j=0;j<cface.n;j++)
			{
				center+=vertices3[cface[j]];
			}
			center*=1.0/cface.n;
			center+=ext;
			if(dot(nomal, (viewp-v0))>0)
			{
				nomal*=1.0/norm(nomal);
			}
			else
			{
				nomal*=-1.0/norm(nomal);
			}
			glNormal3dv(nomal.x);
			glBegin(GL_TRIANGLE_STRIP);
				for(j=0;j<cface.n;j++)
				{
					Vector3 v=vertices3[cface[j]]+ext;
					register Vector3 vv=0.35*center+0.65*v;
					glVertex3dv(v.x);
					glVertex3dv(vv.x);
				}
				Vector3 v=vertices3[cface[0]]+ext;
				register Vector3  vv=0.35*center+0.65*v;
				glVertex3dv(v.x);
				glVertex3dv(vv.x);
			glEnd();
		}
	}
}

