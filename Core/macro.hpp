/*******************************************************************************
 * fdaudre-@student.42.fr
 * 
 * 
 ******************************************************************************/

#ifndef		__FDV__MACRO__
# define	__FDV__MACRO__

#define FDV_BEGIN_NAMESPACE		namespace fdv {
#define FDV_END_NAMESPACE		}

#define FDV_XSTRINGIFY(s)		FDV_STRINGIFY(s)
#define FDV_STRINGIFY(s)		#s

#define FDV_NEW					new(__FILE__, __LINE__)

#define FDV_DEBUG				fdv::Logger::Debug(__FILE__, __LINE__)

#endif // __FDV__MACRO__
