#include "curve.h"
#include "helper.h"

#define BEZIER_DELTA 0.02

// recursive bezier
Point get_bezier(Point* p, int start, int n, float t){
	if (n == 0){
		return p[start];
	}else{
		return point_add(point_mul(get_bezier(p, start, n-1, t), 1-t), point_mul(get_bezier(p, start+1,n-1,t), t));
	}
}

void curve_setCenterMinMax(Curve* c){
	float x = c->points[0].x;
	float y = c->points[0].y;
	
	c->min = c->points[0];
	c->max = c->points[0];
	
	for (int i = 1; i < 4; i++){
		x += c->points[i].x;
		y += c->points[i].y;
		
		c->min.x = min(c->min.x, c->points[i].x);
		c->min.y = min(c->min.y, c->points[i].y);
		
		c->max.x = max(c->max.x, c->points[i].x);
		c->max.y = max(c->max.y, c->points[i].y);
	}
	
	x = x / 4; y = y / 4;
	
	point_set(&c->center, x, y);
}

Curve curve_create(Point* points){
	Curve c;
	for (int i = 0; i < 4; i++){
		c.points[i].x = points[i].x;
		c.points[i].y = points[i].y;
	}
	c.color = 15; // default white
	curve_setCenterMinMax(&c);
	
	return c;
}

void curve_setPoint(Curve* c, int index, int x, int y){
	point_set(&c->points[index], x, y);
	curve_setCenterMinMax(c);
}

void curve_translate(Curve* c, int dx, int dy){
	for (int i = 0; i < 4; i++){
		point_translate(&c->points[i], dx, dy);
	}
	curve_setCenterMinMax(c);
}

void curve_rotate(Curve* c, float deg){
	for (int i = 0; i < 4; i++){
		point_rotateTo(&c->points[i], deg, c->center);
	}
	curve_setCenterMinMax(c);
}

void curve_scale(Curve* c, float scale){
	for (int i = 0; i < 4; i++){
		point_scaleTo(&c->points[i], scale, scale, c->center);
	}
	curve_setCenterMinMax(c);
}

bool curve_checkCollision(Curve* c, float x, float y){
	float x1 = c->min.x; float y1 = c->min.y;
	float x2 = c->max.x; float y2 = c->max.y;

	return in_rectangle(x,y,x1,y1,x2,y2);
}

void curve_draw(Curve* c){
	float t, dt; Point p1, p2;
	dt = BEZIER_DELTA; t = dt;
	
	p1 = get_bezier(c->points, 0, 3, 0);
	
	while (t < 1){
		p2 = get_bezier(c->points, 0, 3, t);

		point_linedraw(p1, p2, c->color);
		p1 = p2;

		t += dt;
	}
}