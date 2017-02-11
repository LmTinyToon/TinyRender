//	Std includes
#include <iostream>
#include <fstream>

//	Local includes
#include "TGAImage.h"
#include "Line.h"
#include "Triangle.h"
#include "Model.h"
#include "EngineManager.h"

//	Constants/enums
//	Width of image
static const int width = 800;
//	Height of image
static const int height = 800;

int main(void)
{
	//	Engine initialization
	TinyRender::EngineManager engine;
	engine.set_viewport(0, 0, width, height);
	engine.set_depth(width);

	std::vector<std::vector<int>> z_buffer(height, std::vector<int>(width, std::numeric_limits<int>::min()));
	const TinyRender::Point light_vec(0.0, 0.0, -1.0, 0.0);
	const TinyRender::TGAImage::Pixel pixel(255, 255, 255);
	TinyRender::TGAImage tga_image(width, height, TinyRender::TGAImage::ImageFormat_RGB);
	TinyRender::Model model("../../Models/AfricanHead.obj");
	TinyRender::TGAImage text_map("../../Models/AfricanHeadDiffuse.tga");
	std::ofstream out_tga_file("../../Temp/TGATEST.tga", std::ios::binary);
	
	for (size_t tr_id = 0; tr_id < model.triangles().size(); ++tr_id)
	{
		const TinyRender::Point& p1 = model.vertices()[model.triangles()[tr_id].vertices[0]];
		const TinyRender::Point& uv1 = model.uv_vertices()[model.triangles()[tr_id].uv_vertices[0]];
		const TinyRender::Point& p2 = model.vertices()[model.triangles()[tr_id].vertices[1]];
		const TinyRender::Point& uv2 = model.uv_vertices()[model.triangles()[tr_id].uv_vertices[1]];
		const TinyRender::Point& p3 = model.vertices()[model.triangles()[tr_id].vertices[2]];
		const TinyRender::Point& uv3 = model.uv_vertices()[model.triangles()[tr_id].uv_vertices[2]];

		const float p1x = (p1.x() + 1) * width / 2;
		const float p1y = (p1.y() + 1) * height / 2;
		const float p1z = (p1.z() + 1) * width;;
		const float u1x  = (uv1.x()) * text_map.width();
		const float u1y =  (uv1.y()) * text_map.height();

		const float p2x = (p2.x() + 1) * width / 2;
		const float p2y = (p2.y() + 1) * height / 2;
		const float p2z = (p2.z() + 1) * width;
		const float u2x = (uv2.x()) * text_map.width();
		const float u2y = (uv2.y()) * text_map.height();

		const float p3x = (p3.x() + 1) * width / 2;
		const float p3y = (p3.y() + 1) * height / 2;
		const float p3z = (p3.z() + 1) * width;
		const float u3x = (uv3.x()) * text_map.width();
		const float u3y = (uv3.y()) * text_map.height();

		TinyRender::Point norm_vec = (p3 - p1) ^ (p2 - p1);
		norm_vec.normalize();
		const float intense = light_vec * norm_vec;
		if (intense > 0)
		{
			TinyRender::render_triangle(p1x, p1y, p1z, u1x, u1y, 
										p2x, p2y, p2z, u2x, u2y,
										p3x, p3y, p3z, u3x, u3y,
										tga_image, text_map, 
										z_buffer, pixel.mult(intense), intense);
		}
	}
	tga_image << out_tga_file;
	out_tga_file.close();
	return 0;
}