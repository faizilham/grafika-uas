#ifndef BUTTON_H
#define BUTTON_H

#include "libgraph.h"
#include "iohandler.h"
#include "shape.h"

typedef struct Button {
   int x;
   int y;
   int width;
   int height;
   int color; //khusus buat buttoncolor, daripada buat 2 struct :p
   int border;
   void (*callback)(void*);
   Shape icon;
} Button;


void button_draw();
bool button_checkcollision(Button button,int x,int y);
void buttonaction_scaleup(void* args);
void buttonaction_scaldown(void* args);
void buttonaction_rotateleft(void* args);
void buttonaction_rotateright(void* args);
void buttonaction_forward(void* args);
void buttonaction_backward(void* args);
void buttonaction_createline(void* args);
void buttonaction_createcurve(void* args);
void buttonaction_createsquare(void* args);
void buttonaction_createcircle(void* args);
void buttonaction_createpolygon(void* args);
void buttonaction_fill(void* args);

void init_button(Button* buttons);
void refresh_buttons(Button* buttons);

#endif

/*
int abc;
butt.callback = f;
butt.callback((void*) abc)

void f(void* arg){
	int k = (int) arg;

}
*/