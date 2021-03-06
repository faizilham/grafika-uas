#include "button.h"
#include <math.h>
#include "export.h"

extern Line l[100];
extern int nl;
extern Rect r[100];
extern int nr;
extern Poly p[100];
extern int np;
extern Circ ci[100];
extern int nci;
extern Curve cu[100];
extern int ncu;
extern int current_type_shape;
extern int current_i;

extern Point *current_min, *current_max;

extern char msg[100];


void button_draw(Button button){
	draw_line(button.x,button.y,button.x+button.width,button.y,button.border);
	draw_line(button.x+button.width,button.y,button.x+button.width,button.y+button.height,button.border);
	draw_line(button.x+button.width,button.y+button.height,button.x,button.y+button.height,button.border);
	draw_line(button.x,button.y+button.height,button.x,button.y,button.border);
	fill(button.x+1,button.y+1,button.color,button.border);
	//if (button.icon != NULL){
		//button.icon->color = button.border;
		//polygon_draw(button.icon);
	//}
	
	shape_setColor(&button.icon, button.border);
	shape_draw(&button.icon);
}

bool button_checkcollision(Button button,int x,int y){
	return (button.x < x) && (x < button.x+button.width) && (button.y < y) && (y < button.y+button.width);
}


void buttonaction_scaleup(void* args){
	if (current_type_shape == 0){
		line_scale(&l[current_i],1.1);
	}
	else if (current_type_shape == 1){
		curve_scale(&cu[current_i],1.1);
	}
	else if (current_type_shape == 2){
		rect_scale(&r[current_i],1.1);
	}
	else if (current_type_shape == 3){
		circ_scale(&ci[current_i],1.1);
	}
	else if (current_type_shape == 4){
		polygon_scale(&p[current_i], 1.1);
	}
}

void buttonaction_scaledown(void* args){
	float scale = 10;
	scale/=11;
	if (current_type_shape == 0){
		line_scale(&l[current_i],scale);
	}
	else if (current_type_shape == 1){
		curve_scale(&cu[current_i],scale);
	}
	else if (current_type_shape == 2){
		rect_scale(&r[current_i],scale);
	}
	else if (current_type_shape == 3){
		circ_scale(&ci[current_i],scale);
	}
	else if (current_type_shape == 4){
		polygon_scale(&p[current_i],scale);
	}
}

void buttonaction_rotateleft(void* args){
	if (current_type_shape == 0){
		line_rotate(&l[current_i],-15);
	}
	else if (current_type_shape == 1){
		curve_rotate(&cu[current_i],-15);
	}
	else if (current_type_shape == 2){
		rect_rotate(&r[current_i],-15);
	}
	else if (current_type_shape == 3){
		// do nothing
	}
	else if (current_type_shape == 4){
		polygon_rotate(&p[current_i], -15);
	}
}

void buttonaction_rotateright(void* args){
	if (current_type_shape == 0){
		line_rotate(&l[current_i],15);
	}
	else if (current_type_shape == 1){
		curve_rotate(&cu[current_i],15);
	}
	else if (current_type_shape == 2){
		rect_rotate(&r[current_i],15);
	}
	else if (current_type_shape == 3){
		//Do nothing
	}
	else if (current_type_shape == 4){
		polygon_rotate(&p[current_i], 15);
	}
}

void buttonaction_forward(void* args){
	if (current_type_shape == 0){
		l[current_i].z++;
	}
	else if (current_type_shape == 1){
		cu[current_i].z++;
	}
	else if (current_type_shape == 2){
		r[current_i].z++;
	}
	else if (current_type_shape == 3){
		ci[current_i].z++;
	}
	else if (current_type_shape == 4){
		p[current_i].z++;
	}
}

