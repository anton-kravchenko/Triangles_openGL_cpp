#ifndef POINT_H
#define POINT_H
#include <GL/glut.h>

extern const int WIDTH;
extern const int HEIGHT;

class Point
{
public:
	Point();
	Point(float x, float y);
	
	void draw();
	void draw_red();
	float x, y;
};

#endif
