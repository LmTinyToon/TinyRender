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
		Substracts point
		Params: point
		Return: result of substraction
*/
	Point operator-(const Point& rhs) const
	{
		std::array<float, 4> buff;
		for (size_t i = 0; i < buff.size(); ++i)
			buff[i] = coords[i] - rhs.coords[i];
		return Point(buff);
	}

/*
		Performs dot production
		Params: point
		Return: result of dot production
*/
	float operator*(const Point& rhs) const
	{
		float res = 0;
		for (size_t i = 0; i + 1 < coords.size(); ++i)
			res += coords[i] * rhs.coords[i];
		return res;
	}

/*
		Performs cross production
		Params: point
		Return: result of cross production
*/
	Point operator^(const Point& rhs) const
	{
		std::array<float, 4> buff;
		buff[0] = y() * rhs.z() - z() * rhs.y();
		buff[1] = z() * rhs.x() - x() * rhs.z();
		buff[2] = x() * rhs.y() - y() * rhs.x();
		buff[3] = 1.0;
		return Point(buff);
	}

/*
		Computes length
		Params: none
		Return: length
*/
	float len(void) const
	{
		float res = 0;
		for (size_t i = 0; i + 1 < coords.size(); ++i)
			res += coords[i] * coords[i];
		return sqrt(res);
	}

/*
		Normalizes point
		Params: none
		Return: none
*/
	void normalize(void)
	{
		const float length = len();
		for (size_t i = 0; i < coords.size(); ++i)
			coords[i] /= length;
	}

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

//		Triangle class
struct Triangle
{
//	Constructors
/*
		Triangle constructor
		Params: indices of vertices
*/
	Triangle(const int i, const int j, const int k) :
		vertices({ i, j, k })
	{

	}

//	Members
//		Indices of vertices
	std::array<int, 3> vertices;
};

//		Model class
class Model
{
public:
//	Classes
//		vertices type
	typedef std::vector<Point> vertices_type;
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