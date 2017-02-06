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
			tga image, texture map, pixel, intensity
		Return: none

*/
inline void render_triangle(int x0, int y0, int z0, int u0, int v0,
							int x1, int y1, int z1, int u1, int v1,
							int x2, int y2, int z2, int u2, int v2,
							TGAImage& image, const TGAImage& texture_map, 
							std::vector<std::vector<int>>& z_buffer, const TGAImage::Pixel& pixel, 
							const float intensity)
{
	if (y0 == y1 && y1 == y2)
		return;
	if (y0 > y1)
	{
		std::swap(x0, x1);
		std::swap(y0, y1);
		std::swap(z0, z1);
		std::swap(u0, u1);
		std::swap(v0, v1);
	}
	if (y0 > y2)
	{
		std::swap(x0, x2);
		std::swap(y0, y2);
		std::swap(z0, z2);
		std::swap(u0, u2);
		std::swap(v0, v2);
	}
	if (y1 > y2)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
		std::swap(z1, z2);
		std::swap(u1, u2);
		std::swap(v1, v2);
	}
	int xx = y0 == y1 || x0 == x2 ? x0 : (y1 - y0) * static_cast<float>(x2 - x0) / (y2 - y0) + x0;
	int yx = y1;
	int zx = z0 == z2 ? z0 : (z1 - z0) * static_cast<float>(x2 - x0) / (z2 - z0) + z0;
	int ux = v1 == v2 ? u2 : (v1 - v0) * static_cast<float>(u2 - u0) / (v2 - v0) + u0;
	int vx = v1;
	if (x1 < xx)
	{
		std::swap(xx, x1);
		std::swap(yx, y1);
		std::swap(zx, z1);
		std::swap(ux, u1);
		std::swap(vx, v1);
	}
	float alpha = 0.0;
	int seg_height = yx - y0;
	if (seg_height != 0)
	{
		const int lhs_dx = xx - x0;
		const int lhs_dz = zx - z0;
		const int lhs_du = ux - u0;
		const int lhs_dv = vx - v0;

		const int rhs_dx = x1 - x0;
		const int rhs_dz = z1 - z0;
		const int rhs_du = u1 - u0;
		const int rhs_dv = v1 - v0;
		const float dy = 1.0 / seg_height;
		for (int y = y0; y <= yx; ++y, alpha += dy)
		{
			const int rx = x0 + rhs_dx * alpha;
			
			const int lz = z0 + lhs_dz * alpha;
			const int lu = u0 + lhs_du * alpha;
			const int lv = v0 + lhs_dv * alpha;

			const int rz = z0 + rhs_dz * alpha;
			const int ru = u0 + rhs_du * alpha;
			const int rv = v0 + rhs_dv * alpha;

			const float dz = rz == lz ? 0 : 1.0 / (rz - lz);
			const float du = ru == lu ? 0 : 1.0 / (ru - lu);
			const float dv = rv == lv ? 0 : 1.0 / (rv - lv);
			float phi = 0.0;
			float uphi = 0.0;
			float vphi = 0.0;
			for (int x = x0 + lhs_dx * alpha; x <= rx; ++x, phi += dz, uphi += du, vphi += dv)
				image.set_pixel(z_buffer, texture_map.get_pixel(lu + (ru - lu) * uphi, lv + (rv - lv) * vphi).mult(intensity), 
								x, y, lz + (rz - lz) * phi);
		}
	}
	seg_height = y2 - yx;
	alpha = 0.0;
	if (seg_height != 0)
	{
		const int lhs_dx = x2 - xx;
		const int lhs_dz = z2 - zx;
		const int lhs_du = u2 - ux;
		const int lhs_dv = v2 - vx;

		const int rhs_dx = x2 - x1;
		const int rhs_dz = z2 - z1;
		const int rhs_du = u2 - u1;
		const int rhs_dv = v2 - v1;

		const float dy = 1.0 / seg_height;
		for (int y = yx; y <= y2; ++y, alpha += dy)
		{
			const int rx = x1 + rhs_dx * alpha;
			const int lz = zx + lhs_dz * alpha;
			const int lu = ux + lhs_du * alpha;
			const int lv = vx + lhs_dv * alpha;

			const int rz = z1 + rhs_dz * alpha;
			const int ru = u1 + rhs_du * alpha;
			const int rv = v1 + rhs_dv * alpha;

			const float dz = rz == lz ? 0 : 1.0 / (rz - lz);
			const float du = ru == lu ? 0 : 1.0 / (ru - lu);
			const float dv = rv == lv ? 0 : 1.0 / (rv - lv);
			float phi = 0.0;
			float uphi = 0.0;
			float vphi = 0.0;
			for (int x = xx + lhs_dx * alpha; x <= rx; ++x, phi += dz, uphi += du, vphi += dv)
				image.set_pixel(z_buffer, texture_map.get_pixel(lu + (ru - lu) * uphi, lv + (rv - lv) * vphi).mult(intensity),
					x, y, lz + (rz - lz) * phi);
		}
	}
}

//	TinyRender end namespace
};

//	Include guard end
#endif