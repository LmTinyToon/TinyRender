#include "TGAImage.h"

//	TinyRender namespace
namespace TinyRender
{

//	TGAImage - constructors
TGAImage::TGAImage(const int width, const int height, const ImageFormat image_format) :
	m_width(width), m_height(height), 
	m_bytes_per_pixel(static_cast<int>(image_format)), 
	m_buffer(width*height*m_bytes_per_pixel, 0)
{
}

TGAImage::TGAImage(const std::string& file_name) : 
	m_width(0), m_height(0), m_bytes_per_pixel(0), m_buffer()
{
	std::ifstream is(file_name, std::ios::binary);
	TGAHeader tga_header(0, 0, 0);
	is.read((char*)(&tga_header), sizeof(TGAHeader));
	
	m_width = tga_header.image_width;
	m_height = tga_header.image_height;
	m_bytes_per_pixel = tga_header.image_pixel_depth / 8;
	load_buffer(tga_header, is);
	is.close();
}

//	TGAImage - methods
TGAImage::Pixel TGAImage::get_pixel(const int x, const int y) const
{
	//	TODO: optimize this code
	const int pos = (x + y * m_width)*m_bytes_per_pixel;
	const int offset = (m_bytes_per_pixel == 4) ? 1 : 0;
	Pixel pixel;
	if (pos < 0 || static_cast<int>(m_buffer.size()) <= pos)
		return pixel;
	if (m_bytes_per_pixel == 4)
		memcpy(&pixel.alpha, &m_buffer[pos], 1);
	memcpy(&pixel.blue,  &m_buffer[pos + 0 + offset], 1);
	memcpy(&pixel.green, &m_buffer[pos + 1 + offset], 1);
	memcpy(&pixel.red,   &m_buffer[pos + 2 + offset], 1);
	return pixel;
}

void TGAImage::set_pixel(const Pixel& pixel, const int x, const int y)
{
	//	TODO: optimize this code
	const int pos = (x + y * m_width)*m_bytes_per_pixel;
	//	NOTE: we should put pixel only at existed position in image
	if (pos < 0 || static_cast<int>(m_buffer.size()) <= pos)
		return;
	const int offset = (m_bytes_per_pixel == 4) ? 1 : 0;
	if (m_bytes_per_pixel == 4)
		memcpy(&m_buffer[pos], &pixel.alpha, 1);
	memcpy(&m_buffer[pos + 0 + offset], &pixel.blue, 1);
	memcpy(&m_buffer[pos + 1 + offset], &pixel.green, 1);
	memcpy(&m_buffer[pos + 2 + offset], &pixel.red, 1);
}

void TGAImage::set_pixel(std::vector<std::vector<int>>& z_buffer, const Pixel& pixel,
	const int x, const int y, const int z)
{
	const bool contains = 0 <= y && y < m_height && 0 <= x && x < m_width;
	if (contains && z_buffer[y][x] < z)
	{
		z_buffer[y][x] = z;
		set_pixel(pixel, x, y);
	}
}

std::ostream& TGAImage::operator<<(std::ostream& os) const
{
	{
		const TGAHeader tga_header2(m_width, m_height, m_bytes_per_pixel);
		os.write((char*)(&tga_header2), sizeof(TGAHeader));
	}
	{
		//	Buffer writing
		os.write(m_buffer.data(), m_buffer.size());
	}
	return os;
}

//	TGAImage - private methods
void TGAImage::load_buffer(const TGAImage::TGAHeader& header, std::ifstream& if_stream)
{
	m_buffer = std::vector<char>(m_width * m_height * m_bytes_per_pixel, 0);
	switch (header.image_type)
	{
		case 2:
			if_stream.read(m_buffer.data(), m_buffer.size());
		break;
		case 10:
		{
			
			std::vector<char> abgr(m_bytes_per_pixel, 0);
			//	Parsing compressed pixels
			for (size_t i = 0; i < m_buffer.size(); )
			{
				int id = if_stream.get();
				//	8th bit indicates run length data
				if (id < 128)
				{ 
					++id;
					for (int length = 0; length < id; ++length, i += m_bytes_per_pixel)
					{
						if_stream.read(abgr.data(), abgr.size());
						std::copy(abgr.begin(), abgr.end(), m_buffer.begin() + i);
					}
					
				}
				else
				{
					id -= 127;
					if_stream.read(abgr.data(), abgr.size());
					for (int length = 0; length < id; ++length, i += m_bytes_per_pixel)
						std::copy(abgr.begin(), abgr.end(), m_buffer.begin() + i);
				}
			}
		}
		break;
		default:
			throw std::exception("Unsupporting file format");
	}
}

//	TinyRender end namespace
};