//	Std includes
#include <fstream>

//	Local includes
#include "Model.h"

//	TinyReader namespace
namespace TinyRender
{

//	Model - constructors/destructor
Model::Model(const std::string& model_name) : 
	m_vertices()
{
	std::ifstream file_model(model_name);
	size_t triangles_count = 0;
	file_model >> triangles_count;
	m_vertices.resize(triangles_count * 9);
	for (size_t i = 0; i < m_vertices.size(); ++i)
		file_model >> m_vertices[i];
}

//	TinyReader end namespace
};