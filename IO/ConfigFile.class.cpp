/*******************************************************************************
 * fdaudre-@student.42.fr
 *
 *
 ******************************************************************************/

#include "IO/ConfigFile.class.hpp"
#include "Misc/stringConvert.hpp"
#include "String/trim.inline.hpp"

#include <fstream>
#include <cstring>

FDV_BEGIN_NAMESPACE

ConfigFile::ConfigFile(void)
{
}

ConfigFile::ConfigFile(const std::string &filename)
{
	this->open(filename);
}


void
ConfigFile::open(std::string const & filename)
{
	std::ifstream	ifs(filename);

	if (not ifs.is_open())
		throw std::runtime_error(std::string("[ConfigFile::open] Cannot open ")
				+ filename + " (" + strerror(errno) + ")");

	std::string		line;
	std::size_t		idx;

	while (std::getline(ifs, line))
	{
		if (line.empty())
			continue ;
		if ((idx = line.find("=")) == std::string::npos)
			/*warning(),*/ continue ;

		std::string	key(line.substr(0, idx - 1));
		std::string	value(line.substr(idx + 1));

		_values[str_trim(key)] = str_trim(value);
	}
	ifs.close();
}


std::string
ConfigFile::operator[](std::string const & key)
{
	if (not this->exists(key))
		return "";
	return _values.at(key);
}


template<> std::string
ConfigFile::get<std::string>(std::string const & key)
{
	return _values.at(key);
}

FDV_END_NAMESPACE
