//	Include guard
#ifndef TINY_RENDER_MODEL_INCLUDED_H__
#define TINY_RENDER_MODEL_INCLUDED_H__

//	Std includes
#include <vector>
#include <string>

//	Includes

//	TinyRender namespace 
namespace TinyRender
{

//	Constants/enums

//	Global classes
//		Model class
class Model
{
public:
//	Classes
	typedef std::vector<int> vertices_type;

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