//	Std includes
#include <iostream>
#include <fstream>

//	Local includes
#include "TGAImage.h"
#include "Line.h"
#include "Model.h"

//	Constants/enums
//	Width of image
static const int width = 800;
//	Height of image
static const int height = 800;

int main(void)
{
	std::ofstream out_tga_file("TGATEST.tga", std::ios::binary);
	TinyRender::TGAImage tga_image(width, height, TinyRender::TGAImage::ImageFormat_RGB);
	TinyRender::Model model("../../Models/PyramidModel.txt");
	TinyRender::Model::vertices_type& vertices = model.vertices();
	for (size_t i = 0; i < vertices.size(); i += 9)
	{
		TinyRender::render_line(vertices[i], vertices[i + 1], vertices[i + 3], vertices[i + 4], tga_image, TinyRender::TGAImage::Pixel(255, 0, 0));
		TinyRender::render_line(vertices[i + 3], vertices[i + 4], vertices[i + 6], vertices[i + 7], tga_image, TinyRender::TGAImage::Pixel(255, 0, 0));
		TinyRender::render_line(vertices[i + 6], vertices[i + 7], vertices[i], vertices[i + 1], tga_image, TinyRender::TGAImage::Pixel(255, 0, 0));
	}
	tga_image << out_tga_file;
	out_tga_file.close();
	return 0;
}