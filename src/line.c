#include "line.h"
#include "helper.h"

Line l[100];
int nl;
extern int current_max_c;

void line_setMinMax(Line* l){	
	l->min.x = min(l->p1.x, l->p2.x);
	l->max.x = max(l->p1.x, l->p2.x);
	l->min.y = min(l->p1.y, l->p2.y);
	l->max.y = max(l->p1.y, l->p2.y);
}

Line line_create(int x1, int y1, int x2, int y2){
	Line l;
	
	l.p1.x = x1; l.p1.y = y1;
	l.p2.x = x2; l.p2.y = y2;
	
	l.center.x = ((float) (x1 + x2)) / 2.f;
	l.center.y = ((float) (y1 + y2)) / 2.f;
	
	line_setMinMax(&l);
	
	l.color = WHITE;
	l.z = current_max_c;
	current_max_c++;
	return l;
}

void line_translate(Line* l, int dx, int dy){
	point_translate(&l->p1, dx, dy);
	point_translate(&l->p2, dx, dy);
	point_translate(&l->center, dx, dy);
	
	line_setMinMax(l);
}

void line_rotate(Line* l, float deg){
	point_rotateTo(&l->p1, deg, l->center);
	point_rotateTo(&l->p2, deg, l->center);
	
	line_setMinMax(l);
}

void line_scale(Line* l, float scale){
	point_scaleTo(&l->p1, scale, scale, l->center);
	point_scaleTo(&l->p2, scale, scale, l->center);
	
	line_setMinMax(l);
}

bool line_checkCollision(Line* l, float x, float y){	
	return in_rectangle(x,y,l->min.x,l->min.y,l->max.x,l->max.y);
}

void line_draw(Line* l){
	point_linedraw(l->p1, l->p2, l->color);
}