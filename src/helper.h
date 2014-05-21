#ifndef HELPER_H
#define HELPER_H

static float min(float a, float b){
	return (a < b) ? a : b;
}

static float max(float a, float b){
	return (a > b) ? a : b;
}

static int in_rectangle(float x, float y, float x1, float y1, float x2, float y2){
	return (x1 < x) && (x < x2) && (y1 < y) && (y < y2);
}

#endif
