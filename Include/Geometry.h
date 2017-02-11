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