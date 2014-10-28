#include "triangle.h"

int 	Triangle::RIGHT_EDGE 	= 0;
int 	Triangle::BOTTOM_EDGE 	= 1;
int 	Triangle::LEFT_EDGE		= 2;
float 	Triangle::ROTATE_ANGLE 	= 30;
float 	Triangle::EGDE_LENGTH 	= -0.3;//very bad
float 	Triangle::EDGE_MULT     = 1.15;
double	Triangle::PI 			=3.141592653589793238463;


Triangle::Triangle(){}

Triangle::Triangle(Point *center)
{
	this->center = center;
	init_edges();
}

Triangle::Triangle(Line* top, Line* right, Line* left)
{
	edges[RIGHT_EDGE]	= right;
	edges[BOTTOM_EDGE] 	= top;
	edges[LEFT_EDGE]	= left;	
}

float Triangle::to_radians(float angle)
{
	return angle * PI / 180;
}

Point* Triangle::find_intersection_point(Line *first, Line *second, Point *x)
{
	float n = ( (second->b->y - second->a->y) *
				(first->b->x  - first->a->x) -
				(second->b->x - second->a->x) *
				(first->b->y  - first->a->y) );

	float m = ( (second->b->x - second->a->x) *
				(first->a->y  - second->a->y) -
				(second->b->y - second->a->y) *
				(first->a->x  - second->a->x) );

	float Ua = m / n;
	float inters_x = first->a->x + Ua * (first->b->x - first->a->x);
	float inters_y = first->a->y + Ua * (first->b->y- first->a->y);

	x->x = inters_x;
	x->y = inters_y;

	return x;
}

void Triangle::init_edges()
{
	Point *bounds[3];

	for(int i = 0, next = 1, angle = 0; i < 3; i++, angle += 120, next++) //must be 120 degree to get right triangle
	{
		Point *v = new Point();
		rotate_point(v, center, angle);
		bounds[i] = v;
	}

	for(int cur = 0, next = 1; cur < 3; cur++, next++)
	{
		if(next > 2) next = 0;
		edges[cur] = new Line(	new Point(center->x + bounds[cur]->x, center->y  + bounds[cur]->y),
								new Point(center->x + bounds[next]->x, center->y + bounds[next]->y));
	}

	draw();
	draw_doodle();
}

Point* Triangle::rotate_point(Point* p, Point* anchor, float angle)
{
	float vx = 0; //can be changed to rotate entire rectangle
	float vy = Triangle::EGDE_LENGTH;
	//p->x can be mult by -1 to change pivot point of rotate
	p->x = -(vx*cos(to_radians(angle)) - vy*sin(to_radians(angle)));
	p->y =  vx*sin(to_radians(angle)) + vy*cos(to_radians(angle));
	p->x += anchor->x;
	p->y += anchor->y;
//	p->draw();
	return p;
}

Line* Triangle::rotate_vector(Line* vector, Point* center,float angle)
{
	static Point *anchor = new Point();

	anchor->x = vector->a->x;
	anchor->y = vector->a->y;

	vector->b->x -= anchor->x;//0
	vector->b->y -= anchor->y;//0
	vector->a->x -= anchor->x;
	vector->a->y -= anchor->y;

	float vx = vector->b->x;
	float vy = vector->b->y;

	vector->b->x = (vx*cos(to_radians(angle)) - vy*sin(to_radians(angle)));
	vector->b->y =   (vx*sin(to_radians(angle)) + vy*cos(to_radians(angle)));

//need if rotate around center
//	vx = vector->a->x;
//	vy = vector->a->y;
//	vector->a->x = (vx*cos(to_radians(angle)) - vy*sin(to_radians(angle)));
//	vector->a->y =   (vx*sin(to_radians(angle)) + vy*cos(to_radians(angle)));

	vector->b->x += anchor->x;
	vector->b->y += anchor->y;

	vector->a->x += anchor->x;
	vector->a->y += anchor->y;
	return vector;
}

void Triangle::draw_doodle()
{
	float rotate_angle = -1;
	for(int a = 0; a < 100; a++, rotate_angle-= 0.005)
	{
		for(int i = 0; i < 3; i++)
		{

			//[0] init vector from current
			//[1] rotate to some angle
			//[2] find intersection point of V and next line
			//[3] init second point of current with inters point values

			int cur = i;
			int next = i+1;
			if( 3 == next) next = 0;

	//[0]
			Line *vector = edges[cur];

	//[1]
			// can be negative with vx value in rotate point line:81
			rotate_vector(vector, this->center, rotate_angle);

	//[2]
			Point *inters_point = new Point();
			find_intersection_point(edges[cur], edges[next], inters_point);

	//[3]
			edges[next]->a = inters_point;

			//try to find problem with this pointer
			edges[cur]->b->x = inters_point->x;
			edges[cur]->b->y = inters_point->y;

			edges[cur]->draw();

//		sleep(2);
		usleep(10000);
		}
	}
}

void Triangle::draw()
{
	edges[RIGHT_EDGE]->draw();
	edges[BOTTOM_EDGE]->draw();
	edges[LEFT_EDGE]->draw();	
}
