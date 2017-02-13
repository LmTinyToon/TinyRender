//	Include guard
#ifndef TINY_RENDER_ENGINE_MANAGER_INCLUDED_H__
#define TINY_RENDER_ENGINE_MANAGER_INCLUDED_H__

//	Std includes
#include <array>

//	Includes
#include "Geometry.h"

//	TinyRender namespace 
namespace TinyRender
{

//	Constants/enums

//	Global classes
//		EngineManager forward declaration class
class EngineManager;
//		Model forward declaration class
class Model;
//		Pixel forward declaration class
class Pixel;

//		Shader class
class Shader
{
public:
//	Constructors/destructors
/*
		IShader constructor
		Params: engine manager
*/
	Shader(EngineManager& engine) : 
		m_engine(engine)
	{
	}

/*
		IShader destructor
*/
	virtual ~Shader(void)
	{
	}

//	Methods
/*
		Vertex producer
		Params: model, index of face, index of vertex
		Return: screen vertex
*/
	virtual Vec3i vertex(const Model& model, const int face_id, const int vertex_id) = 0;

/*
		Color producer
		Params: pixel 
		Return: production result
*/
	virtual bool color(Pixel& pixel) = 0;

protected:
//	Protected methods
/*
		Engine manager getter
		Params: none
		Return: engine manager
*/
	EngineManager& get_engine(void)
	{
		return m_engine;
	}

private:
//	Members
//		EngineManager class
	EngineManager& m_engine;
};

//		EngineManager class
class EngineManager
{
public:
//	Enums/constans
//		Matrix mode
	enum class MatrixMode
	{
		MODEL = 0,
		VIEW = 1,
		PROJECTIVE = 2
	};

//	Constructors/destructors
/*
		EngineManager constructor
		Params: none
*/
	EngineManager(void);

//	Methods
/*	
		Transforms point
		Params: model point
		Return: screen point
*/
	Vec3i transform(const Vec3f& model_point) const;

/*
		Sets viewport
		Params: left top coordinates, sizes
		Return: none
*/
	void set_viewport(const int x, const int y, const int width, const int height);

/*
		Sets depth
		Params: depth
		Return: none
*/
	void set_depth(const int depth);

/*
		Changes mode of engine
		Params: mode
		Return: current matrix
*/
	Matr4f& set_mode(const MatrixMode mode);

/*
		Gets current matrix
		Params: none
		Return: current matrix
*/
	Matr4f& get_matrix(void);

/*
		Sets light direction
		Params: light direction
		Return: none
*/
	void set_light_direction(const Vec3f& light_dir);

/*
		Gets light position
		Params: none
		Return: light position
*/
	const Vec3f& get_light_direction(void) const;

private:
//	Private methods

//	Members
//		Current mode
	MatrixMode m_mode;
//		Matrices
	std::array<Matr4f, 3> m_matrices;
//		Viewport matrix
	Matr4f m_viewport;
//		Light direction
	Vec3f m_light_dir;
};

//	Global functions

//	TinyRender end namespace
};

//	Include guard end
#endif