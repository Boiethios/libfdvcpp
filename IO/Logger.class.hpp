/*******************************************************************************
 * fdaudre-@student.42.fr
 *
 *
 ******************************************************************************/

#pragma once

#include "Core/macro.hpp"
#include "Core/Object.abstract.hpp"
#include "Core/Time.class.hpp"
#include "IO/Color.class.hpp"

#include <cerrno>
#include <cstring>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <mutex>
#include <sstream>

FDV_BEGIN_NAMESPACE

class Logger;

extern Logger		out;
extern Logger		log;
extern Logger		warning;
extern Logger		error;

class Logger : public Object
{
		//! Log file handler
		class File
		{
				static constexpr std::size_t	mmax_size = 100000;

				std::string						mlog_path;
				std::size_t						mnum;
				int								mfd;

				std::size_t			init_num(void);
				std::string			name(std::size_t num);

				int					open(std::string const name);

			public:
				File(std::string const & log_path = "./log");
				~File(void);
				bool				write(const std::string & buff);
		};

		static Logger			cdbg__;

		static std::mutex		mshutup_dude;

		std::string const		mlevel;
		bool					misInFile;
		static File				mfile;

		bool					mdouble_output_in_standard = true;

		void buffurize(std::stringstream & buff)
		{
			(void)buff;
		}
		template<typename T>
		void buffurize(std::stringstream & buff, T arg)
		{
			buff << arg;
		}
		template<typename T, typename ...TARGS>
		void buffurize(std::stringstream & buff, T first_arg, TARGS... targs)
		{
			buff << first_arg;
			buffurize(buff, targs...);
		}

	public:
		Logger(std::string const & level, bool write_in_file = true);
		~Logger(void);

		template<typename ...TARGS>
		void operator()(TARGS... targs)
		{
			std::stringstream	buff;
			// date + time, type of log
			buff << "[" /*<< crf::Time::format()*/ << "] [" << mlevel << "] ";
			buffurize(buff, targs...);
			buff << "\n";
			if ((misInFile) and (not mfile.write(buff.str())))
			{
				out("Cannot write in log file : ",
						fdv::color(0xDD4444u), strerror(errno), fdv::color(),
						"\n\t->\t", fdv::color(Color::STYLE::FAINT), buff.str(), fdv::color());
			}
			else if (mdouble_output_in_standard)
			{
				::write(1, buff.str().c_str(), buff.str().size());
			}
		}

		class Debug
		{
				std::string			mcompilfile;
				int					mcompilline;

			public:
				Debug(std::string const & file, int line);

				template<typename ...TARGS>
				void operator()(TARGS... targs)
				{
					cdbg__(mcompilfile, ":", mcompilline, ": ", targs...);
				}
		};
};

FDV_END_NAMESPACE
