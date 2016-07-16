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
inline void render_line(const int x0, const int y0, const int x1, const int y1, TGAImage& image, const TGAImage::Pixel& pixel)
{
	(void*)(&x0);
	(void*)(&y0);
	(void*)(&x1);
	(void*)(&y1);
	(void*)(&image);
	(void*)(&pixel);
}

//	TinyRender end namespace
};

//	Include guard end
#endif