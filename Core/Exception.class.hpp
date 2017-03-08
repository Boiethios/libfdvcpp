/*******************************************************************************
 * fdaudre-@student.42.fr
 *
 *
 ******************************************************************************/

#pragma once

#include "Core/macro.hpp"

#include <exception>

FDV_BEGIN_NAMESPACE

class Exception : public std::exception
{
	public:
		Exception(std::string const & what);
		~Exception(void);
};

FDV_END_NAMESPACE
