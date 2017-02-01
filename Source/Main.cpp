//	Std includes
#include <iostream>
#include <fstream>

//	Local includes
#include "TGAImage.h"
#include "Line.h"
#include "Triangle.h"
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
	TinyRender::Model model("../../Models/PyramidModel.obj");
	TinyRender::Model::vertices_type& vertices = model.vertices();
	for (size_t i = 0; i < vertices.size(); i += 3)
	{
		//	TODO: (alex) fix extra conversion
		TinyRender::render_triangle(vertices[i].x(), vertices[i].y(), 
									vertices[i + 1].x(), vertices[i + 1].y(), 
									vertices[i + 2].x(), vertices[i + 2].y(), tga_image, TinyRender::TGAImage::Pixel(255, 0, 0));
	}
	tga_image << out_tga_file;
	out_tga_file.close();
	return 0;
}