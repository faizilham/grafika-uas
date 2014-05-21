
void button_draw(){

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