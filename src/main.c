#include "libgraph.h"
#include "iohandler.h"
#include "button.h"

#include "shape.h"
#include "libgraph.h"

#include "overlay.h"
#include "export.h"

#define EVENT_NONE 0
#define EVENT_REDRAW 1
#define EVENT_DRAGGING 2


int current_event = EVENT_NONE;
int current_type_shape;
int current_i;
int current_max_c;
Point *current_min = NULL, *current_max = NULL;
Rect* current_shape = NULL;

Button buttons[100];

extern Line l[100];
extern int nl;

extern Rect r[100];
extern int nr;

extern Poly p[100];
extern int np;

extern Circ ci[100];
extern int nci;

extern Curve cu[100];
extern int ncu;

Array arr_rect; //array of rect for overlaying

Rect canvas;


void draw_select(){
	int color = 14;
	int part = 6;
	int d = 2;
	if (current_min != NULL && current_max != NULL){
		draw_dash(current_min->x - d, current_min->y - d, current_min->x - d, current_max->y + d, part, color);
		draw_dash(current_min->x - d, current_max->y + d, current_max->x + d, current_max->y + d, part, color);
		draw_dash(current_max->x + d, current_max->y + d, current_max->x + d, current_min->y - d, part, color);
		draw_dash(current_max->x + d, current_min->y - d, current_min->x - d, current_min->y - d, part, color);
	}
}

void refresh_canvas(){
	cleardevice();
	
	/* Draw canvas boundary */
	rect_draw(&canvas);
	
	for (int i=0;i<nl;i++){
		line_draw(&l[i]);
	}

	for (int i = 0; i < nr; ++i){
		rect_draw(&r[i]);
	}

	for (int i=0;i<np;i++){
		polygon_draw(&p[i]);
	}

	for (int i=0;i<nci;i++){
		circ_draw(&ci[i]);
	}
	for (int i=0;i<ncu;i++){
		curve_draw(&cu[i]);
	}
	
	draw_select();
	
	/*rect overlay test*/
	for (int i = 0; i < arr_rect.size; ++i){
		Rect objRect = array_get(&arr_rect,i);
		rect_draw(&objRect);
	}
	doOverlay(&arr_rect);
	/*end of rect overlay test*/
}

int main(){
	current_type_shape = -1; //0 = line, 1 = curve, 2 = rect, 3 = circle, 4 = poly
	current_max_c = 0;
	printf("a");
	char c = 0; mevent_t e, last;
	last.button = MOUSE_NONE;
	
	init_graph();
	
	canvas = rect_create(-300, 160, 295, -210);

	nl = 0;
	nr = 0;
	/*rect overlay test*/
	array_init(&arr_rect);
	
	Rect r1 = rect_create(-30,-30,20,20);
	r1.fill = RED;
	Rect r2 = rect_create(-10,-10,35,35);
	r2.fill = BLUE;
	
	array_append(&arr_rect,r1);
	array_append(&arr_rect,r2);
	/*end of rect overlay test*/
	
	refresh_canvas();
	init_button(buttons);
	refresh_buttons(buttons);
	// main loop
	printf("a");
	//export_canvas();
	
	while (c != 'q' && c != 'Q'){

		
		//printf("a");
		if (current_event != EVENT_NONE){
			refresh_canvas();
			refresh_buttons(buttons);
			if (current_event == EVENT_REDRAW){
				current_event = EVENT_NONE;
			}
		}
		//refresh_buttons(buttons);
		// mouse process
		//printf("a");
		
		get_mouse_event(&e);
		//printf("a");
		if (e.button & MOUSE_LEFT){			
			if (current_event == EVENT_NONE){
				bool found = false;
				// check collide dengan garis
				for (int i=0; i < nl; i++){
					if (line_checkCollision(&l[i], e.x, e.y)){
						current_event = EVENT_DRAGGING;
						current_type_shape = 0;
						current_i = i;
						current_min = &l[i].min;
						current_max = &l[i].max;
						found = true;
						break;
					}
				}

				// check collide dengan curve
				if (!found){
					for (int i = 0; i < ncu; ++i){
						if (curve_checkCollision(&cu[i], e.x, e.y)){
							current_event = EVENT_DRAGGING;
							//current_shape = &r[i];
							current_type_shape = 1;
							current_i = i;
							current_min = &cu[i].min;
							current_max = &cu[i].max;
							found = true;
							break;
						}
					}
				}


				// check collide dengan rectangle
				if (!found){
					for (int i = 0; i < nr; ++i){
						if (rect_checkCollision(&r[i], e.x, e.y)){
							current_event = EVENT_DRAGGING;
							//current_shape = &r[i];
							current_type_shape = 2;
							current_i = i;
							current_min = &r[i].min;
							current_max = &r[i].max;
							found = true;
							break;
						}
					}
				}
				// check collide dengan circle
				if (!found){
					for (int i=0;i < nci; i++){
						if (circ_checkCollision(&ci[i],e.x,e.y)){
							current_event = EVENT_DRAGGING;
							current_type_shape = 3;
							current_i = i;
							current_min = &ci[i].min;
							current_max = &ci[i].max;
							found = true;
							break;
						}
					}
				}


				// check collide dengan polygon
				if (!found) {
					for (int i=0;i<np;i++){
						if (polygon_checkCollision(&p[i], e.x, e.y)){
							current_event = EVENT_DRAGGING;
							current_type_shape = 4;
							current_i = i;
							current_min = &p[i].min;
							current_max = &p[i].max;
							found = true;
							break;
						}
					}
				}
				// check collide dengan button
				if (!found){
					for (int i=0;i<30;i++){
						if (button_checkcollision(buttons[i],e.x,e.y)){

							// action fill
							if (i < 16){
								if (current_type_shape == 0){
									l[current_i].color = i;
								} else if (current_type_shape == 1){
									cu[current_i].color = i;
								} else if (current_type_shape == 2){
									r[current_i].fill = i;
								}
								else if (current_type_shape == 3){
									ci[current_i].fill = i;
								}else if (current_type_shape == 4){
									p[current_i].fill = i;
								}
								
							}
							else if (i < 30) {
								buttons[i].border = 14;
								refresh_buttons(buttons);
								
								int *args;
								buttons[i].callback((void*) args);
								
								buttons[i].border = 15;
								refresh_buttons(buttons);
							}
							refresh_canvas();
							refresh_buttons(buttons);
							break;
						}
					}
				}
			}else if (current_event = EVENT_DRAGGING){
				if (current_type_shape == 0)
					line_translate(&l[current_i], e.x - last.x, e.y - last.y);
				else if (current_type_shape == 1)
					curve_translate(&cu[current_i], e.x - last.x, e.y - last.y);
				else if (current_type_shape == 2)
					rect_translate(&r[current_i], e.x - last.x, e.y - last.y);
				else if (current_type_shape == 3)
					circ_translate(&ci[current_i], e.x - last.x, e.y - last.y);
				else if (current_type_shape == 4)
					polygon_translate(&p[current_i], e.x - last.x, e.y - last.y);
			}
			
		}else if (e.button & MOUSE_RIGHT){			
			if (current_event == EVENT_NONE){
				for (int i = 0; i < nr; ++i){
					if (rect_checkCollision(&r[i], e.x, e.y)){
						rect_rotate(&r[i],45);
						current_event = EVENT_REDRAW;
						break;
					}
				}
			}
		}else{
			current_event = EVENT_NONE;
			//current_shape = NULL;
			//refresh_buttons(buttons);
		}
		
		last = e;
		getch_async(&c);
		delay(100);
	}
	
	//export_canvas();
	
	return 0;

}