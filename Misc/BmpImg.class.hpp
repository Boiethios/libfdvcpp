/*******************************************************************************
 * fdaudre-@student.42.fr
 *
 *
 ******************************************************************************/

#pragma once

#include "Core/Object.abstract.hpp"

#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <fstream>
#include <array>
#include <vector>

FDV_BEGIN_NAMESPACE

class BmpImg : public Object
{
		static uint8_t constexpr	_Default_color = 0u;

		struct __attribute__((__packed__)) header_t
		{
			struct __attribute__((__packed__))
			{
					char const		signature[2];
					uint32_t		file_size;
					uint32_t		:32;
					uint32_t const	img_offset;
			}						head;

			struct __attribute__((__packed__))
			{
					uint32_t const	info_size;
					uint32_t		img_width;
					uint32_t		img_height;
					uint16_t const	planes;
					uint16_t const	bpp;
					uint32_t const	compression;
					uint32_t		img_size;
					uint32_t const	horz_resolution;
					uint32_t const	vert_resolution;
					uint32_t const	n_colors;
					uint32_t const	n_important_colors;
			}						info;

			typedef std::array<uint32_t, 256> color_t;

			color_t const			colormap;
		};


		uint32_t const				_width;
		uint32_t const				_height;
		header_t					_header;
		std::vector<uint8_t>		_bitmap;

	public:

		BmpImg(uint32_t width, uint32_t height);

		std::size_t
		width(void) const;

		std::size_t
		height(void) const;

		uint8_t &
		operator()(std::size_t line, std::size_t col);

		void
		write(std::string filename);

		void
		clear(uint8_t color = _Default_color);
};

FDV_END_NAMESPACE
