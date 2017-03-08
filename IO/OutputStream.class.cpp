/*******************************************************************************
 * fdaudre-@student.42.fr
 *
 *
 ******************************************************************************/

#include "OutputStream.class.hpp"

#include <iostream>

FDV_BEGIN_NAMESPACE

OutputStream	error("error", std::cerr, OutputStream::NORMAL),
				warn("warning", std::cerr, OutputStream::NORMAL),
				info("info", std::cout, OutputStream::VERBOSE),
				debug("debug", std::cout, OutputStream::DEBUG);

int				OutputStream::_Level = OutputStream::DEBUG;

OutputStream::OutputStream(std::string title,
						   std::ostream & os,
						   VERBOSITY_LEVEL level) :
	_title(title),
	_os(os),
	_l(level)
{
	_name = title;
}

OutputStream::~OutputStream(void)
{
}


void
OutputStream::setLevel(int level)
{
	if (level < 0 or level > 4)
		throw std::runtime_error(std::string("Bad output level: ") + std::to_string(level));
	_Level = level;
}

FDV_END_NAMESPACE