void buttonaction_backward(void* args){
	if (current_type_shape == 0){
		l[current_i].z--;
	}
	else if (current_type_shape == 1){
		cu[current_i].z--;
	}
	else if (current_type_shape == 2){
		r[current_i].z--;
	}
	else if (current_type_shape == 3){
		ci[current_i].z--;
	}
	else if (current_type_shape == 4){
		p[current_i].z--;
	}
}

void buttonaction_createline(void* args){
	mevent_t e;
	
	do {
		delay(100);
		get_mouse_event(&e);
		
		if (e.button & MOUSE_RIGHT)
			return;
		
	} while (!(e.button & MOUSE_LEFT));
	
	int x1 = e.x;
	int y1 = e.y;
	
	paintpix(x1, y1, 15);
	bool onceUp = false;
	
	do {
		delay(100);
		get_mouse_event(&e);
		if (e.button == MOUSE_NONE){
			onceUp = true;
		}
	} while (!(e.button & MOUSE_LEFT) || !onceUp );
	
	
	int x2 = e.x;
	int y2 = e.y;
	l[nl] = line_create(x1, y1, x2, y2);
	line_draw(&l[nl]);
	
	
	current_type_shape = 0;
	current_i = nl;
	current_min = &l[current_i].min;
	current_max = &l[current_i].max;
	
	nl++;
}

void buttonaction_createcurve(void* args){
	mevent_t e;
	Point points[4];
	int n = 0;
	
	bool onceUp = false;
	
	do {
		delay(100);
		get_mouse_event(&e);
		if (onceUp && (e.button & MOUSE_LEFT)){
			points[n].x = e.x;
			points[n].y = e.y;
			n++;
			
			paintpix(e.x, e.y, 15);
			onceUp = false;
		}else if (e.button == MOUSE_NONE){
			onceUp = true;
		}else if (e.button & MOUSE_RIGHT){
			return;
		}
	} while (n < 4);
	
	for (int i = 0; i < 4; i++){
		paintpix(points[i].x, points[i].y, 0);
	}
	
	cu[ncu] = curve_create(points);
	curve_draw(&cu[ncu]);
	
	current_type_shape = 1;
	current_i = ncu;
	current_min = &cu[current_i].min;
	current_max = &cu[current_i].max;
	
	ncu++;
	// belom ada fungsi penambahan ke array
}

void buttonaction_createsquare(void* args){
	mevent_t e;
	do {
		delay(100);
		get_mouse_event(&e);
		
		if (e.button & MOUSE_RIGHT)
			return;
		
	} while (!(e.button & MOUSE_LEFT));
	
	int x1 = e.x;
	int y1 = e.y;
	
	bool onceUp = false;
	
	paintpix(x1, y1, 15);
	
	do {
		delay(100);
		get_mouse_event(&e);
		
		if (e.button == MOUSE_NONE){
			onceUp = true;
		}
	} while (!(e.button & MOUSE_LEFT) || !onceUp );
	
	int x2 = e.x;
	int y2 = e.y;
	r[nr] = rect_create(x1, y1, x2, y2);
	rect_draw(&r[nr]);
	
	current_type_shape = 2;
	current_i = nr;
	current_min = &r[current_i].min;
	current_max = &r[current_i].max;
	
	nr++;
	
}

void buttonaction_createcircle(void* args){
	mevent_t e;
	do {
		delay(100);
		get_mouse_event(&e);
		
		if (e.button & MOUSE_RIGHT)
			return;
		
	} while (!(e.button & MOUSE_LEFT));
	
	int x1 = e.x;
	int y1 = e.y;
	
	bool onceUp = false;
	
	paintpix(x1, y1, 15); // mark center
	
	do {
		delay(100);
		get_mouse_event(&e);
		
		if (e.button == MOUSE_NONE){
			onceUp = true;
		}
	} while (!(e.button & MOUSE_LEFT) || !onceUp );
	
	paintpix(x1, y1, 0); // demark center
	
	int x2 = e.x;
	int y2 = e.y;
	
	float r = sqrt(pow(x1-x2,2) + pow(y1-y2,2));
	
	
	ci[nci] = circ_create(x1, y1, r);
	circ_draw(&ci[nci]);
	
	current_type_shape = 3;
	current_i = nci;
	current_min = &ci[current_i].min;
	current_max = &ci[current_i].max;
	
	nci++;
}

