#include "rect.h"
#include "helper.h"
#include "libgraph.h"

Rect r[100];
int nr;

void rect_setMinMax(Rect* r){
	r->min = r->corner[0];
	r->max = r->corner[0];
	
	for (int i = 1; i < 4; i++){
		r->min.x = min(r->min.x, r->corner[i].x);
		r->min.y = min(r->min.y, r->corner[i].y);
		
		r->max.x = max(r->max.x, r->corner[i].x);
		r->max.y = max(r->max.y, r->corner[i].y);
	}
}

Rect rect_create(int x1, int y1, int x2, int y2){
	Rect r;
	r.corner[0].x = x1;
	r.corner[0].y = y1;
	
	r.corner[1].x = x1;
	r.corner[1].y = y2;
	
	r.corner[2].x = x2;
	r.corner[2].y = y2;
	
	r.corner[3].x = x2;
	r.corner[3].y = y1;
	
	r.center.x = ((float) (x1 + x2)) / 2.f;
	r.center.y = ((float) (y1 + y2)) / 2.f;
	
	rect_setMinMax(&r);
	
	r.fill = BLACK;
	r.color = WHITE;
	
	return r;
}

void rect_translate(Rect* r, int dx, int dy){	
	for (int i = 0; i < 4; ++i){
		point_translate(&r->corner[i], dx, dy);
	}
	
	point_translate(&r->min, dx, dy);
	point_translate(&r->max, dx, dy);
	point_translate(&r->center, dx, dy);
}

void rect_rotate(Rect* r, float deg){
	for (int i = 0; i < 4; ++i){
		point_rotateTo(&r->corner[i], deg, r->center);
	}
	
	rect_setMinMax(r);
}

void rect_scale(Rect* r, float scale){
	for (int i = 0; i < 4; ++i){
		point_scaleTo(&r->corner[i], scale, scale, r->center);
	}
	
	rect_setMinMax(r);
}

bool rect_checkCollision(Rect* r, float x, float y){
	float x1 = r->min.x; float y1 = r->min.y;
	float x2 = r->max.x; float y2 = r->max.y;

	return in_rectangle(x,y,x1,y1,x2,y2);
}

void rect_draw(Rect* r){

	for (int i = 0; i < 3; i++){
		point_linedraw(r->corner[i], r->corner[i+1], r->color);
	}
	
	point_linedraw(r->corner[3], r->corner[0], r->color);
	
	fill_polygon(r->min.x, r->min.y, r->max.x, r->max.y, r->fill, WHITE);
}