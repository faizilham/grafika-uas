#ifndef LINE_H
#define LINE_H

#include "boolean.h"
#include "point.h"

typedef struct{
	Point p1, p2;
	Point center, min, max;
	int color;
	int z;
} Line;

Line line_create(int x1, int y1, int x2, int y2);

void line_translate(Line* l, int dx, int dy);
void line_rotate(Line* l, float deg);
void line_scale(Line* l, float scale);
bool line_checkCollision(Line* l, float x, float y);

void line_draw(Line* l);

#endif