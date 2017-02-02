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
	const TinyRender::Point light_vec(1.0, 0.0, 0.0, 0.0);
	std::ofstream out_tga_file("TGATEST.tga", std::ios::binary);
	TinyRender::TGAImage tga_image(width, height, TinyRender::TGAImage::ImageFormat_RGB);
	TinyRender::Model model("../../Models/AfricanHead.obj");
	for (size_t tr_id = 0; tr_id < model.triangles().size(); ++tr_id)
	{
		const TinyRender::Point& p1 = model.vertices()[model.triangles()[tr_id].vertices[0]];
		const TinyRender::Point& p2 = model.vertices()[model.triangles()[tr_id].vertices[1]];
		const TinyRender::Point& p3 = model.vertices()[model.triangles()[tr_id].vertices[2]];

		TinyRender::Point norm_vec = (p2 - p1) ^ (p3 - p1);
		norm_vec.normalize();
		const float intense = light_vec * norm_vec;
		if (intense > 0)
		{
			TinyRender::render_triangle(p1.x(), p1.y(), p2.x(), p2.y(), p3.x(), p3.y(), tga_image, 
				TinyRender::TGAImage::Pixel(255 * intense, 255 * intense, 255 * intense));
		}
	}
	tga_image << out_tga_file;
	out_tga_file.close();
	return 0;
}