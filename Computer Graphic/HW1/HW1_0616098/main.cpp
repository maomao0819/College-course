#define _USE_MATH_DEFINES
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Object.h"
#include "glut.h"
#include <math.h>
using namespace std;

bool is_base_rotate = false;
bool is_pikachu_rotate = false;
bool is_pikachu_revolve = false;

class Vertex {
	public:
		float x;
		float y;
		float z;
		void normalize() {
			float magnitude;
			magnitude = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
			*this = *this / magnitude;
		}
		Vertex operator + (Vertex const& obj) {
			Vertex temp;
			temp.x = this->x + obj.x;
			temp.y = this->y + obj.y;
			temp.z = this->z + obj.z;
			return temp;
		}
		Vertex operator - (Vertex const& obj) {
			Vertex temp;
			temp.x = this->x - obj.x;
			temp.y = this->y - obj.y;
			temp.z = this->z - obj.z;
			return temp;
		}
		Vertex operator / (float const& num) {
			Vertex temp;
			temp.x = this->x / num;
			temp.y = this->y / num;
			temp.z = this->z / num;
			return temp;
		}
		friend ostream& operator<<(ostream& os, const Vertex& v) {
			os << v.x << "," << v.y << "," << v.z;
			return os;
		}
};

int windowSize[2];
unsigned int texture;
int width, height, nrChannels;
unsigned char* pikachuTexture;
Object* Clock = new Object("clock.obj");
Object* Pikachu = new Object("Pikachu.obj");

void light();
void display();
void idle();
void reshape(GLsizei, GLsizei);
void InitTexture();
void LoadModel(Object*, bool is_Pikachu = false);
void keyboard(unsigned char key, int x, int y);
void DrawBase();

// default light color, can be use to reset the material color
GLfloat default_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f};
GLfloat default_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f};


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("HW1");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	InitTexture();
	glutMainLoop();
	return 0;
}

void light()
{
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat light_position[] = { 10.0, 10.0, 5.0, 0.0 };
	glShadeModel(GL_SMOOTH);
	// z buffer enable
	glEnable(GL_DEPTH_TEST);
	// enable lighting
	glEnable(GL_LIGHTING);
	// set light property
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, light_specular);
	GLfloat mat_shininess[] = { 100 };
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// viewport transformation
	glViewport(0, 0, windowSize[0], windowSize[1]);

	// projection transformation
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)windowSize[0] / (GLfloat)windowSize[1], 1.0, 1000.0);
	// viewing and modeling transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 15.0, 40.0,// eye
		0.0, 0.0, 0.0,     // center
		0.0, 1.0, 0.0);    // up

	light();

	////TO DO : add model, translate, rotate, scale ,material
	
	// rotate parameter
	static float base_rotate = 0.0f;
	static float pikachu_rotate = 0.0f;
	static float pikachu_revolve = 0.0f;

	// Clock
	glPushMatrix();
	glTranslatef(0.0f, 7.5f, 0.0f);
	glRotatef(base_rotate, 0.0f, 1.0f, 0.0f);
	// clock model
	glPushMatrix();
	glScalef(0.08f, 0.08f, 0.08f);
	LoadModel(Clock, false);
	glPopMatrix();
	// time
	static float minute = 15.0f * 6;
	static float hour = 0.0f;
	// hour hand
	glPushMatrix();
	GLUquadricObj* hour_hand_quadratic;
	hour_hand_quadratic = gluNewQuadric();
	GLfloat hour_hand_diffuse[] = { 0, 1, 1, 1 };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, hour_hand_diffuse);
	glRotatef(-(hour), 0.0f, 0.0f, 1.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(hour_hand_quadratic, 0.3, 0.3, 3.0, 30, 30);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, default_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, default_ambient);
	glPopMatrix();
	// minute hand
	glPushMatrix();
	GLUquadricObj* minute_hand_quadratic;
	minute_hand_quadratic = gluNewQuadric();
	GLfloat minute_hand_diffuse[] = { 1, 0, 1, 1 };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, minute_hand_diffuse);
	glRotatef(-(minute), 0.0f, 0.0f, 1.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(minute_hand_quadratic, 0.3, 0.3, 5.0, 30, 30);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, default_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, default_ambient);
	glPopMatrix();
	glPopMatrix();

	// Pikachu
	glPushMatrix();
	glRotatef(pikachu_revolve, 0.0f, 1.0f, 0.0f);
	glTranslatef(14.0f, 0.0f, 0.0f);
	glRotatef(45.0f + pikachu_rotate, 0.0f, 1.0f, 0.0f);
	glScalef(10.0f, 10.0f, 10.0f);
	LoadModel(Pikachu, true);
	glPopMatrix();
	
	// Base
	glPushMatrix();
	glRotatef(base_rotate, 0.0f, 1.0f, 0.0f);
	DrawBase();
	glPopMatrix();

	// update parameter
	hour += 1.0 / 12;
	minute++;
	if (is_base_rotate)
		base_rotate++;
	if (is_pikachu_rotate)
		pikachu_rotate++;
	if (is_pikachu_revolve)
		pikachu_revolve += 2;

	glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h)
{
	windowSize[0] = w;
	windowSize[1] = h;
}

