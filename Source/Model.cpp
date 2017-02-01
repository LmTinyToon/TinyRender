//	Std includes
#include <fstream>

//	Local includes
#include "Model.h"

//	Using namespaces
using namespace std;

//	TinyReader namespace
namespace TinyRender
{

//	Classes
class ObjParser
{
public:
//	Constructors/destructors
/*
		ObjParser constructor
		Params: file name
*/
	ObjParser(const string& file_name)
	{
		ifstream file_model(file_name);
		parse_stream(file_model);
	}

protected:
private:
//	Enums/Constants
//		ElementType
	enum ElementType
	{
		Comment,
		GeometricVertex
	};

//	Methods
/*
		Extracts element type from string
		Params: string
		Return: element type

		NOTE: in current implementation it can only recognize vertices and comments (skip it)
*/
	ElementType extract_elem_type(const string& str)
	{
		for (size_t pos = 0; pos < str.size(); ++pos)
		{
			if (str[pos] == ' ')
				continue;
			switch (str[pos])
			{
				case 'v':
					return ElementType::GeometricVertex;
				case '#':
					return ElementType::Comment;
			}
		}
		return ElementType::Comment;
	}

/*
		Parses ifstream file
		Params: ifstream file
		Return: none
*/
	void parse_stream(ifstream& file)
	{
		for (string buff; getline(file, buff); )
		{
			switch (extract_elem_type(buff))
			{
				case ElementType::GeometricVertex:
					parse_vertex(buff);
				break;
				case ElementType::Comment:
					//	Skipping comment
				break;
			}
		}
	}

/*
		Parses vertex line
		Params: vertex line
		Return: none
*/
	void parse_vertex(const string& vertex_line)
	{
	}

//	Members
};

//	Model - constructors/destructor
Model::Model(const string& model_name) : 
	m_vertices()
{
	ifstream file_model(model_name);
	size_t triangles_count = 0;
	file_model >> triangles_count;
	m_vertices.resize(triangles_count * 9);
	for (size_t i = 0; i < m_vertices.size(); ++i)
		file_model >> m_vertices[i];
}

//	TinyReader end namespace
};