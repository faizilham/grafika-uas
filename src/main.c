#include "libgraph.h"
#include "iohandler.h"
#include "button.h"

#include "line.h"
#include "rect.h"


#define EVENT_NONE 0
#define EVENT_REDRAW 1
#define EVENT_DRAGGING 2


int current_event = EVENT_NONE;
Rect* current_shape = NULL;
Button buttons[100];
Rect r[3];

void refresh_canvas(){
	cleardevice();
		
	for (int i = 0; i < 3; ++i){
		rect_draw(&r[i]);
	}
}

int main(){
	char c = 0; mevent_t e, last;
	last.button = MOUSE_NONE;
	
	init_graph();
	
	
	r[0] = rect_create(-50, -50, -10, -10);
	r[1] = rect_create(10, 10, 50, 50);
	r[2] = rect_create(-50, 50, -10, 10);
	
	refresh_canvas();
	init_button(buttons);
	// main loop
	while (c != 'q' && c != 'Q'){
		
		if (current_event != EVENT_NONE){
			refresh_canvas();
			if (current_event == EVENT_REDRAW){
				current_event = EVENT_NONE;
			}
		}
		
		// mouse process
		
		get_mouse_event(&e);
		if (e.button & MOUSE_LEFT){			
			if (current_event == EVENT_NONE){
				for (int i = 0; i < 3; ++i){
					if (rect_checkCollision(&r[i], e.x, e.y)){
						current_event = EVENT_DRAGGING;
						current_shape = &r[i];
						break;
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
		}
		
		last = e;
		getch_async(&c);
		delay(100);
	}
	
	
	return 0;

}