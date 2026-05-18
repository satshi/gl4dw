#include "gl4d.h"
#include "gl_compat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Ary<Vector3> vertices3;
projector proj;
Vector3 viewp(0.0, 0.0, 3.5);
int hidePoly=0;
double ExtendRate=0.06;

GLfloat mat_diffuse[11][3]={{1.0f, 0.6f, 1.0f}, {0.87f, 0.87f, 0.3f}, {0.3f, 1.0f, 1.0f}
			,{1.0f, 0.6f, 0.4f}, {0.5f, 1.0f, 0.5f}, {0.7f, 0.7f, 1.0f}
			,{1.0f, 0.8f, 0.4f}, {0.4f, 0.8f, 1.0f}, {0.85f, 0.6f, 1.0f}
			,{1.0f, 0.4f, 0.8f}, {0.4f, 1.0f, 0.8f}};


void drawPolytopeSolid(void)
{
	int i,j,k, prevn=0;
	points& vertices=*poly.vertices;
	cells& faces=*poly.faces;
	cells& ff=*poly.Facets_to_faces;
	if(vertices3.n != vertices.n) vertices3.renew(vertices.n);
	
	for(i=0;i<vertices.n;i++)
		vertices3[i]=proj.projection(vertices[i]);
	
	for(k=0;k<ff.n;k++)
	if( dot(proj[3],(*poly.Facet_normals)[k])>0
		&& ff[k].n !=hidePoly)
	{
		if(ff[k].n!=prevn)
		{
			prevn=ff[k].n;
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_diffuse[prevn%11]);
		}
		Vector3 ext=proj.projection((*poly.Facet_normals)[k])*ExtendRate;
		for (i = 0; i < ff[k].n; i++)
		{
			cell& cface=faces[ff[k][i]];
			Vector3& v0=vertices3[cface[0]];
			Vector3 v1=vertices3[cface[1]]-vertices3[cface[0]];
			Vector3 v2=vertices3[cface[2]]-vertices3[cface[0]];
			Vector3 normal=cross(v1,v2);
			if(dot(normal, (viewp-v0))>0)
			{
				normal*=1.0/norm(normal);
			}
			else
			{
				normal*=-1.0/norm(normal);
			}
			glNormal3dv(normal.x);
			glBegin(GL_TRIANGLE_FAN);
				for(j=0;j<cface.n;j++)
				{
					Vector3 v=vertices3[cface[j]]+ext;
					glVertex3dv(v.x);
				}
			glEnd();
		}
	}
}

void drawPolytopeFrame(void)
{
	int i,j,k, prevn=0;
	points& vertices=*poly.vertices;
	cells& faces=*poly.faces;
	cells& ff=*poly.Facets_to_faces;
	if(vertices3.n != vertices.n) vertices3.renew(vertices.n);
	
	for(i=0;i<vertices.n;i++)
		vertices3[i]=proj.projection(vertices[i]);
	
	for(k=0;k<ff.n;k++)
	if( dot((*poly.Facet_normals)[k], proj[3])>0
		&& ff[k].n !=hidePoly)
	{
		if(ff[k].n!=prevn)
		{
			prevn=ff[k].n;
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_diffuse[prevn%11]);
		}
		Vector3 ext=proj.projection((*poly.Facet_normals)[k])*ExtendRate;
		for (i = 0; i < ff[k].n; i++)
		{
			cell& cface=faces[ff[k][i]];
			Vector3& v0=vertices3[cface[0]];
			Vector3 v1=vertices3[cface[1]]-vertices3[cface[0]];
			Vector3 v2=vertices3[cface[2]]-vertices3[cface[0]];
			Vector3 normal=cross(v1,v2);
			Vector3 center(0,0,0);
			for(j=0;j<cface.n;j++)
			{
				center+=vertices3[cface[j]];
			}
			center*=1.0/cface.n;
			center+=ext;
			if(dot(normal, (viewp-v0))>0)
			{
				normal*=1.0/norm(normal);
			}
			else
			{
				normal*=-1.0/norm(normal);
			}
			glNormal3dv(normal.x);
			glBegin(GL_TRIANGLE_STRIP);
				for(j=0;j<cface.n;j++)
				{
					Vector3 v=vertices3[cface[j]]+ext;
					Vector3 vv=0.35*center+0.65*v;
					glVertex3dv(v.x);
					glVertex3dv(vv.x);
				}
				Vector3 v=vertices3[cface[0]]+ext;
				Vector3  vv=0.35*center+0.65*v;
				glVertex3dv(v.x);
				glVertex3dv(vv.x);
			glEnd();
		}
	}
}
