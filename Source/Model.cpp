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
		GeometricVertex,
		Face
	};

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
			size_t pos = 0;
			skip_spaces(buff, pos);
			const ElementType elem_type = parse_elem_type(get_token_str(buff, pos, ' '));
			switch (elem_type)
			{
				case ElementType::GeometricVertex:
					m_geom_vertices.push_back(parse_geom_vertex(buff, pos));
				break;
				case ElementType::Face:
					m_triangles.push_back(parse_triangle(buff, pos));
				break;
				case ElementType::Comment:
					//	Skipping comment
				break;
			}
		}
	}

/*
		Parses element type
		Params: element string representation
		Return: element type
*/
	ElementType parse_elem_type(const string& elem_str)
	{
		if (elem_str == "v")
			return ElementType::GeometricVertex;
		if (elem_str == "f")
			return ElementType::Face;
		return ElementType::Comment;
	}

/*
		Parses geometric vertex
		Params: vertex line, position
		Return: geometric vertex
*/
	Point parse_geom_vertex(const string& vertex_line, size_t& pos)
	{
		array<float, 4> coords;
		coords[3] = 1.0;
		for (size_t i = 0; i < 3 && skip_spaces(vertex_line, pos); ++i)
			coords[i] = parse_float_number(get_token_str(vertex_line, pos, ' '));
		return Point(coords);
	}

/*
		Parses face
		Params: face line, position
		Return: face
*/
	Triangle parse_triangle(const string& face_line, size_t& pos)
	{
		skip_spaces(face_line, pos);
		const int i = parse_int_number(get_token_str(face_line, pos, '/'));
		
		//	TODO: (alex) too dirty
		get_token_str(face_line, pos, ' ');
		skip_spaces(face_line, pos);

		const int j = parse_int_number(get_token_str(face_line, pos, '/'));

		//	TODO: (alex) too dirty
		get_token_str(face_line, pos, ' ');
		skip_spaces(face_line, pos);

		const int k = parse_int_number(get_token_str(face_line, pos, '/'));
		return Triangle(i - 1, j - 1, k - 1);
	}

/*
		Parses float number
		Params: number string
		Return: float number
*/
	float parse_float_number(const string& num_str)
	{
		float num = 0;
		const bool neg = num_str[0] == '-';
		size_t pos = neg ? 1 : 0;
		for (; pos < num_str.size() && num_str[pos] != '.'; ++pos)
			num = num * 10 + num_str[pos] - '0';
		int frac_digs = 1;
		for (++pos; pos < num_str.size(); ++pos, frac_digs *= 10)
			num = num * 10 + num_str[pos] - '0';
		num /= frac_digs;
		return neg ? -num : num;
	}

/*
		Parses int number
		Params: number string
		Return: int number
*/
	int parse_int_number(const string& num_str)
	{
		int num = 0;
		const bool neg = num_str[0] == '-';
		size_t pos = neg ? 1 : 0;
		for (; pos < num_str.size(); ++pos)
			num = num * 10 + num_str[pos] - '0';
		return neg ? -num : num;
	}

/*
		Get token string
		Params: string, position, end delimiter
		Return: token string
*/
	string get_token_str(const string& str, size_t& pos, const char del)
	{
		string buf;
		buf.reserve(4);
		for (; pos < str.size() && str[pos] != del; ++pos)
			buf.push_back(str[pos]);
		return buf;
	}

/*
		Skips spaces in string
		Params: string, current position
		Return: continue flag
*/
	bool skip_spaces(const string& str, size_t& pos)
	{
		bool res = pos < str.size();
		for (; res && str[pos] == ' ';)
			res = ++pos < str.size();
		return res;
	}

//	Members
//		Geometry vertices
	vector<Point> m_geom_vertices;
//		Triangles
	vector<Triangle> m_triangles;
};

//	Model - constructors/destructor
Model::Model(const string& model_name) : 
	m_vertices()
{
	ifstream file_model(model_name);
	size_t triangles_count = 0;
	file_model >> triangles_count;
	m_vertices.reserve(triangles_count * 3);
	for (size_t i = 0; i < triangles_count * 3; ++i)
	{
		array<float, 4> coords = { 0.0, 0.0, 0.0, 1.0 };
		for (size_t j = 0; j < 2; ++j)
			file_model >> coords[j];
		m_vertices.push_back(Point(coords));
	}
}

//	TinyReader end namespace
};