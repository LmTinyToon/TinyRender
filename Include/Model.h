//	Include guard
#ifndef TINY_RENDER_MODEL_INCLUDED_H__
#define TINY_RENDER_MODEL_INCLUDED_H__

//	Std includes
#include <vector>
#include <string>
#include <array>

//	Includes

//	TinyRender namespace 
namespace TinyRender
{

//	Constants/enums

//	Global classes
//		Point class
struct Point
{
//	Constructors
/*
		Point constructor
		Params: x, y, z, w coords
*/
	Point(const float x, const float y, const float z, const float w = 1.0) :
		coords({x, y, z, w})
	{
	}

/*
		Point constructor
		Params: coords array
*/
	Point(const std::array<float, 4>& _coords) :
		coords(_coords)
	{
	}

//	Public methods
/*
		X coord getter
		Params: none
		Return: x coord getter
*/
	float x(void) const
	{
		return coords[0];
	}

/*
		Y coord getter
		Params: none
		Return: x coord getter
*/
	float y(void) const
	{
		return coords[1];
	}

/*
		Z coord getter
		Params: none
		Return: x coord getter
*/
	float z(void) const
	{
		return coords[2];
	}

//	Public members
//		Coords
	std::array<float, 4> coords;
};

//		Model class
class Model
{
public:
//	Classes
	typedef std::vector<Point> vertices_type;

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

protected:
private:
//	Members
//		Vertices of model
	vertices_type m_vertices;
};
//	Global functions
	
//	TinyRender end namespace
};

//	Include guard end
#endif