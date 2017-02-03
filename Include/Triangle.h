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
	if (y0 == y1 && y1 == y2)
		return;
	if (y0 > y1)
	{
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	if (y0 > y2)
	{
		std::swap(x0, x2);
		std::swap(y0, y2);
	}
	if (y1 > y2)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}
	int xx = y0 == y1 || x0 == x2 ? x0 : (y1 - y0) * static_cast<float>(x2 - x0) / (y2 - y0) + x0;
	int yx = y1;
	if (x1 < xx)
	{
		std::swap(xx, x1);
		std::swap(yx, y1);
	}
	int seg_height = yx - y0;
	if (seg_height != 0)
	{
		for (int y = y0; y <= yx; ++y)
		{
			const float alpha = static_cast<float>(y - y0) / seg_height;
			const int lx = x0 + (xx - x0) * alpha;
			const int rx = x0 + (x1 - x0) * alpha;
			for (int x = lx; x <= rx; ++x)
				image.set_pixel(pixel, x, y);
		}
	}
	seg_height = y2 - yx;
	if (seg_height != 0)
	{
		for (int y = yx; y <= y2; ++y)
		{
			const float alpha = static_cast<float>(y - yx) / seg_height;
			const int lx = xx + (x2 - xx) * alpha;
			const int rx = x1 + (x2 - x1) * alpha;
			for (int x = lx; x <= rx; ++x)
				image.set_pixel(pixel, x, y);
		}
	}
}

//	TinyRender end namespace
};

//	Include guard end
#endif