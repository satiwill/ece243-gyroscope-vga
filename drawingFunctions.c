#include "constants.h"
#include "address_map_arm.h"
#include "externalVariables.h"


void plot_pixel(int x, int y, short int line_color)
{
    *(short int *)(pixel_buffer_start + (y << 10) + (x << 1)) = line_color;
}


void wait_for_vsync(volatile int* pixelStatusPtr, volatile int* pixel_ctrl_ptr){
	*pixel_ctrl_ptr = 1; //initializ the S bit
	while ((*pixelStatusPtr&1)!=0){//don't draw the next thing until the whole screen has been drawn
			;
		}
}

void draw_line(int x0, int x1, int y0, int y1, short int color){
	int absy = y1-y0;
	int absx = x1-x0;
	if(absy < 0){
		absy = absy*(-1);
	}
	if(absx < 0){
		absx = absx*(-1);
	}

	int isSteep = absy > absx;
	int swap = 0;
	
	if (isSteep){
		swap = x0;
		x0 = y0;
		y0 = swap;
		
		swap = x1;
		x1 = y1;
		y1 = swap;
	}
	
	if (x1 < x0){
		swap = x0;
		x0 = x1;
		x1 = swap; 
		
		swap = y0;
		y0 = y1;
		y1 = swap;
	}

	int deltaX = x1 - x0;
	int deltaY = y1 - y0;
	int yStep = 1;
	
	if(deltaY < 0){
		deltaY = deltaY*(-1);
		yStep = -1;
	}
	
	int error = -(deltaX/2);
	
	int y = y0;
	int x = x0;
	for (;  x <= x1 ; x++ ){
		
		if(isSteep){
			plot_pixel(y,x,color);
		}else{
			plot_pixel(x,y,color);
		}
		
		error = error + deltaY;
		
		if(error >= 0){
			y = y + yStep;
			error = error - deltaX;
		}
	}
}

void clear_screen(){
	int x = 0;
	int y = 0;
	
	for( ; x < 320 ; x++){
		y = 0;
		for( ; y < 240 ; y++ ){
			plot_pixel(x,y,0);
		}
		
	}
}

void drawBox(int xLeft, int yTop, int width, int height, short int color_Xs){
	int i = 0;
	for(; i<width ; i++){
		
		int j = 0;
		for(; j < height ; j++){
			plot_pixel(xLeft+i,yTop+j, color_Xs);
		}
		
	}
}