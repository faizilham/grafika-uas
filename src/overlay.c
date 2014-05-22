#include "overlay.h"

void doOverlay(Array *array_polygon){
	//variable declaration
	int x,y,i;
	int xmin,ymin,xmax,ymax;
	Rect objRect;	
	
	objRect = array_get(array_polygon,0);
	xmin = objRect.min.x;
	ymin = objRect.min.y;
	xmax = objRect.max.x;
	ymax = objRect.max.y;
	//determine xmin, ymin, xmax, ymax
	for(i = 0; i < (array_polygon->size); i++){
		objRect = array_get(array_polygon,i);
		if((objRect.min.x) < xmin){
			xmin = objRect.min.x;
		}
		if((objRect.min.y) < ymin){
			ymin = objRect.min.y;
		}
		if((objRect.max.x) > xmax){
			xmax = objRect.max.x;
		}
		if((objRect.max.y) > ymax){
			ymax = objRect.max.y;
		}
	}
	int freeline[xmax-xmin+1];
	
	//scanline and filling process, top-down
	for(y = ymax; y >= ymin; y--){
		//reset freeline
		for(i = 0; i < (xmax-xmin+1); i++){
			freeline[i] = 0;
		}
		
		//do the scanline for each quad
		for(i = 0; i < (array_polygon->size); i++){
			//alokasi jatah setiap quad ke free line
			objRect = array_get(array_polygon,i);
			int fill = objRect.fill;
			for(x = xmin; x <= xmax; x++){
				if((freeline[x-xmin] == 0) && (x >= objRect.min.x) && (x <= objRect.max.x) && (y >= objRect.min.y) && (y <= objRect.max.y)){
					//set freeline[x] dengan "kode jatah" quad
					freeline[x-xmin] = i+1;
					//proses pewarnaan
					paintpix(x,y,fill);
				}
			}
		}
	}
}
