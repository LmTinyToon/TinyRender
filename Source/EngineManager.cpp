//	Std includes

//	Local includes
#include "EngineManager.h"

//	Using namespaces
using namespace std;

//	TinyReader namespace
namespace TinyRender
{

//	Classes
//		EngineManager implementation
//		EngineManager constructors/destructors
EngineManager::EngineManager(void) : 
	m_mode(MatrixMode::MODEL), m_matrices({ Matr4f::identity(), Matr4f::identity(), Matr4f::identity() }),
	m_viewport(Matr4f::identity())
{
}

//	EngineManager - public methods
Vec3i EngineManager::transform(const Vec3f& model_point) const
{
	Vec4f mod_point;
	for (int i = 0; i < 3; ++i)
		mod_point[i] = model_point[i];
	mod_point[3] = 1.0;
	const Vec4f& converted_point = m_viewport * m_matrices[2] * m_matrices[1] * m_matrices[0] * mod_point;
	Vec3f screen_point;
	for (int i = 0; i < 3; ++i)
		screen_point[i] = converted_point[i];
	return convert(screen_point);
}

void EngineManager::set_viewport(const int x, const int y, const int width, const int height)
{
	const float w2 = width / 2.0;
	const float h2 = height / 2.0;
	scale(m_viewport, w2, h2, 1.0);
	translate(m_viewport, x + w2, y + h2, 0.0);
}

void EngineManager::set_depth(const int depth)
{
	const float d2 = depth / 2.0;
	scale(m_viewport, 1.0, 1.0, d2);
	translate(m_viewport, 0.0, 0.0, d2);
}

Matr4f& EngineManager::set_mode(const MatrixMode mode)
{
	m_mode = mode;
	return get_matrix();
}

Matr4f& EngineManager::get_matrix(void)
{
	return m_matrices[static_cast<int>(m_mode)];
}	

//	EngineManager - private methods

//	TinyReader end namespace
};