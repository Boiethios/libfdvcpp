/*******************************************************************************
 * fdaudre-@student.42.fr
 *
 *
 ******************************************************************************/

#ifndef		__FDV__STRINGCONVERT_CLASS__
# define	__FDV__STRINGCONVERT_CLASS__

#include "Core/macro.hpp"

#include <string>

FDV_BEGIN_NAMESPACE

template<typename T> T
stringTo(std::string const &, int base, std::size_t *idx);
template<typename T> T
stringTo(std::string const &, std::size_t *idx);

template<> inline double
stringTo<double>(std::string const & str, std::size_t *idx)
{
	return std::stod(str, idx);
}

template<> inline float
stringTo<float>(std::string const & str, std::size_t *idx)
{
	return std::stof(str, idx);
}

template<> inline long double
stringTo<long double>(std::string const & str, std::size_t *idx)
{
	return std::stold(str, idx);
}

template<> inline int
stringTo<int>(std::string const & str, int base, std::size_t *idx)
{
	return std::stoi(str, idx, base);
}

template<> inline long
stringTo<long>(std::string const & str, int base, std::size_t *idx)
{
	return std::stol(str, idx, base);
}

template<> inline long long
stringTo<long long>(std::string const & str, int base, std::size_t *idx)
{
	return std::stoll(str, idx, base);
}

template<> inline unsigned long
stringTo<unsigned long>(std::string const & str, int base, std::size_t *idx)
{
	return std::stoul(str, idx, base);
}

template<> inline unsigned long long
stringTo<unsigned long long>(std::string const & str, int base, std::size_t *idx)
{
	return std::stoull(str, idx, base);
}

FDV_END_NAMESPACE

#endif // __FDV__STRINGCONVERT_CLASS__