void idle() {
	glutPostRedisplay();
}

void InitTexture() {
	stbi_set_flip_vertically_on_load(true);
	pikachuTexture = stbi_load("Pikachu.png", &width, &height, &nrChannels, 0);
	glEnable(GL_TEXTURE_2D);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pikachuTexture);

	glDisable(GL_TEXTURE_2D);
}

void LoadModel(Object* Model,bool is_Pikachu) {
	if (is_Pikachu) {
		GLfloat pikachu_diffuse[] = { 1, 1, 0, 1 };
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, pikachu_diffuse);
		glEnable(GL_TEXTURE_2D);
	}
	for (size_t i = 0; i < Model->fNum; ++i)
	{
		glBegin(GL_TRIANGLES);
		for (size_t j = 0; j < 3; ++j)
		{
			if (is_Pikachu) {
				int idx = i * 3 * 2 + j * 2;
				glTexCoord2f(Model->texcoords[idx],Model->texcoords[idx+1]);
			}
			glNormal3fv(Model->nList[Model->faceList[i][j].nIndex].ptr);
			glVertex3fv(Model->vList[Model->faceList[i][j].vIndex].ptr);
		}
		glEnd();
	}
	if (is_Pikachu) {
		// set amibent back to default
		glMaterialfv(GL_FRONT, GL_AMBIENT, default_ambient);
		glDisable(GL_TEXTURE_2D);
	}
}

void keyboard(unsigned char key, int x, int y) {
	//// TO DO : implement the keyboard function
	//
	switch (key)
	{
		case 'r':
		case 'R':
			is_base_rotate = !is_base_rotate;
			break;
		case 'p':
		case 'P':
			is_pikachu_rotate = !is_pikachu_rotate;
			break;
		case 'm':
		case 'M':
			is_pikachu_revolve = !is_pikachu_revolve;
			break;
	}
}

