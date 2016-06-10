/*******************************************************************************
 * fdaudre-@student.42.fr
 *
 *
 ******************************************************************************/

#ifndef		__FDV__AMAIN_ABSTRACT__
# define	__FDV__AMAIN_ABSTRACT__

# include "Core/Object.abstract.hpp"

# include <vector>
# include <string>

FDV_BEGIN_NAMESPACE

class AMain : public Object
{
	protected:
		std::vector<std::string> const	_args;

		AMain(int argc, char *argv[]);

		virtual int
		exec(void) = 0;
};

FDV_END_NAMESPACE

#endif // __FDV__AMAIN_ABSTRACT__
