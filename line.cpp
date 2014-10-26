#include "line.h"
Line::Line(Point *a, Point *b)
{
	this->a = a;
	this->b = b;
}

void Line::draw()
{
	static int count = 0;

	glEnable (GL_LINE_SMOOTH);
	glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
	glLineWidth (1);


	int ac, bc, cc;
	switch(count)
	{
		case 0: ac = 1; bc = 0; cc = 0;break;
		case 1: ac = 0; bc = 1; cc = 0;break;
		case 2: ac = 0; bc = 0; cc = 1;break;
	}
	glBegin(GL_LINES);
			glColor4f(ac, bc, cc, 1);
			glVertex2f(a->x, a->y);
			glVertex2f(b->x, b->y);
		glEnd();

//	glBegin(GL_LINES);
//		ONE_COLOR;
//		glVertex2f(a->x, a->y);
//		SECOND_COLOR
//		glVertex2f(b->x, b->y);
//	glEnd();
	glFlush();
	count++;
	if(count == 3) count = 0;
}