void DrawBase() {
	//// TO DO : Draw base 
	//
	
	//// TO DO : draw the star polygon
	//

	// Draw the triangle with color #f72585
	GLfloat red_diffuse[] = { 247.0f / 255.0f , 37.0f / 255.0f , 133.0f / 255.0f , 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, red_diffuse);
	// draw the triangle
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-10.0f, 0.0f, 0.0f);
	glVertex3f(-5.0f, 0.0f, 10.0f);
	glVertex3f(-15.0f, 0.0f, 10.0f);
	
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-5.0f, 0.0f, 10.0f);
	glVertex3f(5.0f, 0.0f, 10.0f);
	glVertex3f(0.0f, 0.0f, 20.0f);
	
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(5.0f, 0.0f, 10.0f);
	glVertex3f(10.0f, 0.0f, 0.0f);
	glVertex3f(15.0f, 0.0f, 10.0f);
	
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(10.0f, 0.0f, 0.0f);
	glVertex3f(5.0f, 0.0f, -10.0f);
	glVertex3f(15.0f, 0.0f, -10.0f);
	
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(5.0f, 0.0f, -10.0f);
	glVertex3f(-5.0f, 0.0f, -10.0f);
	glVertex3f(0.0f, 0.0f, -20.0f);
	
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-5.0f, 0.0f, -10.0f);
	glVertex3f(-10.0f, 0.0f, 0.0f);
	glVertex3f(-15.0f, 0.0f, -10.0f);
	glEnd();

	/*glBegin(GL_TRIANGLES);
	glNormal3f(0.0f, 1.0f, 0.0f);
	float r = 10.0f;
	for (int i = 0; i < 6; i++)
	{
		float angle_1 = 60 * i * M_PI / 180;
		float angle_2 = 60 * (i + 1) * M_PI / 180;
		glVertex3f(r * cos(angle_1), 0.0f, r * sin(angle_1));
		glVertex3f(r * cos(angle_2), 0.0f, r * sin(angle_2));
		glVertex3f(r * cos(angle_1) + r * cos(angle_2), 0.0f, r * sin(angle_1) + 10.0 * sin(angle_2));
	}
	glEnd();*/

	glMaterialfv(GL_FRONT, GL_DIFFUSE, default_diffuse);
	
	// Draw the hexagon with color #4cc9f0
	GLfloat blue_diffuse[] = { 114.0f / 255.0f , 201.0f / 255.0f , 240.0f / 255.0f , 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, blue_diffuse);
	// draw the star polygon
	
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-10.0f, 0.0f, 0.0f);
	glVertex3f(-5.0f, 0.0f, 10.0f);
	glVertex3f(5.0f, 0.0f, 10.0f);
	glVertex3f(10.0f, 0.0f, 0.0f);
	glVertex3f(5.0f, 0.0f, -10.0f);
	glVertex3f(-5.0f, 0.0f, -10.0f);
	glEnd();

	/*glBegin(GL_POLYGON);
	glNormal3f(0.0f, 1.0f, 0.0f);
	float r = 10.0f;
	for (int i = 0; i < 6; i++)
	{
		float angle = 60 * i * M_PI / 180;
		glVertex3f(r * cos(angle), 0.0f, r * sin(angle));
	}
	glEnd();*/

	glMaterialfv(GL_FRONT, GL_DIFFUSE, default_diffuse);

	//// TO DO : draw the rectangle edge
	//
	// Draw the rectangle with color #f72585
	glMaterialfv(GL_FRONT, GL_DIFFUSE, red_diffuse);
	glBegin(GL_QUADS);
	glNormal3f(-0.66f, 0.0f, -0.33f);
	glVertex3f(-10.0f, 0.0f, 0.0f);
	glVertex3f(-15.0f, 0.0f, 10.0f);
	glVertex3f(-15.0f, -5.0f, 10.0f);
	glVertex3f(-10.0f, -5.0f, 0.0f);
	
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-5.0f, 0.0f, 10.0f);
	glVertex3f(-15.0f, 0.0f, 10.0f);
	glVertex3f(-15.0f, -5.0f, 10.0f);
	glVertex3f(-5.0f, -5.0f, 10.0);

	glNormal3f(-0.66f, 0.0f, 0.33f);
	glVertex3f(-5.0f, 0.0f, 10.0f);
	glVertex3f(0.0f, 0.0f, 20.0f);
	glVertex3f(0.0f, -5.0f, 20.0f);
	glVertex3f(-5.0f, -5.0f, 10.0f);

	glNormal3f(0.66f, 0.0f, 0.33f);
	glVertex3f(5.0f, 0.0f, 10.0f);
	glVertex3f(0.0f, 0.0f, 20.0f);
	glVertex3f(0.0f, -5.0f, 20.0f);
	glVertex3f(5.0f, -5.0f, 10.0f);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(5.0f, 0.0f, 10.0f);
	glVertex3f(15.0f, 0.0f, 10.0f);
	glVertex3f(15.0f, -5.0f, 10.0f);
	glVertex3f(5.0f, -5.0f, 10.0f);

	glNormal3f(0.66f, 0.0f, -0.33f);
	glVertex3f(10.0f, 0.0f, 0.0f);
	glVertex3f(15.0f, 0.0f, 10.0f);
	glVertex3f(15.0f, -5.0f, 10.0f);
	glVertex3f(10.0f, -5.0f, 0.0f);

	glNormal3f(0.66f, 0.0f, 0.33f);
	glVertex3f(10.0f, 0.0f, 0.0f);
	glVertex3f(15.0f, 0.0f, -10.0f);
	glVertex3f(15.0f, -5.0f, -10.0f);
	glVertex3f(10.0f, -5.0f, 0.0f);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(5.0f, 0.0f, -10.0f);
	glVertex3f(15.0f, 0.0f, -10.0f);
	glVertex3f(15.0f, -5.0f, -10.0f);
	glVertex3f(5.0f, -5.0f, -10.0f);

	glNormal3f(0.66f, 0.0f, -0.33f);
	glVertex3f(5.0f, 0.0f, -10.0f);
	glVertex3f(0.0f, 0.0f, -20.0f);
	glVertex3f(0.0f, -5.0f, -20.0f);
	glVertex3f(5.0f, -5.0f, -10.0f);

	glNormal3f(-0.66f, 0.0f, -0.33f);
	glVertex3f(-5.0f, 0.0f, -10.0f);
	glVertex3f(0.0f, 0.0f, -20.0f);
	glVertex3f(0.0f, -5.0f, -20.0f);
	glVertex3f(-5.0f, -5.0f, -10.0f);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-5.0f, 0.0f, -10.0f);
	glVertex3f(-15.0f, 0.0f, -10.0f);
	glVertex3f(-15.0f, -5.0f, -10.0f);
	glVertex3f(-5.0f, -5.0f, -10.0f);

	glNormal3f(-0.66f, 0.0f, 0.33f);
	glVertex3f(-10.0f, 0.0f, 0.0f);
	glVertex3f(-15.0f, 0.0f, -10.0f);
	glVertex3f(-15.0f, -5.0f, -10.0f);
	glVertex3f(-10.0f, -5.0f, 0.0f);
	glEnd();

	/*glBegin(GL_QUADS);
	float r = 10.0f;
	for (int i = 0; i < 6; i++)
	{
		float angle_n_1 = (30 + i * 60) * M_PI / 180;
		float angle_1 = 60 * i * M_PI / 180;
		float angle_2 = 60 * (i + 1) * M_PI / 180;
		glNormal3f(cos(angle_n_1), 0.0f, -sin(angle_n_1));
		glVertex3f(r * cos(angle_1), 0.0f, r * sin(angle_1));
		glVertex3f(r * cos(angle_1) + r * cos(angle_2), 0.0f, r * sin(angle_1) + r * sin(angle_2));
		glVertex3f(r * cos(angle_1) + r * cos(angle_2), -5.0f, r * sin(angle_1) + r * sin(angle_2));
		glVertex3f(r * cos(angle_1), -5.0f, r * sin(angle_1));
		float angle_n_2 = (-90 + i * 60) * M_PI / 180;
		glNormal3f(cos(angle_n_2), 0.0f, -sin(angle_n_2));
		glVertex3f(r * cos(angle_2), 0.0f, r * sin(angle_2));
		glVertex3f(r * cos(angle_1) + r * cos(angle_2), 0.0f, r * sin(angle_1) + r * sin(angle_2));
		glVertex3f(r * cos(angle_1) + r * cos(angle_2), -5.0f, r * sin(angle_1) + r * sin(angle_2));
		glVertex3f(r * cos(angle_2), -5.0f, r * sin(angle_2));
	}
	glEnd();*/
	glMaterialfv(GL_FRONT, GL_DIFFUSE, default_diffuse);
}