/*******************************************************************************
 * fdaudre-@student.42.fr
 *
 *
 ******************************************************************************/

#ifndef		__FDV__COLOR_CLASS__
# define	__FDV__COLOR_CLASS__

#include "Core/Object.abstract.hpp"

#include <string>
#include <sstream>

FDV_BEGIN_NAMESPACE

class Color
{
	public:
		enum STYLE
		{
			DEFAULT		= -1,
			NONE		= 1 << 0u,
			BOLD		= 1 << 1u,
			FAINT		= 1 << 2u,
			ITALIC		= 1 << 3u,
			UNDERLINE	= 1 << 4u,
			BLINK		= 1 << 5u,
			RAPID_BLINK	= 1 << 6u,
			REVERSE		= 1 << 7u,
			HIDDEN		= 1 << 8u,
		};

		Color(void);
		~Color(void);


		std::string
		operator()(STYLE style = STYLE::NONE);
		std::string
		operator()(unsigned int fg_rgb, STYLE style = STYLE::DEFAULT);
		std::string
		operator()(unsigned int fg_rgb, unsigned int bg_rgb, STYLE style = STYLE::DEFAULT);

		std::string
		fg(unsigned char r, unsigned char g, unsigned char b,
			STYLE style = STYLE::DEFAULT);
		std::string
		fg(unsigned int rgb,
			STYLE style = STYLE::DEFAULT);

		std::string
		bg(unsigned char r, unsigned char g, unsigned char b,
			STYLE style = STYLE::NONE);
		std::string
		bg(unsigned int rgb,
			STYLE style = STYLE::NONE);
};

Color::STYLE operator|(Color::STYLE style1, Color::STYLE style2);

extern Color color;

FDV_END_NAMESPACE

#endif // __FDV__COLOR_CLASS__
