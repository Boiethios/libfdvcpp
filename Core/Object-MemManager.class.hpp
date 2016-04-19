/*******************************************************************************
 * fdaudre-@student.42.fr
 *
 *
 ******************************************************************************/

#ifndef		__FDV__OBJECT_MEMMANAGER_ABSTRACT__
# define	__FDV__OBJECT_MEMMANAGER_ABSTRACT__

#include "Core/Object.abstract.hpp"

FDV_BEGIN_NAMESPACE

class Object::MemManager
{
		struct Infos
		{
			std::size_t		size;
			std::string		file;
			int				line;
			bool			array;
		};

	public:
		static MemManager &
		Instance(void);

		void *
		alloc(std::size_t size, std::string const & file, int line, bool is_array);

		void
		free(void *ptr);

	private:
		MemManager(void);
		~MemManager(void);

		std::unordered_map< void *, Infos >		_stored_allocs;
};

FDV_END_NAMESPACE

#endif // __FDV__OBJECT_MEMMANAGER_ABSTRACT__
