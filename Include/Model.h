//	Include guard
#ifndef TINY_RENDER_MODEL_INCLUDED_H__
#define TINY_RENDER_MODEL_INCLUDED_H__

//	Std includes
#include <vector>
#include <string>
#include <array>

//	Includes
#include "Geometry.h"

//	TinyRender namespace 
namespace TinyRender
{

//	Constants/enums

//	Global classes
//		Triangle class
struct Triangle
{
//	Constructors
/*
		Triangle constructor
		Params: indices of vertices
*/
	Triangle(const int i, const int j, const int k) :
		vertices({ i, j, k }), uv_vertices({ 0, 0, 0 })
	{
	}

/*
		Triangle constructor
		Params: indices of vertices, indices of texture vertices
*/
	Triangle(const int i, const int j, const int k, const int i_uv, const int j_uv, const int k_uv) :
		vertices({ i, j, k }), uv_vertices({ i_uv, j_uv, k_uv })
	{
	}

//	Members
//		Indices of vertices
	std::array<int, 3> vertices;
//		Indices of texture vertices
	std::array<int, 3> uv_vertices;
};

//		Model class
class Model
{
public:
//	Classes
//		vertices type
	typedef std::vector<Vec3f> vertices_type;
//		triangles type
	typedef std::vector<Triangle> triangles_type;

//	Constructors/destructor
/*
		Model constructor
		Params: name of model
*/
	explicit Model(const std::string& model_name);

/*
		Gets vertices of model
		Params: none
		Return: vertices of model
*/
	inline vertices_type& vertices(void)
	{
		return m_vertices;
	}

/*
		Gets texture vertices of model
		Params: none
		Return: texture vertices of model
*/
	inline vertices_type& uv_vertices(void)
	{
		return m_uv_vertices;
	}

/*
		Gets trianlges of model
		Params: none
		Return: triangles of model
*/
	inline triangles_type& triangles(void)
	{
		return m_triangles;
	}

protected:
private:
//	Members
//		Vertices of model
	vertices_type m_vertices;
//		Texture vertices
	vertices_type m_uv_vertices;
//		Triangles of model
	triangles_type m_triangles;
};
//	Global functions
	
//	TinyRender end namespace
};

//	Include guard end
#endif