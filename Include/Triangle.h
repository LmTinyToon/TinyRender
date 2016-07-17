//	Include guard
#ifndef TINY_RENDER_TRIANGLE_INCLUDED_H__
#define TINY_RENDER_TRIANGLE_INCLUDED_H__

//	Std includes

//	Includes
#include "TGAImage.h"
#include "Line.h"

//	TinyRender namespace 
namespace TinyRender
{

//	Constants/enums

//	Global classes

//	Global functions
/*
		Renders triangle
		Params: 
			x0 position, y0 position,
			x1 position, y1 position, 
			x2 position, y2 position, 
			tga image, pixel
		Return: none

*/
inline void render_triangle(int x0, int y0, int x1, int y1, int x2, int y2, TGAImage& image, const TGAImage::Pixel& pixel)
{
	/*
			This algorithm is similar to Bresenham's line algorithm
			I just use two consequenced calling Bresenham's line algorithm
	*/
	bool reversed = false;
	if (std::abs(x1 - x0) < std::abs(y1 - y0))
	{
		std::swap(x0, y0);
		std::swap(x1, y1);
		reversed = true;
	}
	if (x0 > x1)
	{
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	const float derror = std::abs(static_cast<float>(y1 - y0) / (x1 - x0));
	float error = 0;
	int y = y0;
	for (int x = x0; x < x1; ++x)
	{
		if (reversed)
			render_line(y, x, x2, y2, image, pixel);
		else
			render_line(x, y, x2, y2, image, pixel);
		error += derror;
		if (error >= 0.5)
		{
			y += (y0 < y1) ? 1 : -1;
			error -= 1.0;
		}
	}
}

//	TinyRender end namespace
};

//	Include guard end
#endif