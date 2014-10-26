#ifndef LINE_H
#define LINE_H
#include <GL/glut.h>
#include "point.h" 	


#define ONE_COLOR		glColor4f(0, 1, 0.7, 1);
#define SECOND_COLOR	glColor4f(0, 0.5, 1, 1);

class Line
{
public:
	Line(Point *a, Point *b);
	Point *a;
	Point *b;

	void draw();

};
#endif
