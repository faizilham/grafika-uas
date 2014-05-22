#include "button.h"

extern Rect r[100];
extern int nr;
extern Poly p[100];
extern int np;


void button_draw(Button button){
	draw_line(button.x,button.y,button.x+button.width,button.y,15);
	draw_line(button.x+button.width,button.y,button.x+button.width,button.y+button.height,15);
	draw_line(button.x+button.width,button.y+button.height,button.x,button.y+button.height,15);
	draw_line(button.x,button.y+button.height,button.x,button.y,15);
	fill(button.x+1,button.y+1,button.color,15);
	if (button.icon != NULL)
		polygon_draw(button.icon);
}

bool button_checkcollision(Button button,int x,int y){
	return (button.x < x) && (x < button.x+button.width) && (button.y < y) && (y < button.y+button.width);
}


void buttonaction_scaleup(void* args){
	int shape_type = ((int*)args)[0];
	int shape_id = ((int*)args)[1];
}

void buttonaction_scaldown(void* args){
	int shape_type = ((int*)args)[0];
	int shape_id = ((int*)args)[1];
}

void buttonaction_rotateleft(void* args){
	int shape_type = ((int*)args)[0];
	int shape_id = ((int*)args)[1];
}

void buttonaction_rotateright(void* args){
	int shape_type = ((int*)args)[0];
	int shape_id = ((int*)args)[1];
}

void buttonaction_forward(void* args){
	int shape_type = ((int*)args)[0];
	int shape_id = ((int*)args)[1];
}

void buttonaction_backward(void* args){
	int shape_type = ((int*)args)[0];
	int shape_id = ((int*)args)[1];
}

void buttonaction_createline(void* args){

}

void buttonaction_createcurve(void* args){

}

void buttonaction_createsquare(void* args){
	mevent_t e;
	delay(100);
	do {
		get_mouse_event(&e);
	} while (!(e.button & MOUSE_LEFT));
	int x1 = e.x;
	int y1 = e.y;
	delay(100);
	do {
		get_mouse_event(&e);
	} while (!(e.button & MOUSE_LEFT));
	int x2 = e.x;
	int y2 = e.y;
	r[nr] = rect_create(x1, y1, x2, y2);
	nr++;
	rect_draw(&r[nr-1]);
}

void buttonaction_createcircle(void* args){

}

void buttonaction_createpolygon(void* args){
	mevent_t e;
	Point corner[100];
	int i = 0;
	delay(100);
	do {
		get_mouse_event(&e);
		if (e.button & MOUSE_LEFT){
			corner[i].x = e.x;
			corner[i].y = e.y;
			i++;
			//outtextxy(i*3, 0, "o");
			delay(100);
		}
	} while (!(e.button & MOUSE_RIGHT));
	p[np] = polygon_create(corner,i);
	//outtextxy(100,100,"ok");
	np++;
}

void buttonaction_fill(void* args){
	int shape_type = ((int*)args)[0];
	int shape_id = ((int*)args)[1];
	int color = ((int*)args)[2];
}

Poly polygon,polygon2,polygon3,polygon4,polygon5;

