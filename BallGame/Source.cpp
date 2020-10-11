#include<windows.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;

GLfloat light_ambient[] = { 0.10f, 0.10f, 0.0f, 1.0f },
light_diffuse[] = { 3.0f, 2.0f, 2.0f, 1.0f },
light_specular[] = { 10.0f, 10.0f, 5.0f, 5.0f },
light_position[] = { 10.0f, 10.0f, 10.0f, 0.0f },

mat_ambient[] = { 0.7f, 0.7f, 0.7f, .7f },
mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f },
mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f },
high_shininess[] = { 100.0f };

////////////floating ///////////////

float artio;
float zoom = 4;
float traX = 0, traY = -1.8, traZ = -8;
float traZ1 = -20, traZ2 = -40, traZ3 = -60, traZ4 = -80;
float speed = 0;
float ptx[7] = { -1.8,1.8,1,1.8,-1,-1.8,0 };


/////////////////boolean///////////////////////
bool v = true;


//////////////////////function///////////////////////////////

/////////////reshape current window////////////////////////////////
void reshape(int w, int h)
{
	if (h == 0) h = 1;
	artio = (float)w / (float)h;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50, artio, 1, 1000.0);
	glMatrixMode(GL_MODELVIEW);

}

/////////////////draw the ground////////////
void Ground()
{
	if (traX >= 5.1)traX = 5.1;
	if (traX <= -5.1)traX = -5.1;

	glColor3d(0.1, 0.2, 0.2);
	glPushMatrix();
	glTranslated(0, 0, 0);
	glScaled(20, 0, 4000);
	glutSolidCube(1);
	glPopMatrix();

}
///////////////draw cube///////////////////
void cube(int n, float z) {

	glColor3d(0.2, 0.4, 0);
	glPushMatrix();
	glTranslated(ptx[n], 0, z);
	glScaled(1.2, 1.2, 1.2);
	glutSolidCube(1);
	glPopMatrix();

}



///////////////////draw ball///////////////////////
void ball()
{

	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(traX, traY, 0.0);
	glScalef(1.3, 1.3, 1.3);
	glutSolidSphere(0.4, 20, 20);
	glPopMatrix();
}


void draw()
{


	//////////////////////ball////////////////////////
	glPushMatrix();
	glTranslated(0, 1, 0);
	glScaled(0.4, 0.4, 0.4);
	ball();
	glPopMatrix();

	//////////////////////////////////////
	//////////////v///////////////////
	if ((traX > 2.5 && traX < 5) && (traZ >= 10.847 && traZ < 11))
	{
		v = false;


	}


	///////////v1//////////////
	if ((traX <= -2.5 && traX >= -5.1) && (traZ >= -1.5077 && traZ < 0.185584))
	{
		v = false;

	}


	/////////v2///////
	if ((traX >= 1 && traX <= 3.5) && (traZ >= -100.01&& traZ<-99.1))
	{
		v = false;


	}

	///////v3/////////
	if ((traX >= 3 && traX <= 5.1) && (traZ >= -79 && traZ<78))

		v = false;




	///////v4///////
	if ((traX <= -1 && traX >= -5) && (traZ >= -59 && traZ < -58))

		v = false;



	glPushMatrix();
	cube(0, traZ);
	glPopMatrix();

	glPushMatrix();
	cube(1, traZ1);
	glPopMatrix();

	glPushMatrix();
	cube(2, traZ2);
	glPopMatrix();

	glPushMatrix();
	cube(3, traZ3);
	glPopMatrix();

	glPushMatrix();
	cube(4, traZ4);
	glPopMatrix();


	traZ += speed;
	traZ1 += speed;
	traZ2 += speed;
	traZ3 += speed;
	traZ4 += speed;


	if (traZ >= 20)traZ = -110;
	if (traZ1 >= 20)traZ1 = -110;
	if (traZ2 >= 20)traZ2 = -110;
	if (traZ3 >= 20)traZ3 = -110;
	if (traZ4 >= 20)traZ4 = -110;




	if (v == 0)
	{
		speed = 0;

	}
	else
		speed += 0.00001;




	if (speed >= 0.2)speed = 0.2;


}


static void display(void)
{


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	/////////////////////camera/////////////////
	gluLookAt(0.0, 4.5, 12.0,
		0, 4, 0,
		0, 1.0f, 0.0f);

	//////Ground///////
	Ground();


	glPushMatrix();
	glTranslated(0, 0, 0);
	glScaled(zoom, zoom, zoom);
	draw();
	glPopMatrix();



	glutSwapBuffers();
}


static void keyboard(unsigned char key, int x, int y)
{

	float frac = 0.5;
	switch (key)
	{
	case 27:
	case 'q':
		exit(0);
		break;
	case 'z':
		zoom += 0.05;
		break;
	case 'x':
		zoom -= 0.05;

	case 'a':
		traX -= frac;

		break;
	case 'd':
		traX += frac;
		break;
	case 'f':
		v = true;
		traX = 0;


	}

	glutPostRedisplay();
}


static void idle(void)
{
	glutPostRedisplay();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1366, 720);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);

	glutCreateWindow("Ball Game");

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);



	glClearColor(0, 0.5, 0.9, 1);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);



	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

	glutMainLoop();

	return EXIT_SUCCESS;
}