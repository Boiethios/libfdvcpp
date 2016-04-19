/*******************************************************************************
 * fdaudre-@student.42.fr
 *
 *
 ******************************************************************************/

#include "IO/Color.class.hpp"

FDV_BEGIN_NAMESPACE

Color color;

Color::Color(void)
{
}
Color::~Color(void)
{
}


static inline void init_buffer(std::stringstream & buff)
{
	buff << "\033[";
}
static inline std::string close_buffer(std::stringstream & buff)
{
	std::string			res(buff.str());

	res[res.size() - 1] = 'm';
	return res;
}

static inline void add_style(std::stringstream & buff, int style)
{
	std::string			tmp("?;");

	for (int i = 1, idx = 0 ; i <= (int)Color::HIDDEN ; i <<= 1, ++idx)
		if (style & i)
		{
			tmp[0] = (char)('0' + idx);
			buff << tmp;
		}
}

static inline void add_fg(std::stringstream & buff,
			unsigned char r, unsigned char g, unsigned char b)
{
	buff << "38;2;" << (int)r << ";" << (int)g << ";" << (int)b << ";";
}

static inline void add_bg(std::stringstream & buff,
			unsigned char r, unsigned char g, unsigned char b)
{
	buff << "48;2;" << (int)r << ";" << (int)g << ";" << (int)b << ";";
}


std::string
Color::operator()(Color::STYLE style)
{
	std::stringstream	buff;

	init_buffer(buff);
	if (style == Color::STYLE::NONE)
		buff << "0;";
	else if ((int)style > 0)
		add_style(buff, (int)style);
	return close_buffer(buff);
}
std::string
Color::operator()(unsigned int fg_rgb, Color::STYLE style)
{
	std::stringstream	buff;

	init_buffer(buff);
	if (style == Color::STYLE::NONE)
		buff << "0;";
	else if ((int)style > 0)
		add_style(buff, (int)style);
	add_fg(buff, (unsigned char)((fg_rgb & 0xFF0000) >> 0xF),
			(unsigned char)((fg_rgb & 0x00FF00) >> 0x8),
			(unsigned char)(fg_rgb & 0x0000FF));
	return close_buffer(buff);
}
std::string
Color::operator()(unsigned int fg_rgb, unsigned int bg_rgb, Color::STYLE style)
{
	std::stringstream	buff;

	init_buffer(buff);
	if (style == Color::STYLE::NONE)
		buff << "0;";
	else if ((int)style > 0)
		add_style(buff, (int)style);
	add_fg(buff, (unsigned char)((fg_rgb & 0xFF0000) >> 0xF),
			(unsigned char)((fg_rgb & 0x00FF00) >> 0x8),
			(unsigned char)(fg_rgb & 0x0000FF));
	add_bg(buff, (unsigned char)((bg_rgb & 0xFF0000) >> 0xF),
			(unsigned char)((bg_rgb & 0x00FF00) >> 0x8),
			(unsigned char)(bg_rgb & 0x0000FF));
	return close_buffer(buff);
}

std::string
Color::fg(unsigned char r, unsigned char g, unsigned char b,
	Color::STYLE style)
{
	std::stringstream	buff;

	init_buffer(buff);
	if (style == Color::STYLE::NONE)
		buff << "0;";
	else if ((int)style > 0)
		add_style(buff, (int)style);
	add_fg(buff, r, g, b);
	return close_buffer(buff);
}
std::string
Color::fg(unsigned int fg_rgb,
	Color::STYLE style)
{
	std::stringstream	buff;

	init_buffer(buff);
	if (style == Color::STYLE::NONE)
		buff << "0;";
	else if ((int)style > 0)
		add_style(buff, (int)style);
	add_fg(buff, (unsigned char)((fg_rgb & 0xFF0000) >> 0xF),
			(unsigned char)((fg_rgb & 0x00FF00) >> 0x8),
			(unsigned char)(fg_rgb & 0x0000FF));
	return close_buffer(buff);
}

std::string
Color::bg(unsigned char r, unsigned char g, unsigned char b,
	Color::STYLE style)
{
	std::stringstream	buff;

	init_buffer(buff);
	if (style == Color::STYLE::NONE)
		buff << "0;";
	else if ((int)style > 0)
		add_style(buff, (int)style);
	add_bg(buff, r, g, b);
	return close_buffer(buff);
}
std::string
Color::bg(unsigned int bg_rgb,
	Color::STYLE style)
{
	std::stringstream	buff;

	init_buffer(buff);
	if (style == Color::STYLE::NONE)
		buff << "0;";
	else if ((int)style > 0)
		add_style(buff, (int)style);
	add_bg(buff, (unsigned char)((bg_rgb & 0xFF0000) >> 0xF),
			(unsigned char)((bg_rgb & 0x00FF00) >> 0x8),
			(unsigned char)(bg_rgb & 0x0000FF));
	return close_buffer(buff);
}


FDV_END_NAMESPACE
