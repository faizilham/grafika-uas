// dummy conio.h
#ifndef DUMMY_CONIO_H
#define DUMMY_CONIO_H

#ifndef LIBOPENBGI_H
#include <graphics.h>
#endif


static inline int getch(){
	return readkey();
}

static inline int kbhit(){
	return anykeypressed();
}

#endif