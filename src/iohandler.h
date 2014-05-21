#ifndef IOHANDLER_H
#define IOHANDLER_H

#include <dos.h>
#include <conio.h>

#include "boolean.h"

#define MOUSE_NONE 0
#define MOUSE_LEFT 1
#define MOUSE_RIGHT 2
#define MOUSE_MIDDLE 4

typedef struct{
	int x, y;
	int button;
	long long timestamp;
} mevent_t;

bool getch_async(char* c);
void get_mouse_event(mevent_t* e);


#endif