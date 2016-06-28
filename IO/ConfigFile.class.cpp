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
ConfigFile::write(void) const
{
	std::ofstream	ofs(_filename);

	if (not ofs.is_open())
	{
		error("Cannot open:", _filename, "for writing.");
		return ;
	}
	if (this->exists(""))
	{
		for (auto const & item : _sections.at(""))
			ofs << item.first << " = " << item.second << "\n";
		ofs << '\n';
	}
	for (auto const & section : _sections)
	{
		if (section.first.empty())
			continue ;
		ofs << '[' << section.first << "]\n";
		for (auto const & item : section.second)
			ofs << item.first << " = " << item.second << "\n";
		ofs << '\n';
	}
	ofs.close();
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

/* ConfigFile::Type */

// string specialization
template<> ConfigFile::Type<std::string> &
ConfigFile::Type<std::string>::operator=(std::string const & value)
{
	_section[_key] = value;
	return *this;
}
template<>
ConfigFile::Type<std::string>::operator std::string (void) const
{
	return _section.at(_key);
}

// bool specialization
template<> ConfigFile::Type<bool> &
ConfigFile::Type<bool>::operator=(bool const & value)
{
	_section[_key] = (value ? "true" : "talse");
	return *this;
}
template<>
ConfigFile::Type<bool>::operator bool (void) const
{
	std::string		str(_section.at(_key));

	for (auto & c: str)
		c = tolower(c);
	if (str == "true")
		return true;
	if (str == "false")
		return false;
	warn(std::string("Entry `") + str + "` is not a valid bool.");
	return false;
}

FDV_END_NAMESPACE