void buttonaction_createpolygon(void* args){
	mevent_t e;
	Point corner[100];
	int i = 0;
	
	bool onceUp = false;
	
	do {
		delay(100);
		get_mouse_event(&e);
		if (onceUp && (e.button & MOUSE_LEFT)){
			corner[i].x = e.x;
			corner[i].y = e.y;
			i++;
			
			paintpix(e.x, e.y, 15); // mark
			onceUp = false;
		}else if (e.button == MOUSE_NONE){
			onceUp = true;
		}
		
	} while (!(e.button & MOUSE_RIGHT));
	
	if (i < 3){
		for (int j = 0; j < i; ++j){
			paintpix(corner[j].x,corner[j].y, 0); // demark
		}
	
		return;
	}
	
	p[np] = polygon_create(corner,i);
	//outtextxy(100,100,"ok");
	polygon_draw(&p[np]);
	
	current_type_shape = 4;
	current_i = np;
	current_min = &p[current_i].min;
	current_max = &p[current_i].max;
	
	np++;
}

void buttonaction_export(void* args){
	export_canvas();
	strcpy(msg,"File gambar berhasil terbentuk!");
}

void buttonaction_load(void* args){
	printf("buttonaction_load\n");
	FILE* file = fopen ("tmp.txt", "r");
	int nline, ncurve, nrect, ncircle, npoly;
  	fscanf (file, "%d %d %d %d %d", &nline, &ncurve, &nrect, &ncircle, &npoly);
  	for (int i=0;i<nline;i++){
  		int x1,y1,x2,y2;
  		fscanf(file, "%d %d %d %d", &x1, &y1, &x2, &y2);
  		l[i] = line_create(x1,y1,x2,y2);
  		int z;
  		fscanf(file, "%d", &z);
  		l[i].z = z;
  	}
  	nl = nline;
  	for (int i=0;i<ncurve;i++){
  		Point corner[4];
  		for (int j=0;j<4;j++){
  			int x,y;
  			fscanf(file, "%d %d", &x,&y);
  			corner[j].x = x;
  			corner[j].y = y;
  		}
  		cu[i] = curve_create(corner);
  		int z;
  		fscanf(file, "%d", &z);
  		cu[i].z = z;
  	}
  	ncu = ncurve;
  	for (int i=0;i<nrect;i++){
  		int x1,y1,x2,y2;
  		fscanf(file, "%d %d %d %d", &x1, &y1, &x2, &y2);
  		r[i] = rect_create(x1,y1,x2,y2);
  		int z,fill;
  		fscanf(file, "%d %d", &z, &fill);
  		r[i].z = z;
  		r[i].fill = fill;
  	}
  	nr = nrect;
  	for (int i=0;i<ncircle;i++){
  		int x,y,r;
  		fscanf(file, "%d %d %d", &x, &y, &r);
  		ci[i] = circ_create(x,y,r);
  		int z,fill;
  		fscanf(file, "%d %d", &z, &fill);
  		ci[i].z = z;
  		ci[i].fill = fill;
  	}
  	nci = ncircle;
  	for (int i=0;i<npoly;i++){
  		int length;
  		fscanf(file, "%d", &length);
  		Point corner[100];
  		for (int j=0;j<length;j++){
  			int x,y;
  			fscanf(file, "%d %d", &x, &y);
  			corner[j].x = x;
  			corner[j].y = y;
  		}
  		p[i] = polygon_create(corner,length);
  		int z,fill;
  		fscanf(file, "%d %d", &z, &fill);
  		p[i].z = z;
  		p[i].fill = fill;
  	}
  	np = npoly;
  	printf("buttonaction_load2\n");
  	strcpy(msg,"File berhasil termuat!");
  	fclose (file); 
}

