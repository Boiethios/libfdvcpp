/*******************************************************************************
 * fdaudre-@student.42.fr
 *
 *
 ******************************************************************************/

#include "Core/Object-MemManager.class.hpp"

#include <iostream>
FDV_BEGIN_NAMESPACE

Object::MemManager &
Object::MemManager::Instance(void)
{
	static MemManager instance_;

	return instance_;
}

void *
Object::MemManager::alloc(std::size_t size, std::string const & file, int line,
						  bool is_array)
{
	Infos		alloc_infos{size, file, line, is_array};
	void		*ptr(::malloc(size));

	if (line < 0) // TODO
		std::cout << "Prefer using " FDV_STRINGIFY(FDV_NEW)
					" instead of new for fdv classes\n";
	_stored_allocs.emplace(ptr, alloc_infos);
	return ptr;
}

void
Object::MemManager::free(void *ptr)
{
	if (not _stored_allocs.erase(ptr))
		throw std::runtime_error("[MemManager::free] "
					"This does not point to allocated memory");
	::free(ptr);
}


Object::MemManager::MemManager(void)
{
}

Object::MemManager::~MemManager(void)
{
	if (not _stored_allocs.empty())
	{
		//TODO personnal logger
		std::cout << "Leaks :\n";
		for (auto const & elem : _stored_allocs)
		{
			if (elem.second.line < 0)
				std::cout	<< "\t[" << elem.first << "] "
							<< elem.second.size << " octets was not freed"
							<< (elem.second.array ? " (array)\n" : "\n");
			else
				std::cout	<< "\t[" << elem.first << "] ["
							<< elem.second.file << ":" << elem.second.line
							<< "] " << elem.second.size << " octets was not freed"
							<< (elem.second.array ? " (array)\n" : "\n");
		}
	}
}

FDV_END_NAMESPACE
