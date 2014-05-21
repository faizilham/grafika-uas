#ifndef BUTTON_H
#define BUTTON_H

#include "libgraph.h"

typedef struct Button {
   int x;
   int y;
   int width;
   int height;
   int color; //khusus buat buttoncolor, daripada buat 2 struct :p
   //Polygon icon;
   
   void (*callback)(void*);
} Button;


void button_draw();
void buttonaction_scaleup(void* args);
void buttonaction_scaldown(void* args);
void buttonaction_rotateleft(void* args);
void buttonaction_rotateright(void* args);
void buttonaction_forward(void* args);
void buttonaction_backward(void* args);
void buttonaction_createline(void* args);
void buttonaction_createcurce(void* args);
void buttonaction_createsquare(void* args);
void buttonaction_createcircle(void* args);
void buttonaction_createpolygon(void* args);
void buttonaction_fill(void* args);

void init_button(Button* buttons);

#endif

/*
int abc;
butt.callback = f;
butt.callback((void*) abc)

void f(void* arg){
	int k = (int) arg;

}
*/