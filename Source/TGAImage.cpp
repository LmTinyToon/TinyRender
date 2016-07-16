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

//	TGAImage - methods
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

//	TinyRender end namespace
};