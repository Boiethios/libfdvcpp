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

#include <iostream>
FDV_BEGIN_NAMESPACE

class ConfigFile
{
	public:
		typedef std::unordered_map<std::string, std::string>	Map;

		ConfigFile(void);
		ConfigFile(std::string const & filename);


		void
		open(std::string const & filename);

		inline void
		clear(void) {_values.clear();}


		inline Map::const_iterator
		begin(void) const {return _values.begin();}
		Map::const_iterator
		end(void) const {return _values.end();}


		inline bool
		exists(std::string const & key) {return _values.find(key) != _values.end();}

		std::string
		operator[](std::string const & key);

		template<typename T> T
		get(std::string const & key)
		{
			std::istringstream	iss(_values.at(key));
			T					ans;

			iss >> ans;
			if (iss.rdbuf()->in_avail())
				warn(std::string("`") + iss.str() + "` badly formated");
			return ans;
		}

	private:
		Map		_values;
};

FDV_END_NAMESPACE

#endif // __FDV__CONFIGFILE_CLASS__
