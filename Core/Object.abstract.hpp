/*******************************************************************************
 * fdaudre-@student.42.fr
 *
 *
 ******************************************************************************/

#ifndef		__FDV__OBJECT_ABSTRACT__
# define	__FDV__OBJECT_ABSTRACT__

# include "Core/macro.hpp"

# include <cstdlib>
# include <string>
# include <unordered_map>

FDV_BEGIN_NAMESPACE

class Object
{
		class MemManager;

	public:
		virtual ~Object(void);

		static void *
		operator new (std::size_t size, std::string const & file = "unknown",
					  int line = -1);
		static void *
		operator new[] (std::size_t size, std::string const & file = "unknown",
						int line = -1);

		static void
		operator delete (void *ptr);
		static void
		operator delete[] (void *ptr);

		std::string const &
		name(void) const;
		void
		name(std::string const & new_name);

	protected:
		Object(void);

		std::string		_name = "fdv::Object";
};

FDV_END_NAMESPACE

#include "Core/Object-MemManager.class.hpp"

#endif // __FDV__OBJECT_ABSTRACT__
