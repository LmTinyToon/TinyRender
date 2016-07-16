//	Std includes
#include <iostream>
#include <fstream>

//	Local includes
#include "TGAImage.h"
#include "Line.h"

//	Constants/enums
//	Width of image
static const int width = 800;
//	Height of image
static const int height = 800;

int main(void)
{
	std::ofstream out_tga_file("TGATEST.tga", std::ios::binary);
	TinyRender::TGAImage tga_image(width, height, TinyRender::TGAImage::ImageFormat_RGB);
	TinyRender::render_line(0, 0, width, height, tga_image, TinyRender::TGAImage::Pixel(255, 0, 0));
	tga_image << out_tga_file;
	out_tga_file.close();
	return 0;
}