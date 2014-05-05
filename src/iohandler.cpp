#include "iohandler.hpp"

bool getch_async(char& c){
	// non-blocking getch
	
	if (kbhit()){
		c = getch();
		if(c == 0){ //Handle arrow key
			c = getch();
			//printf("Char: %d\n", c);
		}
		
		return true;
	}else{
		return false;
	}
}

#ifdef DUMMY_DOS_H
static int mouse_tstamp = 0;
static g_mousestate state;

void get_mouse_event(mevent_t& e){
	getmousestate(&state);
	
	e.x = state.x; e.y = state.y; e.button = state.buttons;
	e.timestamp = mouse_tstamp++;
}


#else
/** dos.h beneran **/
/** belom ada **/

void get_mouse_event(mevent_t& e){

}

#endif