//	Std includes
#include <iostream>
#include <fstream>

//	Local includes
#include "TGAImage.h"

int main(void)
{
	std::ofstream out_tga_file("TGATEST.tga", std::ios::binary);
	TinyRender::TGAImage(5, 5, TinyRender::TGAImage::ImageFormat_RGB) << out_tga_file;
	out_tga_file.close();
	return 0;
}