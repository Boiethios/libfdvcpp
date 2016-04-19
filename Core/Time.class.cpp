/*******************************************************************************
 * fdaudre-@student.42.fr
 *
 *
 ******************************************************************************/

#include "Core/Time.class.hpp"

FDV_BEGIN_NAMESPACE

std::chrono::time_point<std::chrono::high_resolution_clock> Time::now(void)
{
	return std::chrono::high_resolution_clock::now();
}

std::string Time::format(std::string const & style, bool millisecond)
{
	auto						now(std::chrono::high_resolution_clock::now());
	auto						ms(std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()));
	std::time_t					t(std::time(NULL));
	std::size_t constexpr		count(0x20);
	char						buff[count];

	std::strftime(buff, count, style.c_str(), std::localtime(&t));

	std::stringstream			ss;
	ss << buff;
	if (millisecond)
		ss << "." << std::setfill('0') << std::setw(3) << ms.count() % 1000;

	return ss.str();
}

FDV_END_NAMESPACE
