/*******************************************************************************
 * fdaudre-@student.42.fr
 *
 *
 ******************************************************************************/

#include "Core/macro.hpp"
#include "IO/Logger.class.hpp"

FDV_BEGIN_NAMESPACE

Logger			out("ERROR", false);
Logger			log("log");
Logger			warning("warning");
Logger			error("error");

Logger::File	Logger::mfile;
std::mutex		Logger::mshutup_dude;

Logger::Logger(std::string const & level, bool write_in_file) :
	mlevel(level), misInFile(write_in_file)
{
}
Logger::~Logger(void)
{
}


/* Logger::Debug class */
Logger		Logger::cdbg__("debug");

Logger::Debug::Debug(std::string const &file, int line) :
	mcompilfile(file), mcompilline(line)
{
}


/* Logger::File class */
Logger::File::File(std::string const & log_path) :
	mlog_path(log_path), mnum(this->init_num()),
	mfd(this->open(this->name(mnum)))
{
}

Logger::File::~File(void)
{
	close(mfd);
}


std::size_t		Logger::File::init_num(void)
{
	std::size_t		n = 0;

	//Creating the log directory
	struct stat		st;
	if (not ((!stat(mlog_path.c_str(), &st)) and S_ISDIR(st.st_mode)))
		if (mkdir(mlog_path.c_str(), 0771) < 0)
			fdv::out("Cannot create log directory : ",
					fdv::color(0xDD4444u), strerror(errno), fdv::color());

	for (struct stat st;
		 (not stat(this->name(n).c_str(), &st)) and ((std::size_t)st.st_size > mmax_size);
		 ++n)
		;
	return n;
}
std::string		Logger::File::name(std::size_t num)
{
	std::stringstream	ss;

	ss	<< mlog_path << "/"
		<< Time::format("%Y_%b_%d.", false)
		<< std::setfill('0') << std::setw(3) << num
		<< ".log";
	return ss.str();
}


int				Logger::File::open(std::string const name)
{
	int fd(::open(name.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0660));

	if (fd < 0)
		fdv::out("Cannot open ", this->name(mnum), " : ",
				fdv::color(0xDD4444u), strerror(errno), fdv::color());
	return (fd);
}

bool			Logger::File::write(std::string const & buff)
{
	struct stat	st;

	if ((not fstat(mfd, &st)) and ((std::size_t)st.st_size > mmax_size))
	{
		mshutup_dude.lock();
			struct stat	st;
			if ((not fstat(mfd, &st)) and ((std::size_t)st.st_size > mmax_size))
			{ // double check
				int		old_fd(mfd);

				// TODO éviter de rappeler name() à chaque fois
				mfd = this->open(this->name(++mnum));
				close(old_fd);
			}
		mshutup_dude.unlock();
	}
	if (::write(mfd, buff.c_str(), buff.size()) < 0)
		return false;
	return true;
}

FDV_END_NAMESPACE
