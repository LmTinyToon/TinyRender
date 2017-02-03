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
	int dx = std::abs(x1 - x0);
	int dy = std::abs(y1 - y0);
	if (dx < dy)
	{
		std::swap(x0, y0);
		std::swap(x1, y1);
		std::swap(dx, dy);
		reversed = true;
	}
	if (x0 > x1)
	{
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	const int derror2 = dy * 2;
	for (int x = x0, y = y0, error2 = 0; x <= x1; ++x)
	{
		if (reversed)
			image.set_pixel(pixel, y, x);
		else
			image.set_pixel(pixel, x, y);
		error2 += derror2;
		if (error2 > dx)
		{
			y += (y0 < y1) ? 1 : -1;
			error2 -= dx * 2;
		}
	}
}

//	TinyRender end namespace
};

//	Include guard end
#endif