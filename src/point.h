#ifndef POINT_H
#define POINT_H

#include "libgraph.h"

typedef struct{
	float x, y;
} Point;

Point point_create(float x, float y);

void point_set(Point* p, float x, float y);

void point_translate(Point* p, float dx, float dy);
void point_rotate(Point* p, float deg);
void point_rotateTo(Point* p, float deg, Point center);
void point_scale(Point* p, float sx, float sy);
void point_scaleTo(Point* p, float sx, float sy, Point center);

void point_linedraw(Point p1, Point p2, int color);

#endif