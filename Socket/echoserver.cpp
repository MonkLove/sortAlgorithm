/*************************************************************************\
**  Copyright(C)2016 All Rights Reserved
**
**  File Name    : epollserver.cpp
**  Author       : Quasimodo
**  Created Time : 2016-11-09
**  Description  :
*************************************************************************/

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <inttypes.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

uint32_t sock_init(uint16_t port)
{
	uint32_t listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if(listenfd < 0){
		perror("socket");
		exit(0);
	}
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;
	int ret = bind(listenfd, (struct sockaddr*)&addr, sizeof(addr));
	if(ret < 0){
		perror("bind");
		exit(1);
	}

	int flag = 1;
	ret = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));
	if(ret < 0){
		perror("setsockopt");
	}
	ret = listen(listenfd, 512);
	if(ret < 0){
		perror("listen");
		exit(1);
	}
	return listenfd;
}

void echo(uint32_t connfd)
{
	char buf[1024] = {};
	uint16_t len = 0;
	while(1){
		len = recv(connfd, buf, sizeof(buf), 0);
		if(recv > 0){
			send(connfd, buf, sizeof(buf), 0);
		}else if(recv < 0){
			if(errno == EINTR)
				continue;
			break;
		}
	}
	close(connfd);
}

int main(int argc, char* argv[])
{

	uint32_t connfd;
	uint32_t listenfd = sock_init(8000);

	while(1){
		connfd = accept(listenfd, NULL, NULL);
		if(connfd > 0){
			pid_t pid = fork();
			if(pid < 0){
				perror("fork");
				continue;
			}
			if(pid == 0){
				echo(connfd);
			}
		}else{
			if(errno == EINTR)
				continue;
			break;
		}
	
	}
	close(listenfd);
	return 0;
}
