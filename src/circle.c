#include "circle.h"
#include "helper.h"
#include "libgraph.h"

Circ ci[100];
int nci;

void circ_setMinMax(Circ* c){
	c->min = c->center;
	c->max = c->center;
	
	c->min.x = c->min.x - c->radius;
	c->max.x = c->max.x + c->radius;
	c->min.y = c->min.y - c->radius;
	c->max.y = c->max.y + c->radius;
}

Circ circ_create(int _x, int _y, float r){
	Circ c;
	
	c.center.x = _x;
	c.center.y = _y;
	c.radius = r;
	
	circ_setMinMax(&c);
	
	c.fill = BLACK;
	c.color = WHITE;
	
	return c;
}

void circ_translate(Circ* c, int dx, int dy){	
	point_translate(&c->center, dx, dy);
}

void circ_scale(Circ* c, float scale){
	c->radius = (c->radius * scale);
	circ_setMinMax(c);
}

bool circ_checkCollision(Circ* c, float x, float y){
	bool inside = ((x-c->center.x)*(x-c->center.x) + (y-c->center.y)*(y-c->center.y) < (c->radius)*(c->radius));
	/*
	float x1 = c->min.x; float y1 = c->min.y;
	float x2 = c->max.x; float y2 = c->max.y;
	*/
	return inside;//in_rectangle(x,y,x1,y1,x2,y2);
}

void circ_draw(Circ* c){
	fill_ellipse(c->center.x, c->center.y, c->radius, c->radius, c->fill);
	draw_ellipse(c->center.x, c->center.y, c->radius, c->radius, c->color);
	//fill_polygon (c->min.x, c->min.y, c->max.x, c->max.y, c->fill, c->color);
}