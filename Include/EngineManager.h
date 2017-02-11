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
private:
//	Private methods

//	Members
//		Current mode
	MatrixMode m_mode;
//		Matrices
	std::array<Matr4f, 3> m_matrices;
//		Viewport matrix
	Matr4f m_viewport;
};

//	Global functions

//	TinyRender end namespace
};

//	Include guard end
#endif