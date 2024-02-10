#include "utils.hpp"

void setNonBlockingAndCloseOnExec(int fd)
{
	int flag = fcntl(fd, F_GETFL);
	if (flag < 0) {
		log_exit("fcntl", __LINE__, __FILE__, errno);
	} else {
		if (fcntl(fd, F_SETFL, flag | O_NONBLOCK) < 0) {
			log_exit("fcntl/F_SETFL", __LINE__, __FILE__, errno);
		}
		if (fcntl(fd, F_SETFD, FD_CLOEXEC) < 0) {
			log_exit("fcntl/F_SETFD", __LINE__, __FILE__, errno);
		}
	}
}

void setNonBlockingFd(int fd)
{
	int flag = fcntl(fd, F_GETFL);
	if (flag < 0) {
		log_exit("fcntl", __LINE__, __FILE__, errno);
	} else {
		if (fcntl(fd, F_SETFL, flag | O_NONBLOCK) < 0) {
			log_exit("fcntl/F_SETFL", __LINE__, __FILE__, errno);
		}
	}
}

void setCloseOnExec(int fd)
{
	if (fcntl(fd, F_SETFD, FD_CLOEXEC) < 0) {
		log_exit("fcntl/F_SETFD", __LINE__, __FILE__, errno);
	}
}