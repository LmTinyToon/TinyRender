//	Include guard
#ifndef TINY_RENDER_LINE_INCLUDED_H__
#define TINY_RENDER_LINE_INCLUDED_H__

//	Std includes

//	Includes
#include "TGAImage.h"

//	TinyRender namespace 
namespace TinyRender
{

//	Constants/enums

//	Global classes

//	Global functions
/*
		Renders line
		Params: start x position, start y position, end x position, end y position, tga image, pixel
		Return: none

*/
inline void render_line(int x0, int y0, int x1, int y1, TGAImage& image, const TGAImage::Pixel& pixel)
{
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
	for (int x = x0; x < x1; ++x)
	{
		const float t = static_cast<float>(x - x0) / (x1 - x0);
		const int y = static_cast<int>(y0 + t * (y1 - y0));
		if (reversed)
			image.set_pixel(pixel, y, x);
		else
			image.set_pixel(pixel, x, y);
	}
}

//	TinyRender end namespace
};

//	Include guard end
#endif