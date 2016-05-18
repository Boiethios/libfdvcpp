#pragma once

#include "Core/Object.abstract.hpp"

#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <fstream>

FDV_BEGIN_NAMESPACE

class Bmp_image : public Object
{
		struct __attribute__((__packed__))
		{
				char const		signature[2] = {'B', 'M'};
				uint32_t		file_size;
				uint32_t		:32; // reserved
				uint32_t const	img_offset = 1078u;
		}						_header;

		struct __attribute__((__packed__))
		{
				uint32_t const	info_size = 40u;
				uint32_t		width;
				uint32_t		height;
				uint16_t const	planes = 1u;
				uint16_t const	bpp = 8u;
				uint32_t const	compression = 0u;
				uint32_t		img_size;
				uint32_t const	horz_resolution = 0u;
				uint32_t const	vert_resolution = 0u;
				uint32_t const	n_colors = 256u;
				uint32_t const	n_important_colors = 0u;
		}						_info;

		struct __attribute__((__packed__))
		{
				struct __attribute__((__packed__)) color_t
				{
					uint8_t		r,
								g,
								b;
					uint8_t		:8;
				};


				color_t			color[256];
		}						_colormap;

		uint8_t					*_bitmap;

	public:

		Bmp_image(uint32_t width, uint32_t height);

		std::size_t
		width(void) const;

		std::size_t
		height(void) const;

		uint8_t &
		operator()(std::size_t line, std::size_t col);

		void
		write(std::string filename);

		void
		clear(uint8_t color = 0);
};

FDV_END_NAMESPACE
