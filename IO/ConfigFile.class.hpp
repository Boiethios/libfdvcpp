/*******************************************************************************
 * fdaudre-@student.42.fr
 *
 *
 ******************************************************************************/

#ifndef		__FDV__CONFIGFILE_CLASS__
# define	__FDV__CONFIGFILE_CLASS__

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


		Map::const_iterator
		begin(void) const;
		Map::const_iterator
		end(void) const;


		std::string
		operator[](std::string const & key);

		template<typename T> T
		get(std::string const & key)
		{
			std::istringstream	iss(_values.at(key));
			T					ans;

			iss >> ans;
			if (iss.rdbuf()->in_avail())
				std::cout << "Warning: " << iss.str() << "\n";
			return ans;
		}

	private:
		Map		_values;
};

FDV_END_NAMESPACE

#endif // __FDV__CONFIGFILE_CLASS__
