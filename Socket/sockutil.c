#include "sockutil.h"

void sock_nonblock(uint32_t fd)
{
	int flag = fcntl(fd, F_GETFL);
	int ret = fcntl(fd, F_SETFL, flag | O_NONBLOCK);
	if(ret == -1)
	{
		perror("fcntl");
	}
}

void port_reuse(uint32_t fd)
{
	int flag = 1;
	setsockopt(fd, SOL_STREAM, SO_REUSEADDR, &flag, sizeof(flag));
}