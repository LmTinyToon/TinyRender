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
	TinyRender::Model model("../../Models/AfricanHead.obj");
	TinyRender::Model::vertices_type& vertices = model.vertices();
	for (size_t tr_id = 0; tr_id < model.triangles().size(); ++tr_id)
	{
		for (size_t i = 0; i < 3; ++i)
		{
			const TinyRender::Point& p1 = model.vertices()[model.triangles()[tr_id].vertices[i]];
			const TinyRender::Point& p2 = model.vertices()[model.triangles()[tr_id].vertices[(i + 1) % 3]];
			TinyRender::render_line((p1.x() + 1) * width / 2, 
									(p1.y() + 1) * height / 2, 
									(p2.x() + 1) * width / 2, 
									(p2.y() + 1) * height / 2, tga_image, TinyRender::TGAImage::Pixel(255, 0, 0));
		}
	}
	tga_image << out_tga_file;
	out_tga_file.close();
	return 0;
}