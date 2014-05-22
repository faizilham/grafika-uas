#include "export.h"

//0 = red, 1 = green, 2 = blue
unsigned char converttorgb(int pixel, int comp){
	if(pixel == 0){
		if(comp == 0)
			return (unsigned char) 0;
		if(comp == 1)
			return (unsigned char) 0;
		if(comp == 2)
			return (unsigned char) 0;
	}
	if(pixel == 1){
		if(comp == 0)
			return (unsigned char) 0;
		if(comp == 1)
			return (unsigned char) 0;
		if(comp == 2)
			return (unsigned char) 255;
	}
	if(pixel == 2){
		if(comp == 0)
			return (unsigned char) 0;
		if(comp == 1)
			return (unsigned char) 128;
		if(comp == 2)
			return (unsigned char) 0;
	}
	if(pixel == 3){
		if(comp == 0)
			return (unsigned char) 0;
		if(comp == 1)
			return (unsigned char) 255;
		if(comp == 2)
			return (unsigned char) 255;
	}
	if(pixel == 4){
		if(comp == 0)
			return (unsigned char) 0;
		if(comp == 1)
			return (unsigned char) 0;
		if(comp == 2)
			return (unsigned char) 0;
	}
	if(pixel == 5){
		if(comp == 0)
			return (unsigned char) 255;
		if(comp == 1)
			return (unsigned char) 0;
		if(comp == 2)
			return (unsigned char) 0;
	}
	if(pixel == 6){
		if(comp == 0)
			return (unsigned char) 165;
		if(comp == 1)
			return (unsigned char) 42;
		if(comp == 2)
			return (unsigned char) 42;
	}
	if(pixel == 7){
		if(comp == 0)
			return (unsigned char) 211;
		if(comp == 1)
			return (unsigned char) 211;
		if(comp == 2)
			return (unsigned char) 211;
	}
	if(pixel == 8){
		if(comp == 0)
			return (unsigned char) 169;
		if(comp == 1)
			return (unsigned char) 169;
		if(comp == 2)
			return (unsigned char) 169;
	}
	if(pixel == 9){
		if(comp == 0)
			return (unsigned char) 173;
		if(comp == 1)
			return (unsigned char) 216;
		if(comp == 2)
			return (unsigned char) 230;
	}
	if(pixel == 10){
		if(comp == 0)
			return (unsigned char) 144;
		if(comp == 1)
			return (unsigned char) 238;
		if(comp == 2)
			return (unsigned char) 144;
	}
	if(pixel == 11){
		if(comp == 0)
			return (unsigned char) 224;
		if(comp == 1)
			return (unsigned char) 255;
		if(comp == 2)
			return (unsigned char) 255;
	}
	if(pixel == 12){
		if(comp == 0)
			return (unsigned char) 255;
		if(comp == 1)
			return (unsigned char) 69;
		if(comp == 2)
			return (unsigned char) 0;
	}
	if(pixel == 13){
		if(comp == 0)
			return (unsigned char) 255;
		if(comp == 1)
			return (unsigned char) 0;
		if(comp == 2)
			return (unsigned char) 255;
	}
	if(pixel == 14){
		if(comp == 0)
			return (unsigned char) 255;
		if(comp == 1)
			return (unsigned char) 255;
		if(comp == 2)
			return (unsigned char) 0;
	}
	if(pixel == 15){
		if(comp == 0)
			return (unsigned char) 255;
		if(comp == 1)
			return (unsigned char) 255;
		if(comp == 2)
			return (unsigned char) 255;
	}
}

void export_canvas(){
    // Image properties
    int x, y, w = 596, h = 370;
    unsigned char p[h][w][3];
 
    // Bitmap structures to be written to file
    BITMAPFILEHEADER bfh;
    BITMAPINFOHEADER bih;
 
    // Fill BITMAPFILEHEADER structure
    memcpy((char *)&bfh.bfType, "BM", 2);
    bfh.bfSize = sizeof(bfh) + sizeof(bih) + 3*h*w;
    bfh.bfReserved1 = 0;
    bfh.bfReserved2 = 0;
    bfh.bfOffBits = sizeof(bfh) + sizeof(bih);
 
    // Fill BITMAPINFOHEADER structure
    bih.biSize = sizeof(bih);
    bih.biWidth = w;
    bih.biHeight = h;
    bih.biPlanes = 1;
    bih.biBitCount = 24;
    bih.biCompression = BI_RGB; // uncompressed 24-bit RGB
    bih.biSizeImage = 0; // can be zero for BI_RGB bitmaps
    bih.biXPelsPerMeter = 3780; // 96dpi equivalent
    bih.biYPelsPerMeter = 3780;
    bih.biClrUsed = 0;
    bih.biClrImportant = 0;
	
    // Generate pixel data
    for (y=0 ; y<h ; ++y)
    {
        for (x=0 ; x<w ; ++x)
        {
			int pixel = cgetpixel(x-w/2-2,h-y-h/2-25);
            p[y][x][0] = converttorgb(pixel, 0);//255 * (y/(double)h);
            p[y][x][1] = converttorgb(pixel, 1);//255 * (x/(double)w);
            p[y][x][2] = converttorgb(pixel, 2);//0;
        }
    }
 
    // Open bitmap file (binary mode)
    FILE *f;
    f = fopen("export.bmp", "wb");
 
    // Write bitmap file header
    fwrite(&bfh, 1, sizeof(bfh), f);
    fwrite(&bih, 1, sizeof(bih), f);
 
    // Write bitmap pixel data starting with the
    // bottom line of pixels, left hand side
    for (y=h-1 ; y>=0 ; --y)
    {
        for (x=0 ; x<w ; ++x)
        {
            // Write pixel components in BGR order
            fputc(p[y][x][2], f);
            fputc(p[y][x][1], f);
            fputc(p[y][x][0], f);
        }
    }
 
    // Close bitmap file
    fclose(f);
}