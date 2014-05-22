#ifndef CURVE_H
#define CURVE_H

#include "point.h"

typedef struct{
	Point points[4];
	Point center, min, max;
	int color;
	int z;
} Curve;

Curve curve_create(Point* points);

void curve_setPoint(Curve* c, int index, int x, int y);

void curve_translate(Curve* c, int dx, int dy);
void curve_rotate(Curve* c, float deg);
void curve_scale(Curve* c, float scale);
bool curve_checkCollision(Curve* c, float x, float y);

void curve_draw(Curve* c);

#endif