#include "point.h"

Point::Point()
{
	this->x = 0;
	this->y = 0;
}

Point::Point(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Point::draw()
{
	glPointSize(5);
	glBegin(GL_POINTS);
		glColor4f(1, 1, 1, 1);
		glVertex2f(x, y);
	glEnd( );
	glFlush();
}
void Point::draw_red()
{
	glPointSize(5);
	glBegin(GL_POINTS);
		glColor4f(0, 1, 1, 1);
		glVertex2f(x, y);
	glEnd( );
	glFlush();
}
