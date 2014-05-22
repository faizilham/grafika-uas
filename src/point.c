#include "point.h"
#include <math.h>

#define PI 3.14159265358979323846

Point point_create(float x, float y){
	Point p; p.x = x; p.y = y;
	return p;
}

void point_set(Point* p, float x, float y){
	p->x = x;
	p->y = y;
}

void point_translate(Point* p, float dx, float dy){
	p->x += dx;
	p->y += dy;
}

void point_rotate(Point* p, float deg){
	float rad = deg * PI / 180.f;
	float cosr = cos(rad); float sinr = sin(rad);
	float x = p->x; float y = p->y;
	
	p->x = x * cosr - y * sinr;
	p->y = x * sinr + y * cosr;
}

void point_rotateTo(Point* p, float deg, Point center){
	point_translate(p, -center.x, -center.y);
	point_rotate(p, deg);
	point_translate(p, center.x, center.y);
}

void point_scale(Point* p, float sx, float sy){
	p->x *= sx;
	p->y *= sy;
}

void point_scaleTo(Point* p, float sx, float sy, Point center){
	point_translate(p, -center.x, -center.y);
	point_scale(p, sx, sy);
	point_translate(p, center.x, center.y);
}

void point_linedraw(Point p1, Point p2, int color){
	draw_line(p1.x, p1.y, p2.x, p2.y, color);
}

Point point_add(Point p1, Point p2){
	Point p;
	p.x = p1.x + p2.x;
	p.y = p1.y + p2.y;
	
	return p;
}

Point point_mul(Point p1, float factor){
	Point p;
	p.x = p1.x * factor;
	p.y = p1.y * factor;
	
	return p;
}