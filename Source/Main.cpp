//	Std includes
#include <iostream>
#include <fstream>
#include <memory>

//	Local includes
#include "TGAImage.h"
#include "Line.h"
#include "Triangle.h"
#include "Model.h"
#include "EngineManager.h"
#include "Shaders.h"

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
	//	Shader creation
	std::unique_ptr<TinyRender::Shader> shader = std::make_unique<TinyRender::DummyShader>(engine);

	std::vector<std::vector<int>> z_buffer(height, std::vector<int>(width, std::numeric_limits<int>::min()));
	TinyRender::Vec3f light_vec;
	light_vec[0] = 0.0; light_vec[1] = 0.0; light_vec[2] = -1.0;
	TinyRender::TGAImage tga_image(width, height, TinyRender::TGAImage::ImageFormat_RGB);
	TinyRender::Model model("../../Models/AfricanHead.obj");
	TinyRender::TGAImage text_map("../../Models/AfricanHeadDiffuse.tga");
	std::ofstream out_tga_file("../../Temp/TGATEST.tga", std::ios::binary);
	
	//	Buffer of screen points
	std::array<TinyRender::Vec3i, 3> screen_points;

	for (size_t tr_id = 0; tr_id < model.triangles().size(); ++tr_id)
	{

		const TinyRender::Vec3f& p1 = model.vertices()[model.triangles()[tr_id].vertices[0]];
		const TinyRender::Vec3f& uv1 = model.uv_vertices()[model.triangles()[tr_id].uv_vertices[0]];
		const TinyRender::Vec3f& p2 = model.vertices()[model.triangles()[tr_id].vertices[1]];
		const TinyRender::Vec3f& uv2 = model.uv_vertices()[model.triangles()[tr_id].uv_vertices[1]];
		const TinyRender::Vec3f& p3 = model.vertices()[model.triangles()[tr_id].vertices[2]];
		const TinyRender::Vec3f& uv3 = model.uv_vertices()[model.triangles()[tr_id].uv_vertices[2]];

		const TinyRender::Vec3i& p1i = engine.transform(p1);
		const TinyRender::Vec3i& p2i = engine.transform(p2);
		const TinyRender::Vec3i& p3i = engine.transform(p3);

		const float u1x  = uv1[0] * text_map.width();
		const float u1y =  uv1[1] * text_map.height();


		const float u2x = uv2[0] * text_map.width();
		const float u2y = uv2[1] * text_map.height();

		const float u3x = uv3[0] * text_map.width();
		const float u3y = uv3[1] * text_map.height();

		TinyRender::Vec3f norm_vec = vector_product((p3 - p1), (p2 - p1));
		norm_vec.normalize();
		const float intense = light_vec * norm_vec;
		if (intense > 0)
		{
			TinyRender::render_triangle(p1i[0], p1i[1], p1i[2], u1x, u1y, 
										p2i[0], p2i[1], p2i[2], u2x, u2y,
										p3i[0], p3i[1], p3i[2], u3x, u3y,
										tga_image, text_map, z_buffer, intense);
		}
	}
	tga_image << out_tga_file;
	out_tga_file.close();
	return 0;
}