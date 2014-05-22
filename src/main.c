#include "libgraph.h"
#include "iohandler.h"
#include "button.h"

#include "line.h"
#include "rect.h"
#include "circle.h"
#include "curve.h"

#include "overlay.h"

#define EVENT_NONE 0
#define EVENT_REDRAW 1
#define EVENT_DRAGGING 2


int current_event = EVENT_NONE;
Rect* current_shape = NULL;

Button buttons[100];

extern Line l[100];
extern int nl;

extern Rect r[100];
extern int nr;

extern Poly p[100];
extern int np;

Circ cir;
Array arr_rect; //array of rect for overlaying

Rect canvas;
Curve crv;

void refresh_canvas(){
	cleardevice();
	
	/* Draw canvas boundary */
	rect_draw(&canvas);
	
	curve_draw(&crv);
		
	for (int i = 0; i < nr; ++i){
		rect_draw(&r[i]);
	}
	circ_draw(&cir);
	
	/*rect overlay test*/
	for (int i = 0; i < arr_rect.size; ++i){
		Rect objRect = array_get(&arr_rect,i);
		rect_draw(&objRect);
	}
	doOverlay(&arr_rect);
	/*end of rect overlay test*/
}

int main(){
	printf("a");
	char c = 0; mevent_t e, last;
	last.button = MOUSE_NONE;
	
	init_graph();
	
	canvas = rect_create(-300, 160, 295, -210);
	
	crv.color = 15;
	curve_setPoint(&crv, 0, -250, 0);
	curve_setPoint(&crv, 1, -150, 100);
	curve_setPoint(&crv, 2, -100, -100);
	curve_setPoint(&crv, 3, -50, 0);
	
	cir = circ_create(100, 100, 200);

	nl = 0;

	cir = circ_create(100, 100, 20);
	cir.fill = LIGHTGRAY;


	r[0] = rect_create(-50, -50, -10, -10);
	r[0].fill = YELLOW;
	r[1] = rect_create(10, 10, 50, 50);
	r[1].fill = MAGENTA;
	r[2] = rect_create(-50, 50, -10, 10);
	r[2].fill = CYAN;
	nr = 3;
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
	while (c != 'q' && c != 'Q'){

		
		printf("a");
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
				for (int i = 0; i < nr; ++i){
					if (rect_checkCollision(&r[i], e.x, e.y)){
						current_event = EVENT_DRAGGING;
						current_shape = &r[i];
						found = true;
						break;
					}
				}
				if (!found){
					
					// check collide dengan button
					for (int i=0;i<21;i++){
						if (button_checkcollision(buttons[i],e.x,e.y)){

							// action fill
							if (i <= 15){

							}
							else if (i <= 21) {
								int *args;
								buttons[i].callback((void*) args);
								
							}
						}
					}
				}
			}else if (current_event = EVENT_DRAGGING){
				rect_translate(current_shape, e.x - last.x, e.y - last.y);
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
			current_shape = NULL;
			//refresh_buttons(buttons);
		}
		
		last = e;
		getch_async(&c);
		delay(100);
	}
	
	
	return 0;

}