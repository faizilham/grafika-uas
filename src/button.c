#include "button.h"

void button_draw(Button button){
	draw_line(button.x,button.y,button.x+button.width,button.y,15);
	draw_line(button.x+button.width,button.y,button.x+button.width,button.y+button.height,15);
	draw_line(button.x+button.width,button.y+button.height,button.x,button.y+button.height,15);
	draw_line(button.x,button.y+button.height,button.x,button.y,15);
	fill(button.x+1,button.y+1,button.color,15);
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

void buttonaction_createcurce(void* args){

}

void buttonaction_createsquare(void* args){

}

void buttonaction_createcircle(void* args){

}

void buttonaction_createpolygon(void* args){

}

void buttonaction_fill(void* args){
	int shape_type = ((int*)args)[0];
	int shape_id = ((int*)args)[1];
	int color = ((int*)args)[2];
}

void init_button(Button* buttons){
	buttons[0].x = 100; buttons[0].y = 210; buttons[0].width = 20; buttons[0].height = 20; buttons[0].color = 0;
	buttons[1].x = 125; buttons[1].y = 210; buttons[1].width = 20; buttons[1].height = 20; buttons[1].color = 1;
	buttons[2].x = 150; buttons[2].y = 210; buttons[2].width = 20; buttons[2].height = 20; buttons[2].color = 2;
	buttons[3].x = 175; buttons[3].y = 210; buttons[3].width = 20; buttons[3].height = 20; buttons[3].color = 3;
	buttons[4].x = 200; buttons[4].y = 210; buttons[4].width = 20; buttons[4].height = 20; buttons[4].color = 4;
	buttons[5].x = 225; buttons[5].y = 210; buttons[5].width = 20; buttons[5].height = 20; buttons[5].color = 5;
	buttons[6].x = 250; buttons[6].y = 210; buttons[6].width = 20; buttons[6].height = 20; buttons[6].color = 6;
	buttons[7].x = 275; buttons[7].y = 210; buttons[7].width = 20; buttons[7].height = 20; buttons[7].color = 7;

	buttons[ 8].x = 100; buttons[ 8].y = 185; buttons[ 8].width = 20; buttons[ 8].height = 20; buttons[ 8].color =  8;
	buttons[ 9].x = 125; buttons[ 9].y = 185; buttons[ 9].width = 20; buttons[ 9].height = 20; buttons[ 9].color =  9;
	buttons[10].x = 150; buttons[10].y = 185; buttons[10].width = 20; buttons[10].height = 20; buttons[10].color = 10;
	buttons[11].x = 175; buttons[11].y = 185; buttons[11].width = 20; buttons[11].height = 20; buttons[11].color = 11;
	buttons[12].x = 200; buttons[12].y = 185; buttons[12].width = 20; buttons[12].height = 20; buttons[12].color = 12;
	buttons[13].x = 225; buttons[13].y = 185; buttons[13].width = 20; buttons[13].height = 20; buttons[13].color = 13;
	buttons[14].x = 250; buttons[14].y = 185; buttons[14].width = 20; buttons[14].height = 20; buttons[14].color = 14;
	buttons[15].x = 275; buttons[15].y = 185; buttons[15].width = 20; buttons[15].height = 20; buttons[15].color = 15;
	for (int i=0;i<16;i++)
		button_draw(buttons[i]);
}