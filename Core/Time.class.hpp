/*******************************************************************************
 * fdaudre-@student.42.fr
 *
 *
 ******************************************************************************/

#ifndef		__FDV__TIME_CLASS__
# define	__FDV__TIME_CLASS__

#include "Core/Object.abstract.hpp"

#include <chrono>
#include <sstream>
#include <iomanip>
#include <ctime>

FDV_BEGIN_NAMESPACE

class Time
{
	public:
		static std::chrono::time_point<std::chrono::high_resolution_clock>
		now(void);

		static std::string
		format(std::string const & style = "%d/%b/%y %T", bool millisecond = true);
};

FDV_END_NAMESPACE

#endif // __FDV__TIME_CLASS__
