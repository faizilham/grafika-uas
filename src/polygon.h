#ifndef POLYGON_H
#define POLYGON_H

#include "boolean.h"
#include "point.h"

typedef struct Poly{
	Point corner[30];
	Point center, min, max; // center for pivot, min-max for boundary check
	int color, fill,neff;
	int z;
} Poly;


void polygon_setMinMax(Poly* p);
Poly polygon_create(Point* corner, int length);

void polygon_translate(Poly* p, int dx, int dy);
void polygon_rotate(Poly* p, float deg);
void polygon_scale(Poly* p, float scale);
bool polygon_checkCollision(Poly* p, float x, float y);

void polygon_draw(Poly* p); // drawnya masih langsung digambar aja, blom ada clip/anticlip

#endif