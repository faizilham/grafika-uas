#include "shape.h"

Shape shape_create(int num, ...){
	Shape s;
	va_list arglist;
	
	va_start(arglist,num);
	
	//get shape type
	int shape_type = va_arg(arglist,int);
	s.type = shape_type;
	
	switch(shape_type){
		case TYPE_CIRCLE:{
			int _x = va_arg(arglist,int);
			int _y = va_arg(arglist,int);
			float r = (float) va_arg(arglist,double);
			Circ c = circ_create(_x, _y, r);
			s.object = &c;
			break;
		}
		case TYPE_RECT:{
			int x1 = va_arg(arglist,int);
			int y1 = va_arg(arglist,int);
			int x2 = va_arg(arglist,int);
			int y2 = va_arg(arglist,int);
			Rect r = rect_create(x1, y1, x2, y2);
			s.object = &r;
			break;
		}
		case TYPE_POLYGON:{
			Point* corner = va_arg(arglist,Point*);
			int length = va_arg(arglist,int);
			Poly p = polygon_create(corner, length);
			s.object = &p;
			break;
		}
		case TYPE_LINE:{
			int x1 = va_arg(arglist,int);
			int y1 = va_arg(arglist,int);
			int x2 = va_arg(arglist,int);
			int y2 = va_arg(arglist,int);
			Line l = line_create(x1, y1, x2, y2);
			s.object = &l;
			break;
		}
		case TYPE_CURVE:{
			Point* points = va_arg(arglist,Point*);
			Curve c = curve_create(points);
			s.object = &c;
			break;
		}
	}
	
	va_end(arglist);
	
	return s;
}

void shape_setObject(Shape* s, int type, void *object){
	s->type = type;
	s->object = object;
}

void shape_translate(Shape* s, int dx, int dy){
	switch(s->type){
		case TYPE_CIRCLE: circ_translate((Circ*)s->object, dx, dy); break;
		case TYPE_RECT: rect_translate((Rect*)s->object, dx, dy); break;
		case TYPE_POLYGON: polygon_translate((Poly*)s->object, dx, dy); break; 
		case TYPE_LINE: line_translate((Line*)s->object, dx, dy); break;
		case TYPE_CURVE: curve_translate((Curve*)s->object, dx, dy); break;
	}
}

void shape_rotate(Shape* s, float deg){
	switch(s->type){
		case TYPE_CIRCLE: break; //tidak ada rotate pada circle
		case TYPE_RECT: rect_rotate((Rect*)s->object, deg); break;
		case TYPE_POLYGON: polygon_rotate((Poly*)s->object, deg); break; 
		case TYPE_LINE: line_rotate((Line*)s->object, deg); break;
		case TYPE_CURVE: curve_rotate((Curve*)s->object, deg); break;
	}
}

void shape_scale(Shape* s, float scale){
	switch(s->type){
		case TYPE_CIRCLE: circ_scale((Circ*)s->object, scale); break;
		case TYPE_RECT: rect_scale((Rect*)s->object, scale); break;
		case TYPE_POLYGON: polygon_scale((Poly*)s->object, scale); break; 
		case TYPE_LINE: line_scale((Line*)s->object, scale); break;
		case TYPE_CURVE: curve_scale((Curve*)s->object, scale); break;
	}
}

bool shape_checkCollision(Shape* s, float x, float y){
	bool result = false;
	switch(s->type){
		case TYPE_CIRCLE: result = circ_checkCollision((Circ*)s->object, x, y); break;
		case TYPE_RECT: result = rect_checkCollision((Rect*)s->object, x, y); break;
		case TYPE_POLYGON: result = polygon_checkCollision((Poly*)s->object, x, y); break; 
		case TYPE_LINE: result = line_checkCollision((Line*)s->object, x, y); break;
		case TYPE_CURVE: result = curve_checkCollision((Curve*)s->object, x, y); break;
	}
	return result;
}

void shape_draw(Shape* s){
	switch(s->type){
		case TYPE_CIRCLE: circ_draw((Circ*)s->object); break;
		case TYPE_RECT: rect_draw((Rect*)s->object); break;
		case TYPE_POLYGON: polygon_draw((Poly*)s->object);  break;
		case TYPE_LINE: line_draw((Line*)s->object); break;
		case TYPE_CURVE: curve_draw((Curve*)s->object); break;
	}
}

void shape_setColor(Shape* s, int color){
	switch(s->type){
		case TYPE_CIRCLE:((Circ*)s->object)->color = color; break;
		case TYPE_RECT:((Rect*)s->object)->color = color; break;
		case TYPE_POLYGON: ((Poly*)s->object)->color = color; break;
		case TYPE_LINE: ((Line*)s->object)->color = color; break;
		case TYPE_CURVE:((Curve*)s->object)->color = color; break;
	}
}

void shape_setFillColor(Shape* s, int fill){
	switch(s->type){
		case TYPE_CIRCLE: ((Circ*)s->object)->fill = fill; break;
		case TYPE_RECT:((Rect*)s->object)->fill = fill; break;
		case TYPE_POLYGON: ((Poly*)s->object)->fill = fill; break;
		// line dan curve tidak bisa di fill
	}
}
