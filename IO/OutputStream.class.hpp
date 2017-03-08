/*******************************************************************************
 * fdaudre-@student.42.fr
 *
 *
 ******************************************************************************/

#ifndef		__FDV__OUTPUTSTREAM_CLASS__
# define	__FDV__OUTPUTSTREAM_CLASS__

# include "Core/Object.abstract.hpp"

# include <sstream>

namespace
{
	inline void
	buffurize(std::stringstream &)
	{
	}
	template<typename T> void
	buffurize(std::stringstream & buff, T arg)
	{
		buff << arg;
	}
	template<typename T, typename ...TARGS> void
	buffurize(std::stringstream & buff, T first_arg, TARGS... other_args)
	{
		buff << first_arg << " ";
		buffurize(buff, other_args...);
	}
}

FDV_BEGIN_NAMESPACE

class OutputStream : public Object
{
	public:
		enum VERBOSITY_LEVEL
		{
			NO_OUTPUT	= 0,
			NORMAL		= 1,
			VERBOSE		= 2,
			DEBUG		= 3,
		};

		OutputStream(std::string title,
					 std::ostream & os,
					 VERBOSITY_LEVEL level = NORMAL);
		~OutputStream(void);

		static void
		setLevel(int level);

		template<typename ...TARGS> void
		operator()(TARGS... targs)
		{
			if (_l > _Level)
				return ;

			std::stringstream	buff;

			buff << "[" << _title << "] ";
			buffurize(buff, targs...);
			buff << "\n";
			_os << buff.str();
		}

	private:
		std::string			_title;
		std::ostream &		_os;
		int					_l;

		static int			_Level;
};

extern OutputStream		error,
						warn,
						info,
						debug;

FDV_END_NAMESPACE

#endif // __FDV__OUTPUTSTREAM_CLASS__
