//	Include guard
#ifndef TINY_RENDER_GEOMETRY_INCLUDED_H__
#define TINY_RENDER_GEOMETRY_INCLUDED_H__

//	Std includes
#include <array>
//	Includes

//	TinyRender namespace 
namespace TinyRender
{

//	Constants/enums

//	Global classes
//		Vector class
template <typename _Ty, size_t _Dim>
class Vector
{
//		Num type
	typedef _Ty num_type;
//		Data type
	typedef std::array<num_type, _Dim> data_type;

//	Constructors/destructor

//	Methods
/*
		Item getter
		Params: Item index
		Return: Item
*/
	num_type& operator[](const int row)
	{
		return m_data[row];
	}

/*
		Item const getter
		Params: Item index
		Return: const Item
*/
	const num_type& operator[](const int row) const
	{
		return m_data[row];
	}
public:
private:
//		Vector data
	data_type m_data;
};

//		Matrix class
template <typename _Ty, size_t _Dim>
class Matrix
{
//	Private classes
//		Num type
	typedef _Ty num_type;
//		Data type
	typedef std::array<std::array<num_type, _Dim>, _Dim> data_type;
public:
//	Classes
//		Self type
	typedef Matrix<num_type, _Dim> self_type;
//		Vector type
	typedef Vector<num_type, _Dim> vec_type;

//	Constructors
//		Static methods
/*
		Computes identity matrix
		Params: none
		Return: identity matrix
*/
	static self_type identity()
	{
		data_type data;
		for (size_t i = 0; i < _Dim; ++i)
			for (size_t j = 0; j < _Dim; ++j)
				data[i][j] = (i == j) ? 1.0 : 0.0;
		return self_type(data);
	}

//	Methods
/*
		Multiplies matrix by matrix
		Params: matrix
		Return: multiplication result
*/
	self_type operator*(const self_type& rhs) const
	{
		data_type data;
		for (size_t i = 0; i < _Dim; ++i)
			for (size_t j = 0; j < _Dim; ++j)
			{
				data[i][j] = num_type();
				for (size_t k = 0; k < _Dim; ++k)
					data[i][j] += data[i][k] * data[k][j];
			}
		return self_type(data);
	}

/*
		Multiplies matrix by vector
		Params: vector
		Return: vector
*/
	vec_type operator*(const vec_type& vec) const
	{
		vec_type res;
		for (size_t i = 0; i < _Dim; ++i)
		{
			res[i] = num_type();
			for (size_t j = 0; j < _Dim; ++j)
				res[j] += m_data[i][j] * vec[j];
		}
		return res;
	}

/*
		Row getter
		Params: row index
		Return: row
*/
	std::array<num_type, _Dim>& operator[](const int row)
	{
		return m_data[row];
	}

/*
		Row const getter
		Params: row index
		Return: const row
*/
	const std::array<num_type, _Dim>& operator[](const int row) const
	{
		return m_data[row];
	}

private:
//	Private constructors
/*	
		Matrix constructor
		Params: matrix's data
*/
	Matrix(const data_type& data) : 
		m_data(data)
	{
	}

//		Matrix data
	data_type m_data;
};

//	Classes
//		Vec3i class
typedef Vector<int, 3> Vec3i;
//		Vec3f class
typedef Vector<float, 3> Vec3f;
//		Vec4f class
typedef Vector<float, 4> Vec4f;
//		Matr4f class
typedef Matrix<float, 4> Matr4f;


//	Global functions
/*
		Translate matrix along axes
		Params: matrix, x offset, y offset, z offset
		Return: changed matrix
*/
Matr4f& translate(Matr4f& m, const float x, const float y, const float z);

/*
		Scales matrix along axes
		Params: matrix, x scale, y scale, z scale
		Return: changed matrix
*/
Matr4f& scale(Matr4f& m, const float sx, const float sy, const float sz);

/*
		Rotates matrix within axes
		Params: matrix, x rot angle, y rot angle, z rot angle
		Return: changed matrix
*/
Matr4f& rotate(Matr4f& m, const float px, const float py, const float pz);

//	TinyRender end namespace
};

//	Include guard end
#endif