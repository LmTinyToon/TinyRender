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
				data[i][j] = (i == j) ? 1 : 0;
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

//	TinyRender end namespace
};

//	Include guard end
#endif