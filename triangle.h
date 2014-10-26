#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <GL/glut.h>
#include <unistd.h>
#include "line.h"
#include "math.h"

class Triangle
{
private:
public:
	void init_edges();
	void draw_doodle();
	static Line* rotate_vector(Line*, float);
	static Point* rotate_point(Point*, float);
	static Point* find_intersection_point(Line*, Line*, Point*);
	static float to_radians(float);

//public:
	
	Triangle();
	Triangle(Point*);
	Triangle(Line*, Line*, Line*);

	Line* edges[3];
	Point* center;

	static int RIGHT_EDGE;
	static int BOTTOM_EDGE;
	static int LEFT_EDGE;
	static double PI;

	static float ROTATE_ANGLE;
	static float EGDE_LENGTH;

	void draw();
};

#endif