void init_button(Button* buttons){
	buttons[0].x = 100; buttons[0].y = 210; buttons[0].width = 20; buttons[0].height = 20; buttons[0].color = 0; buttons[0].callback = buttonaction_fill;
	buttons[1].x = 125; buttons[1].y = 210; buttons[1].width = 20; buttons[1].height = 20; buttons[1].color = 1; buttons[1].callback = buttonaction_fill;
	buttons[2].x = 150; buttons[2].y = 210; buttons[2].width = 20; buttons[2].height = 20; buttons[2].color = 2; buttons[2].callback = buttonaction_fill;
	buttons[3].x = 175; buttons[3].y = 210; buttons[3].width = 20; buttons[3].height = 20; buttons[3].color = 3; buttons[3].callback = buttonaction_fill;
	buttons[4].x = 200; buttons[4].y = 210; buttons[4].width = 20; buttons[4].height = 20; buttons[4].color = 4; buttons[4].callback = buttonaction_fill;
	buttons[5].x = 225; buttons[5].y = 210; buttons[5].width = 20; buttons[5].height = 20; buttons[5].color = 5; buttons[5].callback = buttonaction_fill;
	buttons[6].x = 250; buttons[6].y = 210; buttons[6].width = 20; buttons[6].height = 20; buttons[6].color = 6; buttons[6].callback = buttonaction_fill;
	buttons[7].x = 275; buttons[7].y = 210; buttons[7].width = 20; buttons[7].height = 20; buttons[7].color = 7; buttons[7].callback = buttonaction_fill;

	buttons[ 8].x = 100; buttons[ 8].y = 185; buttons[ 8].width = 20; buttons[ 8].height = 20; buttons[ 8].color =  8; buttons[ 8].callback = buttonaction_fill;
	buttons[ 9].x = 125; buttons[ 9].y = 185; buttons[ 9].width = 20; buttons[ 9].height = 20; buttons[ 9].color =  9; buttons[ 9].callback = buttonaction_fill;
	buttons[10].x = 150; buttons[10].y = 185; buttons[10].width = 20; buttons[10].height = 20; buttons[10].color = 10; buttons[10].callback = buttonaction_fill;
	buttons[11].x = 175; buttons[11].y = 185; buttons[11].width = 20; buttons[11].height = 20; buttons[11].color = 11; buttons[11].callback = buttonaction_fill;
	buttons[12].x = 200; buttons[12].y = 185; buttons[12].width = 20; buttons[12].height = 20; buttons[12].color = 12; buttons[12].callback = buttonaction_fill;
	buttons[13].x = 225; buttons[13].y = 185; buttons[13].width = 20; buttons[13].height = 20; buttons[13].color = 13; buttons[13].callback = buttonaction_fill;
	buttons[14].x = 250; buttons[14].y = 185; buttons[14].width = 20; buttons[14].height = 20; buttons[14].color = 14; buttons[14].callback = buttonaction_fill;
	buttons[15].x = 275; buttons[15].y = 185; buttons[15].width = 20; buttons[15].height = 20; buttons[15].color = 15; buttons[15].callback = buttonaction_fill;
	

	buttons[16].x = -300; buttons[16].y = 200; buttons[16].width = 25; buttons[16].height = 25; buttons[16].color = 0;
	Point corner[30];
	corner[0].x = -295; corner[0].y = 205; corner[1].x = -280; corner[1].y = 220;
	polygon = polygon_create(corner,2);
	buttons[16].icon = &polygon;
	buttons[16].callback = buttonaction_createline;
	
	buttons[17].x = -270; buttons[17].y = 200; buttons[17].width = 25; buttons[17].height = 25; buttons[17].color = 0;
	Point corner2[30];
	corner2[0].x = -265; corner2[0].y = 205; corner2[1].x = -250; corner2[1].y = 220;
	polygon2 = polygon_create(corner2,2);
	buttons[17].icon = &polygon2;
	buttons[17].callback = buttonaction_createcurve;

	buttons[18].x = -240; buttons[18].y = 200; buttons[18].width = 25; buttons[18].height = 25; buttons[18].color = 0;
	Point corner3[30];
	corner3[0].x = -235; corner3[0].y = 205; corner3[1].x = -235; corner3[1].y = 220;
	corner3[2].x = -220; corner3[2].y = 220; corner3[3].x = -220; corner3[3].y = 205;
	polygon3 = polygon_create(corner3,4);
	buttons[18].icon = &polygon3;
	buttons[18].callback = buttonaction_createsquare;

	buttons[19].x = -210; buttons[19].y = 200; buttons[19].width = 25; buttons[19].height = 25; buttons[19].color = 0;
	Point corner4[30];
	corner4[0].x = -205; corner4[0].y = 205; corner4[1].x = -190; corner4[1].y = 220;
	polygon4 = polygon_create(corner4,2);
	buttons[19].icon = &polygon4;
	buttons[19].callback = buttonaction_createcircle;

	buttons[20].x = -180; buttons[20].y = 200; buttons[20].width = 25; buttons[20].height = 25; buttons[20].color = 0;
	Point corner5[30];
	corner5[0].x = -172; corner5[0].y = 205; corner5[1].x = -163; corner5[1].y = 205;
	corner5[2].x = -160; corner5[2].y = 215; corner5[3].x = -168; corner5[3].y = 220;
	corner5[4].x = -175; corner5[4].y = 215;
	polygon5 = polygon_create(corner5,5);
	buttons[20].icon = &polygon5;
	buttons[20].callback = buttonaction_createpolygon;

	// buttons[16].x = -300; buttons[16].y = 200; buttons[16].width = 25; buttons[16].height = 25; buttons[16].color = 0;
	// Point corner[100];
	// corner[0].x = -295; corner[0].y = 205; corner[1].x = -280; corner[1].y = 220;
	// Poly polygon;
	// polygon = polygon_create(corner,2);
	// buttons[16].icon = &polygon;

	// buttons[16].x = -300; buttons[16].y = 200; buttons[16].width = 25; buttons[16].height = 25; buttons[16].color = 0;
	// Point corner[100];
	// corner[0].x = -295; corner[0].y = 205; corner[1].x = -280; corner[1].y = 220;
	// Poly polygon;
	// polygon = polygon_create(corner,2);
	// buttons[16].icon = &polygon;




	// for (int i=0;i<21;i++)
	// 	button_draw(buttons[i]);
}

void refresh_buttons(Button* buttons){
	//printf("helllo");
	for (int i=0;i<21;i++)
		button_draw(buttons[i]);
	//printf("helllo");
}