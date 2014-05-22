#include "libgraph.h"

int midx, midy;

void init_graph(){
	int gdriver = DETECT; int gmode;
	initgraph(&gdriver,&gmode,"C:\\TC\\BGI");
	midx=(getmaxx() + 1)/2;
	midy=(getmaxy() + 1)/2;
}

void paintpix(int x, int y, int color){
	putpixel(midx + x, midy - y, color);
}

int cgetpixel(int x, int y){
	return getpixel(midx + x, midy - y);
}

void draw_line(int x1, int y1, int x2, int y2, int color){
	// using bresenham algorithm

	int error = 0, x, y, dx, dy, c1, c2, c3;

	if (abs(x1 - x2) > abs(y1 - y2)){ // low slope, |m| < 1
		int xstart, xfinish;

		// calculate start-end x
		if (x1 < x2){
			xstart = x1; xfinish = x2;
			dx = x2 - x1; dy = y2 - y1; y = y1;
		}else{
			xstart = x2; xfinish = x1;
			dx = x1 - x2; dy = y1 - y2; y = y2;
		}

		// calculate constants depends on positive of negative gradient
		if (dy > 0){
			c1 = 2; c2 = 1; c3 = dy - dx;
		}else{
			c1 = -2; c2 = -1; c3 = dy + dx;
		}

		for (x = xstart; x <= xfinish; x++){
			paintpix(x, y, color);

			// calculate next error and next y
			if (c1*(error + dy) < dx){
				error += dy;
			}else{
				y+=c2; error += c3;
			}
		}

	}else{ // high slope, |m| >= 1
		int ystart, yfinish;

		// calculate start-end y
		if (y1 < y2){
			ystart = y1; yfinish = y2;
			dy = y2 - y1; dx = x2 - x1; x = x1;
		}else{
			ystart = y2; yfinish = y1;
			dy = y1 - y2; dx = x1 - x2; x = x2;
		}

		// calculate constants depends on positive of negative gradient
		if (dx > 0){
			c1 = 2; c2 = 1; c3 = dx - dy;
		}else{
			c1 = -2; c2 = -1; c3 = dx + dy;
		}

		for (y = ystart; y <= yfinish; y++){
			paintpix(x, y, color);

			// calculate next error and next x
			if (c1*(error + dx) < dy){
				error += dx;
			}else{
				x+=c2; error += c3;
			}
		}
	}
}

void draw_ellipse(int xc, int yc, int rx,int ry, int color){
	int x=0,y=ry;
	int p=(ry*ry)-(rx*rx*ry)+((rx*rx)/4);
	while((2*x*ry*ry)<(2*y*rx*rx)){
		paintpix(xc+x,yc+y,color);
		paintpix(xc-x,yc-y,color);
		paintpix(xc+x,yc-y,color);
		paintpix(xc-x,yc+y,color);

		if(p<0){
		   x=x+1;
		   p=p+(2*ry*ry*x)+(ry*ry);
		} else {
		   x=x+1;
		   y=y-1;
		   p=p+(2*ry*ry*x+ry*ry)-(2*rx*rx*y);
		}
	}
		p=((float)x+0.5)*((float)x+0.5)*ry*ry+(y-1)*(y-1)*rx*rx-rx*rx*ry*ry;

	while(y>=0){
		paintpix(xc+x,yc+y,color);
		paintpix(xc-x,yc-y,color);
		paintpix(xc+x,yc-y,color);
		paintpix(xc-x,yc+y,color);

		if(p>0){
		   y=y-1;
		   p=p-(2*rx*rx*y)+(rx*rx);
		} else {
		   y=y-1;
		   x=x+1;
		   p=p+(2*ry*ry*x)-(2*rx*rx*y)-(rx*rx);
	    }
	}
}

void fill (int x, int y, int fill_color, int boundary_color)
{
	int current;
	current = cgetpixel(x, y);
	
	if((x+midx > 0) && (x+midx < getmaxx()) && (midy-y > 0) && (midy-y < getmaxy())){
		if ((current != boundary_color) &&  (current != fill_color)){
			setcolor(fill_color);
			paintpix(x, y, fill_color);

			fill (x + 1, y, fill_color, boundary_color); //right
			fill (x - 1,  y, fill_color, boundary_color); //left
			fill (x, y - 1, fill_color, boundary_color) ; //up
			fill (x, y + 1, fill_color, boundary_color); //down
		}
	}
}

bool isExtremePoint(int x, int y){
	bool result;
	
	int boundary_color = cgetpixel(x, y);
	
	//neighbouring pixels
	int left_color = cgetpixel(x-1, y);
	int right_color = cgetpixel(x+1, y);
	int top_color = cgetpixel(x, y+1);
	int bottom_color = cgetpixel(x, y-1);
	int lefttop_color = cgetpixel(x-1, y+1);
	int righttop_color = cgetpixel(x+1, y+1);
	int leftbottom_color = cgetpixel(x-1, y-1);
	int rightbottom_color = cgetpixel(x+1, y-1);
	
	//kondisi 1 : titik ekstrim minimum
	if((left_color != boundary_color)
		&& (right_color != boundary_color)
		&& (leftbottom_color != boundary_color)
		&& (rightbottom_color != boundary_color)
		&& (bottom_color != boundary_color)
		&& (top_color != boundary_color)
		&& (lefttop_color == boundary_color)
		&& (righttop_color == boundary_color)){
			result = true;
	}
	//kondisi 2 : titik ekstrim maksimum
	else if((left_color != boundary_color)
		&& (right_color != boundary_color)
		&& (leftbottom_color == boundary_color)
		&& (rightbottom_color == boundary_color)
		&& (bottom_color != boundary_color)
		&& (top_color != boundary_color)
		&& (lefttop_color != boundary_color)
		&& (righttop_color != boundary_color)){
			result = true;
	}
	else{
		result = false;
	}
	
	return result;
}

void fill_polygon (int xmin, int ymin, int xmax, int ymax, int fill_color, int boundary_color){
//trying to use scan line algorithm
//horizontal scan line
	int curr_x, curr_color, curr_color_next;
	
	//scan line
	for(int y = ymin+1; y < ymax; y++){
		if(midy-y < 0){
			break; //handle out-of-screen condition
		}
		
		curr_x = xmin;
		bool status = false;
		//go to the leftmost edge
		curr_color = cgetpixel(curr_x, y);
		while((curr_color != boundary_color) && (curr_x < xmax)){
			curr_x++;
			curr_color = cgetpixel(curr_x, y);
		}
		//found the leftmost edge, go to the "rightmost" leftmost edge
		curr_color = cgetpixel(curr_x, y);
		curr_color_next = cgetpixel(curr_x+1, y);
		while((curr_color == boundary_color) && (curr_color_next == boundary_color)){
			curr_x++;
			curr_color = cgetpixel(curr_x, y);
			curr_color_next = cgetpixel(curr_x+1, y);
		}
		
		if(curr_color == boundary_color){
			while((curr_x < xmax) && (curr_x+midx < getmaxx())){ //handle out-of-screen condition
				curr_color = cgetpixel(curr_x, y);
				//if curr_x meets the boundary edge
				if(curr_color == boundary_color){
					curr_color_next = cgetpixel(curr_x+1, y);
					if((isExtremePoint(curr_x,y) == false) && (curr_color_next != boundary_color)){
						status = !status;
					}
				}
				if(status == true){
					//if curr_x is inside the polygon
					if ((curr_color != boundary_color) &&  (curr_color != fill_color)){
						setcolor (fill_color);
						paintpix(curr_x, y, fill_color);
					}
				}
				curr_x++;
			}
		}
	}	
}

