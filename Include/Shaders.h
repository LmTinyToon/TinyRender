//	Include guard
#ifndef TINY_RENDER_SHADERS_INCLUDED_H__
#define TINY_RENDER_SHADERS_INCLUDED_H__

//	Std includes

//	Includes
#include "EngineManager.h"

//	TinyRender namespace 
namespace TinyRender
{

//	Constants/enums

//	Global classes
//		DummyShader class
/*
		NOTE: Dummy shader renders model as it is, wihout any effects
*/
class DummyShader : public Shader
{
public:
//	Constructors/desructor
/*
		DummyShader constructor
		Params: engine
*/
	DummyShader(EngineManager& engine);

//	Methods
/*
		Vertex producer
		Params: model, index of face, index of vertex
		Return: screen vertex
*/
	virtual Vec3i vertex(const Model& model, const int face_id, const int vertex_id);

/*
		Color producer
		Params: pixel 
		Return: production result
*/
	virtual bool color(Pixel& pixel);

};

//	Global functions

//	TinyRender end namespace
};

//	Include guard end
#endif