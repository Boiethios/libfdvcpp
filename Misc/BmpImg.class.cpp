/*******************************************************************************
 * fdaudre-@student.42.fr
 *
 *
 ******************************************************************************/

#include "Misc/BmpImg.class.hpp"

#include "Core/make_array.template.hpp"

FDV_BEGIN_NAMESPACE

uint8_t constexpr	BmpImg::_Default_color;

BmpImg::BmpImg(uint32_t width, uint32_t height) :
	_width(width + (4 - (width & 0b11)) % 4), // _width must be multiple of 4
	_height(height),
	_header{
		{
			{'B', 'M'},
			_width * _height + static_cast<uint32_t>(sizeof _header),
			sizeof _header,
		},
		{
			sizeof _header.info,
			width,
			height,
			1u,					// planes
			8u,					// bpp
			0u,					// compression
			_width * _height,
			0u,					// horizontal resolution
			0u,					// vertical resolution
			256u,				// colors number
			0u,					// number of important colors
		},
		fdv::make_array<256u>([](uint32_t x){return x + (x << 8) + (x << 16); })
	},
	_bitmap(_header.info.img_size, _Default_color)
{
}


std::size_t
BmpImg::width(void) const
{
	return _header.info.img_width;
}

std::size_t
BmpImg::height(void) const
{
	return _header.info.img_height;
}

uint8_t &
BmpImg::operator()(std::size_t line, std::size_t col)
{
	std::size_t		w(_header.info.img_width);
	std::size_t		h(_header.info.img_height);

	if (col >= h)
		throw std::runtime_error("Column value out of bounds");
	if (line >= w)
		throw std::runtime_error("Line value out of bounds");

	return _bitmap[w * col + line];
}

void
BmpImg::write(std::string filename)
{
	std::ofstream	ofs(filename, std::ofstream::binary);

	if (not ofs.is_open())
		throw std::runtime_error(std::string("Cannot open ") + filename);
	ofs.write(reinterpret_cast<char *>(&_header), sizeof _header);
	ofs.write(reinterpret_cast<char *>(_bitmap.data()), _bitmap.size());
	ofs.close();
}

void
BmpImg::clear(uint8_t color)
{
	for (std::size_t i(0) ; i < _header.info.img_size ; ++i)
		_bitmap[i] = color;
}


FDV_END_NAMESPACE