void buttonaction_save(void* args){

	FILE * pFile;
  	pFile = fopen ("tmp.txt","w");
  	if (pFile!=NULL)
  	{

  		fprintf (pFile, "%d %d %d %d %d\n", nl, ncu, nr, nci, np);
    	for (int i=0;i<nl;i++){
	  		fprintf(pFile, "%.f %.f %.f %.f\n", l[i].p1.x, l[i].p1.y, l[i].p2.x, l[i].p2.y);
	  		fprintf(pFile, "%d\n",l[i].z);
	  	}
	  	for (int i=0;i<ncu;i++){
	  		for (int j=0;j<4;j++){
	  			fprintf(pFile, "%.f %.f\n", cu[i].points[j].x,cu[i].points[j].y);
	  		}
	  		fprintf(pFile, "%d\n",cu[i].z);
	  	}
	  	for (int i=0;i<nr;i++){
	  		//printf("%d %d %d %d\n", r[i].corner[0].x, r[i].corner[0].y, r[i].corner[2].x, r[i].corner[2].y);
	  		fprintf(pFile, "%.f %.f %.f %.f\n", r[i].corner[0].x, r[i].corner[0].y, r[i].corner[2].x, r[i].corner[2].y);
	  		fprintf(pFile, "%d %d\n",r[i].z, r[i].fill);
	  	}
	  	for (int i=0;i<nci;i++){
	  		fprintf(pFile, "%.f %.f %.f\n", ci[i].center.x, ci[i].center.y, ci[i].radius);
	  		fprintf(pFile, "%d %d\n",ci[i].z, ci[i].fill);
	  	}
	  	for (int i=0;i<np;i++){
	  		fprintf(pFile, "%d\n", p[i].neff);
	  		for (int j=0;j<p[i].neff;j++){
	  			fprintf(pFile, "%.f %.f\n", p[i].corner[j].x, p[i].corner[j].y);
	  		}
	  		fprintf(pFile, "%d %d\n",p[i].z, p[i].fill);
	  	}
	  	//outtextxy(0,0,"buttonaction_save");
    	fclose (pFile);
    	strcpy(msg,"File berhasil tersimpan!");
  	}

}

void buttonaction_fill(void* args){
	int shape_type = ((int*)args)[0];
	int shape_id = ((int*)args)[1];
	int color = ((int*)args)[2];
}

Poly polygon,polygon3,polygon5;
Poly polygon6,polygon7,polygon8,polygon9,polygon10,polygon11;

Curve curv_icon;
Circ circ_icon;

