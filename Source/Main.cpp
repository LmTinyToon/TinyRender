//	Std includes
#include <iostream>
#include <fstream>

//	Local includes
#include "TGAImage.h"

int main(void)
{
	std::ofstream out_tga_file("TGATEST.tga", std::ios::binary);
	TinyRender::TGAImage tga_image(5, 5, TinyRender::TGAImage::ImageFormat_RGB);
	tga_image.set_pixel(TinyRender::TGAImage::Pixel(255, 0, 0), 0, 0);
	tga_image << out_tga_file;
	out_tga_file.close();
	return 0;
}