#include "polygon.h"

Poly p[100];
int np;

void polygon_setMinMax(Poly *p){
	p->min = p->corner[0];
	p->max = p->corner[0];
	for (int i=0; i<p->neff; i++){
		if (p->min.x > p->corner[i].x){
			p->min.x = p->corner[i].x;
		}
		if (p->min.y > p->corner[i].y){
			p->min.y = p->corner[i].y;
		}
		if (p->max.x < p->corner[i].x){
			p->max.x = p->corner[i].x;
		}
		if (p->max.y < p->corner[i].y){
			p->max.y = p->corner[i].y;
		}
	}

	p->center.x = (p->min.x + p->max.x)/2;
	p->center.y = (p->min.y + p->max.y)/2;
}

Poly polygon_create(Point *corner,int length){
	Poly poly;
	for (int i=0;i<length;i++){
		poly.corner[i].x = corner[i].x;
		poly.corner[i].y = corner[i].y;
	}
	poly.neff = length;
	polygon_setMinMax(&poly);
	
	poly.fill = BLACK;
	poly.color = WHITE;
	
	return poly;
}

void polygon_draw(Poly *p){
	int length = p->neff;
	for (int i=0;i<length-1;i++){
		draw_line(p->corner[i].x,p->corner[i].y,p->corner[i+1].x,p->corner[i+1].y,p->color);
	}
	draw_line(p->corner[length-1].x,p->corner[length-1].y,p->corner[0].x,p->corner[0].y,p->color);
	
	fill_polygon (p->min.x, p->min.y, p->max.x, p->max.y, p->fill, WHITE);
}

void polygon_translate(Poly *p, int dx, int dy){
	for (int i = 0; i < p->neff; ++i){
		point_translate(&p->corner[i], dx, dy);
	}
	
	point_translate(&p->min, dx, dy);
	point_translate(&p->max, dx, dy);
	point_translate(&p->center, dx, dy);
}

bool polygon_checkCollision(Poly* p, float x, float y){
	int i, j, c = 0;
  	for (i = 0, j = p->neff-1; i < p->neff; j = i++) {
    if ( ((p->corner[i].y>y) != (p->corner[j].y>y)) && (x < (p->corner[j].x-p->corner[i].x) * (y-p->corner[i].y) / (p->corner[j].y-p->corner[i].y) + p->corner[i].x) )
       	c = !c;
  	}
	return c;
}