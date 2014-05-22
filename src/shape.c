#include "shape.h"

Shape shape_create(){
	
}

void shape_translate(Shape* s, int dx, int dy){
	switch(s->type){ //definisi tipe shape ada di shape.h
		case 1: circ_translate((Circ*)s->object, dx, dy);break;
		case 2: rect_translate((Rect*)s->object, dx, dy);break;
		case 3: /*polygon_translate((Poly*)s->object, dx, dy);*/break; //belum ada implementasi
	}
}

void shape_rotate(Shape* s, float deg){
	switch(s->type){
		case 1: break; //tidak ada rotate pada circle
		case 2: rect_rotate((Rect*)s->object, deg);break;
		case 3: /*polygon_rotate((Poly*)s->object, deg);*/break; //belum ada implementasi
	}
}

void shape_scale(Shape* s, float scale){
	switch(s->type){
		case 1: circ_scale((Circ*)s->object, scale);break;
		case 2: rect_scale((Rect*)s->object, scale);break;
		case 3: /*polygon_scale((Poly*)s->object, scale);*/break; //belum ada implementasi
	}
}

bool shape_checkCollision(Shape* s, float x, float y){
	bool result = false;
	switch(s->type){
		case 1: result = circ_checkCollision((Circ*)s->object, x, y);break;
		case 2: result = rect_checkCollision((Rect*)s->object, x, y);break;
		case 3: /*result = polygon_checkCollision((Poly*)s->object, x, y);*/break; //belum ada implementasi
	}
	return result;
}

void shape_draw(Shape* s){
	switch(s->type){
		case 1: circ_draw((Circ*)s->object);break;
		case 2: rect_draw((Rect*)s->object);break;
		case 3: polygon_draw((Poly*)s->object);break;
	}
}
