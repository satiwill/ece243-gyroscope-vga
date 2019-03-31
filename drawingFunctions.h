//these functions use plot_pixel to draw things to the back buffer. use wait_for_vsync to swap the buffer address you are writting to.

void draw_line(int x0, int x1, int y0, int y1, short int color);
void plot_pixel(int x, int y, short int line_color);
void clear_screen();
void drawBox(int xLeft, int yTop, int width, int height, short int color_Xs);
void wait_for_vsync(volatile int* pixelStatusPtr, volatile int* pixel_ctrl_ptr);