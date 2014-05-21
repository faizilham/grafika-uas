#ifndef BUTTON_H
#define BUTTON_H

struct Button {
   int x;
   int y;
   int width;
   int height;
   int color; //khusus buat buttoncolor, daripada buat 2 struct :p
   Polygon icon;
   
   void (*callback)(void*) = NULL;
};

struct ButtonColor {
   int x;
   int y;
   int width;
   int height;
   int color;
   
   void (*callback)(void*) = NULL;
};

/*
int abc;
butt.callback = f;
butt.callback((void*) abc)

void f(void* arg){
	int k = (int) arg;

}
*/