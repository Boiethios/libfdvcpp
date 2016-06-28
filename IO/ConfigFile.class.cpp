/*******************************************************************************
 * fdaudre-@student.42.fr
 *
 *
 ******************************************************************************/

#include "IO/ConfigFile.class.hpp"
#include "IO/OutputStream.class.hpp"
#include "Misc/stringConvert.hpp"
#include "String/trim.inline.hpp"

#include <fstream>
#include <cstring>

FDV_BEGIN_NAMESPACE

ConfigFile::ConfigFile(void)
{
}

ConfigFile::ConfigFile(const std::string &filename) :
	_filename(filename)
{
	this->_open();
}


void
ConfigFile::_open(void)
{
	std::ifstream	ifs(_filename);

	_sections.clear();
	if (not ifs.is_open())
		return ;

	std::string		section;
	std::string		line;
	std::size_t		idx;

	while (std::getline(ifs, line))
	{
		str_trim(line);
		if (line.empty())
			continue ;
		if(line.front() == '[' and line.back() == ']')
		{
			section = line.substr(1, line.size() - 2);
			str_trim(section);
		}
		else if ((idx = line.find("=")) != std::string::npos)
		{
			std::string	key(line.substr(0, idx - 1));
			std::string	value(line.substr(idx + 1));
			_sections[section][str_rtrim(key)] = str_ltrim(value);
		}
		else
		{
			warn(std::string("In `") + _filename + "`: badly formated: `" + line + "`");
		}
	}
	ifs.close();
}

/* Map */
//TODO
//template<> std::string
//ConfigFile::Map::get<std::string>(std::string const & item) const
//{
//	return this->at(item);
//}

FDV_END_NAMESPACE
