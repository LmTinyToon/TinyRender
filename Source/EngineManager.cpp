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