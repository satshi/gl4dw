#include <gl/glut.h>
#include <time.h>
#include "gl4d.h"

#define FILL_TYPE_SOLID 0
#define FILL_TYPE_FRAME 1

int FillType=FILL_TYPE_SOLID;

void ev_display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(FillType==FILL_TYPE_FRAME)
		drawPolytopeFrame();
	else
		drawPolytopeSolid();
	glutSwapBuffers();
}

static int mouse_state=GLUT_UP;
static int pushed_button=GLUT_RIGHT_BUTTON;
static int xx, yy;
static double theta[6]={0, 0, 0, 0, 0, 0};
static double phi[6]={0, 0, 0, 0, 0, 0};

void ev_mouse(int button, int state, int x, int y)
{
	mouse_state=state;
	pushed_button=button;
	if(state==GLUT_DOWN)
	{
		if(button==GLUT_LEFT_BUTTON)
			for(int i=0;i<6;i++)
				theta[i]=0.0;
		else
			for(int i=0;i<6;i++)
				phi[i]=0.0;
		xx=x;
		yy=y;
	}
}

static projector projt;
void ev_move(int x, int y)
{
	if(mouse_state==GLUT_DOWN)
	{
		if(pushed_button==GLUT_LEFT_BUTTON)
		{
			for(int i=0;i<6;i++)
				theta[i]=0;
			theta[1]=-(x-xx)*0.005;
			theta[2]=(y-yy)*0.005;
			projt.rotation(theta);
		}
		else
		{
			for(int i=0;i<6;i++)
				phi[i]=0;
			phi[3]=-(x-xx)*0.005;
			phi[4]=(y-yy)*0.005;
			projt.rotation(phi);
		}
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				proj[i][j]=projt[j][i];
		ev_display();
		xx=x;
		yy=y;
	}
}

void ev_key(unsigned char key, int x, int y)
{
	switch(key)
	{
	  case 'q':
	  case 'Q':
	  case '\033':
		exit(0);
		break;
	  default:
		break;
	}
}

void ev_resize(int w, int h)
{
	if(h <= 0) h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( /* field of view in degree */ 40.0,
			/* aspect ratio */ (double)w/(double)h,
		/* Z near */ 1.0, /* Z far */ 10.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(viewp[0], viewp[1], viewp[2],	 /* eye is at (0,0,3.5) */
	 0.0, 0.0, 0.0,		 /* center is at (0,0,0) */
	0.0, 1.0, 0.);		/* up is in positive Y direction */
	glutPostRedisplay();
}

void ev_idle()
{
	int mv=0;
	for(int i=0;i<6;i++)
	{
		mv=mv || (theta[i]!=0.0) || (phi[i]!=0.0);
	}
	if(mv && (mouse_state==GLUT_UP))
	{
		projt.rotation(theta);
		projt.rotation(phi);
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				proj[i][j]=projt[j][i];
		ev_display();
	}
}
