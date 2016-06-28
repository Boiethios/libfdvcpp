/*******************************************************************************
 * fdaudre-@student.42.fr
 *
 *
 ******************************************************************************/

#ifndef		__FDV__CONFIGFILE_CLASS__
# define	__FDV__CONFIGFILE_CLASS__

# include "IO/OutputStream.class.hpp"
# include "Core/Object.abstract.hpp"
# include "Misc/stringConvert.hpp"

# include <map>
# include <sstream>

FDV_BEGIN_NAMESPACE

class ConfigFile : public Object
{
	public:
		class Map;

		template<typename T>
		class Type
		{
			friend class Map;

				Map &				_section;
				std::string const	_key;

				Type(Map const *section, std::string const & key) :
					_section(*const_cast<Map *>(section)),
					_key(key)
				{
				}

			public:
				Type<T> &
				operator=(T const & value)
				{
					std::ostringstream	oss;

					oss << value;
					_section[_key] = oss.str();
					return *this;
				}

				operator T (void) const
				{
					std::istringstream	iss(_section.at(_key));
					T					ans;

					iss >> ans;
					if (iss.rdbuf()->in_avail())
						warn(std::string("Entry `") + iss.str() +
								"` is not well formated.");
					return ans;
				}
		};

		class Map : private std::unordered_map<std::string, std::string>
		{
			typedef std::unordered_map<std::string, std::string> Mother;

			template<typename T>
			friend class Type;
			friend class ConfigFile;

				std::string &
				operator[](std::string const & item);
				std::string &
				at(std::string const & item);

			public:
				void
				clear(void);
				void
				erase(std::string const & item);

				Map::const_iterator
				begin(void) const;
				Map::const_iterator
				end(void) const;

				bool
				exists(std::string const & item) const;

				template<typename T> Type<T>
				get(std::string const & item);
		};

		ConfigFile(void);
		ConfigFile(std::string const & filename);

		ConfigFile(ConfigFile const &) = delete;
		ConfigFile &
		operator=(ConfigFile const &) = delete;

		ConfigFile(ConfigFile &&) = default;
		ConfigFile &
		operator=(ConfigFile &&) = default;


		void
		clear(void);
		void
		change(std::string const & filename);
		void
		remove(std::string const & section);


//		Map::const_iterator
//		begin(void) const;
//		Map::const_iterator
//		end(void) const;


		Map &
		operator()(std::string const & section);
		Map &
		operator()(void);

		bool
		exists(std::string const & section);
		bool
		exists(std::string const & section, std::string const & key);

	private:
		std::unordered_map<std::string, Map>
					_sections;
		std::string	_filename;

		void
		_open(void);
};

FDV_END_NAMESPACE

template<typename T>
std::ostream &
operator<<(std::ostream & os, fdv::ConfigFile::Type<T> const & value)
{
	os << static_cast<T>(value);
	return os;
}

#include "IO/ConfigFile.class.inline.hpp"

#endif // __FDV__CONFIGFILE_CLASS__
