#include "libgraph.h"
#include "iohandler.h"

#include "line.h"
#include "rect.h"

int main(){
	char c = 0; mevent_t e;
	init_graph();
	
	Line l = line_create(0, 0, 200, 200);
	Rect r = rect_create(-150, -150, 50, 50);
	
	
	rect_draw(&r);
	line_draw(&l);
	
	// main loop
	while (c != 'q' && c != 'Q'){
		
		get_mouse_event(&e);
		if (e.button & MOUSE_LEFT){
			printf("(%d, %d) time %d\n", e.x, e.y, e.timestamp);
		}
		
		getch_async(&c);
		delay(100);
	}
	
	
	return 0;

}