#ifndef RECT_H
#define RECT_H

#include "boolean.h"
#include "point.h"

typedef struct{
	Point corner[4];
	Point center, min, max; // center for pivot, min-max for boundary check
	int color, fill;
	int z;
} Rect;

Rect rect_create(int x1, int y1, int x2, int y2);

void rect_translate(Rect* r, int dx, int dy);
void rect_rotate(Rect* r, float deg);
void rect_scale(Rect* r, float scale);
bool rect_checkCollision(Rect* r, float x, float y);

void rect_draw(Rect* r); // drawnya masih langsung digambar aja, blom ada clip/anticlip

#endif