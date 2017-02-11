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
void EngineManager::set_viewport(const int x, const int y, const int width, const int height)
{
	const float w2 = width / 2.0;
	const float h2 = height / 2.0;
	scale(m_viewport, w2, h2, 1.0);
	translate(m_viewport, x + w2, y + h2, 0.0);
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