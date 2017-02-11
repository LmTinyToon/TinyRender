//	Std includes

//	Local includes
#include "Geometry.h"

//	Using namespaces
using namespace std;

//	TinyReader namespace
namespace TinyRender
{

//	Classes

//	Global functions implementation
Matr4f& translate(Matr4f& m, const float x, const float y, const float z)
{
	m[0][3] += x;
	m[1][3] += y;
	m[2][3] += z;
	return m;
}

Matr4f& scale(Matr4f& m, const float sx, const float sy, const float sz)
{
	m[0][0] *= sx;
	m[1][1] *= sy;
	m[2][2] *= sz;
	return m;
}

Matr4f& rotate(Matr4f& m, const float phi, const float x, const float y, const float z)
{
	const float c = cos(phi);
	const float _1_c = 1.0 - c;
	const float s = sin(phi);

	Matr4f rot_matr;
	rot_matr[0][0] = x * x * _1_c + c;
	rot_matr[1][0] = x * y * _1_c + z * s;
	rot_matr[2][0] = x * z * _1_c - y * s;
	rot_matr[3][0] = 0.0;

	rot_matr[0][1] = x * y * _1_c - z * s;
	rot_matr[1][1] = y * y * _1_c + c;
	rot_matr[2][1] = y * z * _1_c + x * s;
	rot_matr[3][1] = 0.0;

	rot_matr[0][2] = x * z * _1_c + y * s;
	rot_matr[1][2] = y * z * _1_c - z * s;
	rot_matr[2][2] = z * z * _1_c + c;
	rot_matr[3][2] = 0.0;

	rot_matr[0][3] = 0.0;
	rot_matr[1][3] = 0.0;
	rot_matr[2][3] = 0.0;
	rot_matr[3][3] = 1.0;

	*(&m) = m * rot_matr;
	return m;
}

Vec3i convert(const Vec3f& vec)
{
	Vec3i res;
	for (int i = 0; i < 3; ++i)
		res[i] = static_cast<int>(vec[i]);
	return res;
}

Vec3f vector_product(const Vec3f& lhs, const Vec3f& rhs)
{
	Vec3f res;
	res[0] = lhs[1] * rhs[2] - lhs[2] * rhs[1];
	res[1] = lhs[2] * rhs[0] - lhs[0] * rhs[2];
	res[2] = lhs[0] * rhs[1] - lhs[1] * rhs[0];
	return res;
}

//	TinyReader end namespace
};