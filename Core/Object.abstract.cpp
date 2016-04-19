/*******************************************************************************
 * fdaudre-@student.42.fr
 *
 *
 ******************************************************************************/

#include "Core/Object.abstract.hpp"

#include <iostream>
FDV_BEGIN_NAMESPACE

Object::Object(void)
{
}

Object::~Object(void)
{
}


void *
Object::operator new(std::size_t size, std::string const & file, int line)
{
	return MemManager::Instance().alloc(size, file, line, false);
}
void *
Object::operator new[] (std::size_t size, std::string const & file, int line)
{
	return MemManager::Instance().alloc(size, file, line, true);
}

void
Object::operator delete (void *ptr)
{
	MemManager::Instance().free(ptr);
}
void
Object::operator delete[] (void *ptr)
{
	MemManager::Instance().free(ptr);
}


std::string const &
Object::name(void) const
{
	return _name;
}
void
Object::name(std::string const & new_name)
{
	_name = new_name;
}


FDV_END_NAMESPACE

