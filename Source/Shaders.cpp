//	Std includes

//	Local includes
#include "Shaders.h"
#include "Model.h"

//	Using namespaces
using namespace std;

//	TinyReader namespace
namespace TinyRender
{

//	Classes
//		DummyShader constructors
DummyShader::DummyShader(EngineManager& engine) : 
	Shader(engine), m_fragment_normal()
{
}

//		DummyShader methods
Vec3i DummyShader::vertex(const Model& model, const int face_id, const int vertex_id)
{
	//	TODO: (alex) simplfy model API
	const Vec3f& model_point = model.vertices()[model.triangles()[face_id].vertices[vertex_id]];
	//	TODO: (alex) remove this hack!
	m_fragment_normal = model.normals()[model.triangles()[face_id].normals[vertex_id]];
	return get_engine().transform(model_point);
}

bool DummyShader::color(Pixel& pixel)
{
	//	TODO: (alex) implement this method!
	return true;
}

//	Global functions implementation

//	TinyReader end namespace
};