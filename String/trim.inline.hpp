/*******************************************************************************
 * fdaudre-@student.42.fr
 *
 *
 ******************************************************************************/

#ifndef		__FDV__TRIM_INLINE__
# define	__FDV__TRIM_INLINE__

# include "Core/macro.hpp"

# include <string>

FDV_BEGIN_NAMESPACE

inline std::string &
str_rtrim(std::string & str, std::string const & trim_chars = " \t")
{
	std::size_t	pos(str.find_last_not_of(trim_chars));

	if(std::string::npos != pos)
		str = str.substr(0, pos + 1);
	return str;
}

inline std::string &
str_ltrim(std::string & str, std::string const & trim_chars = " \t")
{
	std::size_t	pos(str.find_first_not_of(trim_chars));

	if(std::string::npos != pos)
		str = str.substr(pos);
	return str;
}

inline std::string &
str_trim(std::string & str)
{
	return str_ltrim(str_rtrim(str));
}

FDV_END_NAMESPACE

#endif // __FDV__TRIM_INLINE__
