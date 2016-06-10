/*******************************************************************************
 * fdaudre-@student.42.fr
 *
 *
 ******************************************************************************/

#ifndef		__FDV__MAKE_ARRAY_TEMPLATE__
# define	__FDV__MAKE_ARRAY_TEMPLATE__

#include "Core/macro.hpp"

FDV_BEGIN_NAMESPACE

template<class Function, std::size_t... Indices>
constexpr auto make_array_helper(Function f, std::index_sequence<Indices...>)
	-> std::array<typename std::result_of<Function(std::size_t)>::type, sizeof...(Indices)>
{
	return {{ f(Indices)... }};
}

template<int N, class Function>
constexpr auto make_array(Function f)
	-> std::array<typename std::result_of<Function(std::size_t)>::type, N>
{
	return make_array_helper(f, std::make_index_sequence<N>{});
}

FDV_END_NAMESPACE

#endif // __FDV__MAKE_ARRAY_TEMPLATE__
