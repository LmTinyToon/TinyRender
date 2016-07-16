//	Include guard
#ifndef TINY_RENDER_TGA_IMAGE_INCLUDED_H__
#define TINY_RENDER_TGA_IMAGE_INCLUDED_H__

//	Std includes
#include <vector>
#include <fstream>

//	Includes

//	TinyRender namespace 
namespace TinyRender
{

//	Constants/enums

//	Global classes

//	TGAImage class
//	Note: this class represents TGA file
//	Current implementation does not support color maps
class TGAImage
{
public:
//	Public classes
//		TGAHeader struct
//		Note: this struct specifies header of any tga file
//		Force alignment
#pragma pack(push, 1)
	struct TGAHeader
	{
		/*
			TGAHeader constructor
			Params: width of image, height of image, bytes per pixel
		*/
		TGAHeader(const int width, const int height, const int bytes_per_pixel) : 
			id_length(0),  
			//	Not include color map
			//	------
			image_type(2), 
			color_map_type(0),
			color_map_first_entry_index(0), color_map_length(0), color_map_entry_size(0),
			//	------
			image_x_origin(0), image_y_origin(0),
			image_width(static_cast<short>(width)), image_height(static_cast<short>(height)),
			image_pixel_depth(static_cast<char>(bytes_per_pixel * 8)),
			image_descriptor(0x20)	//	Top left ordering of pixels
		{
		}

		//	Members
		char  id_length;						//	Specifies size of image id field
		char  color_map_type;					//	Specifies usage color map (its type)
		char  image_type;						//	Specifies type of image
		short color_map_first_entry_index;		//	Specifies first entry index in color map
		short color_map_length;					//	Specifies count of color map entries included
		char  color_map_entry_size;				//	Specifies the number of bits per color map entry
		short image_x_origin;					//	Specifies x origin of image
		short image_y_origin;					//	Specifies y origin of image
		short image_width;						//	Specifies width of image in pixels
		short image_height;						//	Specifies height of image in pixels
		char  image_pixel_depth;				//	Specifies pixel depth (common values 8, 16, 24, 32)
		char  image_descriptor;					//	Speciifes params of transmition of pixels
	};
#pragma pack(pop)

//		ImageFormat
	enum ImageFormat
	{
		ImageFormat_RGB = 3
	};

//	Constructors/destructor
/*
		TGAImage constructor
		Params: width, height, image format
*/
	explicit TGAImage(const int width, const int height, const ImageFormat image_format);

/*
		TGAImage destructor
*/
	~TGAImage(void)
	{
		//	Do nothing
	}

//	Methods
/*
		Gets width of image
		Params: none
		Return: width of image
*/
	inline int width(void) const
	{
		return m_width;
	}

/*
		Gets height of image
		Params: none
		Return: height of image
*/
	inline int height(void) const
	{
		return m_height;
	}

/*
		Ostream printer method
		Params: ostream object
		Return: ostream object
*/
	std::ostream& operator<<(std::ostream& os) const;

protected:
private:
//	Private members
//		Width of image
	int m_width;
//		Height of image
	int m_height;
//		Bytes per pixel
	int m_bytes_per_pixel;
//		Buffer of pixels
	std::vector<char> m_buffer;
};

//	Global functions

//	TinyRender end namespace
};

//	Include guard end
#endif