#include "Misc/BmpImg.class.hpp"

FDV_BEGIN_NAMESPACE

Bmp_image::Bmp_image(uint32_t width, uint32_t height)
{
	auto	normalize([] (uint32_t n)
		-> uint32_t
	{
		for (uint32_t bit(1u << (-1 + 8 * sizeof(n))) ; bit ; bit >>= 1)
		{
			if (n & bit)
			{
				if (n == bit)
					return n;
				else if (bit << 1)
					return bit << 1;
				else
					throw std::exception();
			}
		}
		throw std::exception();
	});

	for (std::size_t count(0) ; count < 256 ; ++count)
	{
		uint8_t	i(static_cast<uint8_t>(count));
		_colormap.color[i] = {i, i, i};
	}

	try
	{
		_info.width = normalize(width);
	}
	catch (std::exception const &)
	{
		throw std::runtime_error("Invalid width");
	}
	try
	{
		_info.height = normalize(height);
	}
	catch (std::exception const &)
	{
		throw std::runtime_error("Invalid height");
	}

	_info.img_size = _info.width * _info.height;
	_header.file_size = _info.img_size + _header.img_offset;

	_bitmap = new uint8_t[_info.img_size];
	this->clear();
}


std::size_t
Bmp_image::width(void) const
{
	return _info.width;
}

std::size_t
Bmp_image::height(void) const
{
	return _info.height;
}

uint8_t &
Bmp_image::operator()(std::size_t line, std::size_t col)
{
	std::size_t		w(_info.width);
	std::size_t		h(_info.height);

	if (col >= h)
		throw std::runtime_error("Column value out of bounds");
	if (line >= w)
		throw std::runtime_error("Line value out of bounds");

	return _bitmap[w * col + line];
}

void
Bmp_image::write(std::string filename)
{
	std::ofstream	ofs(filename, std::ofstream::binary);

	if (not ofs.is_open())
		throw std::runtime_error(std::string("Cannot open ") + filename);
	ofs.write(reinterpret_cast<char *>(&_header), sizeof _header);
	ofs.write(reinterpret_cast<char *>(&_info), sizeof _info);
	ofs.write(reinterpret_cast<char *>(&_colormap), sizeof _colormap);
	ofs.write(reinterpret_cast<char *>(_bitmap), _info.img_size);
	ofs.close();
}

void
Bmp_image::clear(uint8_t color)
{
	for (std::size_t i(0) ; i < _info.img_size ; ++i)
		_bitmap[i] = color;
}


FDV_END_NAMESPACE
