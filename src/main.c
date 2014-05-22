#include "libgraph.h"
#include "iohandler.h"
#include "button.h"

#include "line.h"
#include "rect.h"
#include "circle.h"

#include "overlay.h"

#define EVENT_NONE 0
#define EVENT_REDRAW 1
#define EVENT_DRAGGING 2


int current_event = EVENT_NONE;
Rect* current_shape = NULL;

Button buttons[100];
Rect r[3];
Circ cir;
Array arr_rect; //array of rect for overlaying
void refresh_canvas(){
	cleardevice();
		
	for (int i = 0; i < 3; ++i){
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
	
	cir = circ_create(100, 100, 200);
	r[0] = rect_create(-50, -50, -10, -10);
	r[1] = rect_create(10, 10, 50, 50);
	r[2] = rect_create(-50, 50, -10, 10);
	
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
	;
	// main loop
	printf("a");
	while (c != 'q' && c != 'Q'){
		refresh_buttons(buttons);
		printf("a");
		if (current_event != EVENT_NONE){
			refresh_canvas();
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
				for (int i = 0; i < 3; ++i){
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
						if ((buttons[i].x < e.x) && (buttons[i].x + buttons[i].width > e.x) && (buttons[i].y < e.y) && (buttons[i].y + buttons[i].height < e.y )){
							
						}
					}
				}
			}else if (current_event = EVENT_DRAGGING){
				rect_translate(current_shape, e.x - last.x, e.y - last.y);
			}
			
		}else if (e.button & MOUSE_RIGHT){			
			if (current_event == EVENT_NONE){
				for (int i = 0; i < 3; ++i){
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