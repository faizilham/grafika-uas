#ifndef SHAPE_H
#define SHAPE_H

#include "boolean.h"
#include "circle.h"
#include "rect.h"
#include "polygon.h"
#include "line.h"
#include "curve.h"

#define TYPE_CIRCLE 1
#define TYPE_RECT 2
#define TYPE_POLYGON 3
#define TYPE_LINE 4
#define TYPE_CURVE 5

typedef struct{
	int type; //kode tipe shape
	int priority; //prioritas penggambaran - berpengaruh pada overlaying
	
	void *object;
}Shape;

Shape shape_create();

void shape_translate(Shape* s, int dx, int dy);
void shape_rotate(Shape* s, float deg);
void shape_scale(Shape* s, float scale);
bool shape_checkCollision(Shape* s, float x, float y);

void shape_draw(Shape* s); // drawnya masih langsung digambar aja, blom ada clip/anticlip


#endif