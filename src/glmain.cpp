
#include <stdio.h>
#include <GL/glut.h>
#include <windows.h>
#include "gl4d.h"
#include "glevent.h"
#include "readp.h"
const char copyright[]=
   "gl4dw  Ver 0.1 \n"
   "Copyright (c) 2001 Satoshi Yamaguchi\n";

GLfloat light_ambient[] = {0.05, 0.05, 0.05, 0.05};	 /* ambient light. */
GLfloat light_specular[] = {0.6, 0.6, 0.6, 1.0};  /* specular light. */
GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};	 /*diffuse light. */
GLfloat light_position[] = {-4.0, 4.0, 4.0, 0.0};  /* Inite light location. */
GLfloat mat_specular[3]={0.6, 0.6, 0.6};  // specular material
GLfloat fog_color[4]={0.6, 0.6, 0.6};	// fog color
GLdouble clip_plane[4]={1,-1,-1,0};		// extra clip plane
int Clip=0;	 // exstra clip or not
int Width=640;
int Height=480;
char *window_name=(char*)"gl4dw";
char *name=(char*)"c8";
static void log_step(const char* message)
{
	FILE* fp = fopen("gl4dw.log", "a");
	if(fp)
	{
		fprintf(fp, "%s\n", message);
		fclose(fp);
	}
}

void init(void)
{
	/* Enable a single OpenGL light. */
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	/* Use depth buffering for hidden surface elimination. */
	glEnable(GL_DEPTH_TEST);

	/* Setup the view of the cube. */
	glMatrixMode(GL_PROJECTION);
	gluPerspective( /* field of view in degree */ 40.0,
	/* aspect ratio */ (double)Width/(double)Height,
	/* Z near */ 1.0, /* Z far */ 10.0);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(viewp[0], viewp[1], viewp[2],	 /* eye is at (0,0,3.5) */
	 0.0, 0.0, 0.0,		 /* center is at (0,0,0) */
	0.0, 1.0, 0.);		/* up is in positive Y direction */

	// Material
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS , 30.0);
	// Background color
	glClearColor(0.6, 0.6, 0.6, 0.6);
	// Fog
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_START, 2.0);
	glFogf(GL_FOG_END, 4.5);
	glFogfv(GL_FOG_COLOR, fog_color);
	glEnable(GL_FOG);

	//切断
	glClipPlane(GL_CLIP_PLANE0, clip_plane);
	if(Clip)glEnable(GL_CLIP_PLANE0);
}

int main(int argc, char** argv)
{
	log_step("main: start");
	read_param();  //パラメータの読み込み。
	log_step("main: read_param done");
	// コマンドラインの読み込み
	read_comandline(argc, argv);
	log_step("main: read_commandline done");
	ReadPolytope(name);
	log_step("main: ReadPolytope done");
	//OpenGLの初期化
	glutInit(&argc, argv);
	log_step("main: glutInit done");
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(Width, Height);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	//glutGameModeString("640x480:16@60");
	//glutEnterGameMode();
	int window_id = glutCreateWindow(window_name);
	char logbuf[128];
	sprintf(logbuf, "main: glutCreateWindow id=%d", window_id);
	log_step(logbuf);
	glutShowWindow();
	glutPostRedisplay();
	// イベント処理関数
	glutDisplayFunc(ev_display);
	glutReshapeFunc(ev_resize);
	glutMouseFunc(ev_mouse);
	glutMotionFunc(ev_move);
	glutIdleFunc(ev_idle);
	glutKeyboardFunc(ev_key);
	//シーンの初期化
	init();
	log_step("main: init done");
	// メインループ
	log_step("main: entering glutMainLoop");
	glutMainLoop();
	return 0;
}
