/*******************************************************************************
 * fdaudre-@student.42.fr
 *
 *
 ******************************************************************************/

#ifndef		__FDV__CONFIGFILE_CLASS_INLINE__
# define	__FDV__CONFIGFILE_CLASS_INLINE__

# include "IO/ConfigFile.class.hpp"

#include <iostream>
FDV_BEGIN_NAMESPACE

/* ConfigFile::Map */
inline std::string &
ConfigFile::Map::operator[](std::string const & item)
{
	return this->Mother::operator[](item);
}
inline std::string &
ConfigFile::Map::at(std::string const & item)
{
	if (not this->exists(item))
		throw std::out_of_range(std::string("No item at key `") + item + "`");
	return this->Mother::operator[](item);
}

inline void
ConfigFile::Map::clear(void)
{
	this->clear();
}
inline void
ConfigFile::Map::erase(std::string const & item)
{
	this->erase(item);
}

inline ConfigFile::Map::const_iterator
ConfigFile::Map::begin(void) const
{
	return this->Mother::begin();
}
inline ConfigFile::Map::const_iterator
ConfigFile::Map::end(void) const
{
	return this->Mother::end();
}

inline bool
ConfigFile::Map::exists(std::string const & item) const
{
	return this->find(item) != this->end();
}

template<typename T> ConfigFile::Type<T>
ConfigFile::Map::get(std::string const & item)
{
	return Type<T>(this, item);
}


/* ConfigFile */
inline void
ConfigFile::clear(void)
{
	_sections.clear();
}

inline void
ConfigFile::change(std::string const & filename)
{
	_filename = filename;
	this->_open();
}

inline void
ConfigFile::remove(std::string const & section)
{
	_sections.erase(section);
}


//inline ConfigFile::Map::const_iterator
//ConfigFile::begin(void) const
//{
//	return _values.begin();
//}
//inline ConfigFile::Map::const_iterator
//ConfigFile::end(void) const
//{
//	return _values.end();
//}


inline ConfigFile::Map &
ConfigFile::operator()(std::string const & section)
{
	return _sections.operator[](section);
}
inline ConfigFile::Map &
ConfigFile::operator()(void)
{
	return _sections.operator[]("");
}


inline bool
ConfigFile::exists(std::string const & section)
{
	return _sections.find(section) != _sections.end();
}
inline bool
ConfigFile::exists(std::string const & section, std::string const & key)
{
	return this->exists(section) and this->operator()(section).exists(key);
}


FDV_END_NAMESPACE

#endif // __FDV__CONFIGFILE_CLASS_INLINE__
