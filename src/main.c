#include "libgraph.h"
#include "iohandler.h"
#include "button.h"


Button buttons[100];

int main(){
	char c = 0; mevent_t e;
	init_graph();
	init_button(buttons);
	
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