int nbutton;

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
	
	for (int i = 0; i < nbutton; i++){
		buttons[i].icon.type = -1;
	}
	
	// line button
	buttons[16].x = -300; buttons[16].y = 200; buttons[16].width = 25; buttons[16].height = 25; buttons[16].color = 0;
	Point corner[30];
	corner[0].x = -295; corner[0].y = 205; corner[1].x = -280; corner[1].y = 220;
	polygon = polygon_create(corner,2);
	//buttons[16].icon = &polygon;
	shape_setObject(&buttons[16].icon, TYPE_POLYGON, &polygon);
	buttons[16].callback = buttonaction_createline;
	
	// curve button
	
	buttons[17].x = -270; buttons[17].y = 200; buttons[17].width = 25; buttons[17].height = 25; buttons[17].color = 0;

	Point corner2[4];
	corner2[0].x = -265; corner2[0].y = 205; corner2[1].x = -265; corner2[1].y = 212; corner2[2].x = -257; corner2[2].y = 220; corner2[3].x = -250; corner2[3].y = 220;
	curv_icon = curve_create(corner2);
	//buttons[17].icon = &polygon2;
	shape_setObject(&buttons[17].icon, TYPE_CURVE, &curv_icon);

	buttons[17].callback = buttonaction_createcurve;
	
	// rect button
	
	buttons[18].x = -240; buttons[18].y = 200; buttons[18].width = 25; buttons[18].height = 25; buttons[18].color = 0;
	Point corner3[30];
	corner3[0].x = -235; corner3[0].y = 205; corner3[1].x = -235; corner3[1].y = 220;
	corner3[2].x = -220; corner3[2].y = 220; corner3[3].x = -220; corner3[3].y = 205;
	polygon3 = polygon_create(corner3,4);
	//buttons[18].icon = &polygon3;
	shape_setObject(&buttons[18].icon, TYPE_POLYGON, &polygon3);
	buttons[18].callback = buttonaction_createsquare;
	
	// circ button

	buttons[19].x = -210; buttons[19].y = 200; buttons[19].width = 25; buttons[19].height = 25; buttons[19].color = 0;	
	circ_icon = circ_create(-197, 212, 7);
	//buttons[19].icon = &polygon4;
	shape_setObject(&buttons[19].icon, TYPE_CIRCLE, &circ_icon);

	buttons[19].callback = buttonaction_createcircle;
	
	// poly button

	buttons[20].x = -180; buttons[20].y = 200; buttons[20].width = 25; buttons[20].height = 25; buttons[20].color = 0;
	Point corner5[30];
	corner5[0].x = -172; corner5[0].y = 205; corner5[1].x = -163; corner5[1].y = 205;
	corner5[2].x = -160; corner5[2].y = 215; corner5[3].x = -168; corner5[3].y = 220;
	corner5[4].x = -175; corner5[4].y = 215;
	polygon5 = polygon_create(corner5,5);
	//buttons[20].icon = &polygon5;
	shape_setObject(&buttons[20].icon, TYPE_POLYGON, &polygon5);
	buttons[20].callback = buttonaction_createpolygon;
	
	// rotate + button
	
	buttons[21].x = -80; buttons[21].y = 200; buttons[21].width = 20; buttons[21].height = 20; buttons[21].color = 0;
	Point corner6[30];
	corner6[0].x = -70; corner6[0].y = 210; corner6[1].x = -70; corner6[1].y = 215; corner6[2].x = -70; corner6[2].y = 205;
	corner6[3].x = -70; corner6[3].y = 210; corner6[4].x = -65; corner6[4].y = 210; corner6[5].x = -75; corner6[5].y = 210;
	polygon6 = polygon_create(corner6,6);

	shape_setObject(&buttons[21].icon, TYPE_POLYGON, &polygon6);
	// rotate - button

	buttons[21].callback = buttonaction_rotateright;


	buttons[22].x = -55; buttons[22].y = 200; buttons[22].width = 20; buttons[22].height = 20; buttons[22].color = 0;
	Point corner7[30];
	corner7[0].x = -50; corner7[0].y = 210; corner7[1].x = -40; corner7[1].y = 210;
	polygon7 = polygon_create(corner7,2);

	//buttons[22].icon = &polygon7;
	shape_setObject(&buttons[22].icon, TYPE_POLYGON, &polygon7);

	buttons[22].callback = buttonaction_rotateleft;


	// scale + button

	buttons[23].x = -25; buttons[23].y = 200; buttons[23].width = 20; buttons[23].height = 20; buttons[23].color = 0;
	Point corner8[30];
	corner8[0].x = -15; corner8[0].y = 210; corner8[1].x = -15; corner8[1].y = 215; corner8[2].x = -15; corner8[2].y = 205;
	corner8[3].x = -15; corner8[3].y = 210; corner8[4].x = -10; corner8[4].y = 210; corner8[5].x = -20; corner8[5].y = 210;
	polygon8 = polygon_create(corner8,6);

	//buttons[23].icon = &polygon8;
	shape_setObject(&buttons[23].icon, TYPE_POLYGON, &polygon8);

	buttons[23].callback = buttonaction_scaleup;


	// scale - button
	
	buttons[24].x = 0; buttons[24].y = 200; buttons[24].width = 20; buttons[24].height = 20; buttons[24].color = 0;
	Point corner9[30];
	corner9[0].x = 5; corner9[0].y = 210; corner9[1].x = 15; corner9[1].y = 210;
	polygon9 = polygon_create(corner9,2);

	shape_setObject(&buttons[24].icon, TYPE_POLYGON, &polygon9);

	buttons[24].callback = buttonaction_scaledown;


	// order + button
	
	buttons[25].x = 30; buttons[25].y = 200; buttons[25].width = 20; buttons[25].height = 20; buttons[25].color = 0;
	Point corner10[30];
	corner10[0].x = 40; corner10[0].y = 210; corner10[1].x = 40; corner10[1].y = 215; corner10[2].x = 40; corner10[2].y = 205;
	corner10[3].x = 40; corner10[3].y = 210; corner10[4].x = 45; corner10[4].y = 210; corner10[5].x = 35; corner10[5].y = 210;
	polygon10 = polygon_create(corner10,6);
	//buttons[25].icon = &polygon10;
	shape_setObject(&buttons[25].icon, TYPE_POLYGON, &polygon10);
	buttons[25].callback = buttonaction_forward;
	

	// order - button
	
	buttons[26].x = 55; buttons[26].y = 200; buttons[26].width = 20; buttons[26].height = 20; buttons[26].color = 0;
	Point corner11[30];
	corner11[0].x = 60; corner11[0].y = 210; corner11[1].x = 70; corner11[1].y = 210;
	polygon11 = polygon_create(corner11,2);
	//buttons[26].icon = &polygon11;
	shape_setObject(&buttons[26].icon, TYPE_POLYGON, &polygon11);
	buttons[26].callback = buttonaction_backward;

	buttons[27].x = -142; buttons[27].y = 213; buttons[27].width = 50; buttons[27].height = 18; buttons[27].color = 0;
	buttons[27].callback = buttonaction_load;

	buttons[28].x = -142; buttons[28].y = 190; buttons[28].width = 50; buttons[28].height = 18; buttons[28].color = 0;
	buttons[28].callback = buttonaction_save;

	buttons[29].x = -142; buttons[29].y = 167; buttons[29].width = 50; buttons[29].height = 18; buttons[29].color = 0;
	buttons[29].callback = buttonaction_export;

	nbutton = 30;
	for (int i = 0; i < nbutton; ++i){
		buttons[i].border = 15;
	}
	setcolor(WHITE);
	
	//refresh_buttons(buttons);
	
	/*outtextxy(22,65,"canvas");
	outtextxy(475,60,"color picker");
	outtextxy(25,45,"ln");
	outtextxy(51,45,"crv");
	outtextxy(82,45,"rec");
	outtextxy(111,45,"cir");
	outtextxy(140,45,"poly");
	outtextxy(242,45,"rotate");
	outtextxy(303,45,"zoom");
	outtextxy(353,45,"orde-z");
	outtextxy(188,13,"load");
	outtextxy(188,36,"save");
	outtextxy(183,59,"export");*/
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
	for (int i=0;i<nbutton;i++)
		button_draw(buttons[i]);
	setcolor(WHITE);
	outtextxy(22,65,"canvas");
	outtextxy(475,60,"color picker");
	outtextxy(25,45,"ln");
	outtextxy(51,45,"crv");
	outtextxy(82,45,"rec");
	outtextxy(111,45,"cir");
	outtextxy(140,45,"poly");
	outtextxy(242,45,"rotate");
	outtextxy(297,45,"resize");
	outtextxy(349,45,"order-z");
	outtextxy(188,13,"load");
	outtextxy(188,36,"save");
	outtextxy(183,59,"export");
	//printf("helllo");
}

