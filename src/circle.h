#ifndef CIRCLE_H
#define CIRCLE_H

#include "boolean.h"
#include "point.h"

typedef struct{
	float radius;
	Point center, min, max; // center for pivot, min-max for boundary check
	int color, fill;
} Circ;

Circ circ_create(int _x, int _y, float r);

void circ_translate(Circ* c, int dx, int dy);
void circ_scale(Circ* r, float scale);
bool circ_checkCollision(Circ* r, float x, float y);

void circ_draw(Circ* r); // drawnya masih langsung digambar aja, blom ada clip/anticlip

#endif