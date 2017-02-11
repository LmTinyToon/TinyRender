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

Matr4f& rotate(Matr4f& m, const float px, const float py, const float pz)
{
	(void*)&m;
	(void*)&px;
	(void*)&py;
	(void*)&pz;
	throw exception("Rotation of matrix is not implemented!");
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