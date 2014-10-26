#include <GL/glut.h>
#include <iostream>

using namespace std;

class Point;
class Line;
#include "triangle.h"

void to_float_range(Point *p);
void render(void);
void key_handler(unsigned char button, int x, int y);
void mouse_handler(int button, int state, int x, int y);
void resize(int width, int height);

const int WIDTH  = 1000;
const int HEIGHT = 1000;

int count = 0;

#define KEY_ESCAPE 	27
#define KEY_TAB		9

int main(int argc,char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("GL_TRIANGLES");

	glutDisplayFunc(render);
	glutKeyboardFunc(key_handler);
	//glutReshapeFunc(resize);
	glutMouseFunc(mouse_handler);

	glutMainLoop();


	// add multi thread drawing, and drawing triangles from it's minified copies
	// modify vector's methods to work witk anchor poitnts
}

//void resize(int width, int height) {
//    // we ignore the params and do:
//    glutReshapeWindow( WIDTH, HEIGHT);
//}

void to_float_range(Point *p)
{
	cout << p->x << " " << p->y << "\n";
	p->x = (p->x - WIDTH/2) / (WIDTH/2);
	p->y = -(p->y - HEIGHT/2)/ (HEIGHT/2);
	cout << p->x << " " << p->y << "\n";
}

void render()
{
	glClearColor(0.1, 0.1, 0.1, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glFlush();
	static bool init = true;// true to draw triangle
	if (true == init)
	{
		Triangle *t =  new Triangle(new Point(0, 0));
		init = false;
	}
}

void key_handler(unsigned char button, int x, int y)
{
	cout << "KEY "<< (int)button << "\n";

	if(KEY_ESCAPE == button)
	{
		exit(0);
	}
	if(KEY_TAB == button)
	{
		count = 0;
		glClearColor(0.1, 0.1, 0.1, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glFlush();
	}
}
void mouse_handler(int button, int state, int x, int y)
{
	static Point *p;
	static Line  *l1 = new Line(new Point(), new Point());
	static Line  *l2 = new Line(new Point(), new Point());

	if(GLUT_DOWN == state && GLUT_LEFT_BUTTON == button)
	{
		p = new Point(x, y);
		to_float_range(p);
		p->draw();
		if( 4 == count) count = 0;

		switch(count)
		{
			case 0: l1->a = p; break;
			case 1: l1->b = p; l1->draw(); break;
			case 2: l2->a = p; break;
			case 3: l2->b = p; l2->draw(); Triangle::find_intersection_point(l1, l2, p); break;
		}
		count++;
	}

}
