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
			x0 position, y0 position, z0 position, u0 position, v0 position,
			x1 position, y1 position, z1 position, u1 position, v1 position,
			x2 position, y2 position, z2 position, u2 position, v2 position,s
			tga image, texture map, pixel
		Return: none

*/
inline void render_triangle(int x0, int y0, int z0, int u0, int v0,
							int x1, int y1, int z1, int u1, int v1,
							int x2, int y2, int z2, int u2, int v2,
							TGAImage& image, const TGAImage& texture_map, 
							std::vector<std::vector<int>>& z_buffer, const TGAImage::Pixel& pixel)
{
	if (y0 == y1 && y1 == y2)
		return;
	if (y0 > y1)
	{
		std::swap(x0, x1);
		std::swap(y0, y1);
		std::swap(z0, z1);
	}
	if (y0 > y2)
	{
		std::swap(x0, x2);
		std::swap(y0, y2);
		std::swap(z0, z2);
	}
	if (y1 > y2)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
		std::swap(z1, z2);
	}
	int xx = y0 == y1 || x0 == x2 ? x0 : (y1 - y0) * static_cast<float>(x2 - x0) / (y2 - y0) + x0;
	int yx = y1;
	int zx = z0 == z2 ? z0 : (z1 - z0) * static_cast<float>(x2 - x0) / (z2 - z0) + z0;
	if (x1 < xx)
	{
		std::swap(xx, x1);
		std::swap(yx, y1);
		std::swap(zx, z1);
	}
	float alpha = 0.0;
	int seg_height = yx - y0;
	if (seg_height != 0)
	{
		const int lhs_dx = xx - x0;
		const int lhs_dz = zx - z0;
		const int rhs_dx = x1 - x0;
		const int rhs_dz = z1 - z0;
		const float dy = 1.0 / seg_height;
		for (int y = y0; y <= yx; ++y, alpha += dy)
		{
			const int rx = x0 + rhs_dx * alpha;
			const int lz = z0 + lhs_dz * alpha;
			const int rz = z0 + rhs_dz * alpha;
			const float dz = rz == lz ? 0 : 1.0 / (rz - lz);
			float phi = 0.0;
			for (int x = x0 + lhs_dx * alpha; x <= rx; ++x, phi += dz)
				image.set_pixel(z_buffer, pixel, x, y, lz + (rz - lz) * phi);
		}
	}
	seg_height = y2 - yx;
	alpha = 0.0;
	if (seg_height != 0)
	{
		const int lhs_dx = x2 - xx;
		const int lhs_dz = z2 - zx;
		const int rhs_dx = x2 - x1;
		const int rhs_dz = z2 - z1;
		const float dy = 1.0 / seg_height;
		for (int y = yx; y <= y2; ++y, alpha += dy)
		{
			const int rx = x1 + rhs_dx * alpha;
			const int lz = zx + lhs_dz * alpha;
			const int rz = z1 + rhs_dz * alpha;
			const float dz = rz == lz ? 0 : 1.0 / (rz - lz);
			float phi = 0.0;
			for (int x = xx + lhs_dx * alpha; x <= rx; ++x, phi += dz)
				image.set_pixel(z_buffer, pixel, x, y, lz + (rz - lz) * phi);
		}
	}
}

//	TinyRender end namespace
};

//	Include guard end
#endif