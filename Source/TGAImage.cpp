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
TGAImage::Pixel TGAImage::get_pixel(const int x, const int y) const
{
	//	TODO: optimize this code
	const int pos = (x + y * m_width)*m_bytes_per_pixel;
	const int offset = (m_bytes_per_pixel == 4) ? 1 : 0;
	Pixel pixel;
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
	if (pos < 0 || m_width * m_height <= pos)
		return;
	const int offset = (m_bytes_per_pixel == 4) ? 1 : 0;
	if (m_bytes_per_pixel == 4)
		memcpy(&m_buffer[pos], &pixel.alpha, 1);
	memcpy(&m_buffer[pos + 0 + offset], &pixel.blue, 1);
	memcpy(&m_buffer[pos + 1 + offset], &pixel.green, 1);
	memcpy(&m_buffer[pos + 2 + offset], &pixel.red, 1);
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

//	TinyRender end namespace
};