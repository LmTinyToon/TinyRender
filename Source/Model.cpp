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
//	Methods
/*
		Parses ifstream file
		Params: ifstream file
		Return: none
*/
	void parse_stream(ifstream& file)
	{
		for (string buff; getline(file, buff); )
		{
			switch (buff[0])
			{
				case 'v': 
					parse_vertex(buff);
				break;
				case 'f':
					parse_face(buff);
				break;
				case '#':	
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

/*
		Parses face line
		Params: face line
		Return: none
*/
	void parse_face(const string& face_line)
	{
		//	TODO: (alex) remove usage std exception class
		throw exception("Parsing of faces is not implemented");
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