/*******************************************************************************
 * fdaudre-@student.42.fr
 *
 *
 ******************************************************************************/

#include "Core/AMain.abstract.hpp"

#include <iostream>
FDV_BEGIN_NAMESPACE

namespace
{
	inline std::vector<std::string>
	get_args(std::size_t argc, char *argv[])
	{
		std::vector<std::string>	args(argc);

		for (std::size_t i(0) ; i < argc ; ++i)
			args[i] = argv[i];
		return args;
	}
}


AMain::AMain(int argc, char *argv[]) :
	_args(get_args(static_cast<std::size_t>(argc), argv))
{
}

FDV_END_NAMESPACE
