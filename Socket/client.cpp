/*************************************************************************\
**  Copyright(C)2016 All Rights Reserved
**
**  File Name    : client.cpp
**  Author       : Quasimodo
**  Created Time : 2016-11-09
**  Description  :
*************************************************************************/

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <cstdio>
#include <cstdlib>
#include <arpa/inet.h>
#include <errno.h>
#include <cstring>
using namespace std;


int main(int argc, char* argv[])
{

	uint32_t connfd = socket(AF_INET, SOCK_STREAM, 0);
	if(connfd < 0){
		perror("socket");
		exit(1);
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8000);
	inet_pton(AF_INET, "192.168.11.46", &addr.sin_addr);
	int ret = connect(connfd, (struct sockaddr*)&addr, sizeof(addr));
	if(ret < 0){
		perror("connect");
		exit(1);
	}

	char buf[1024] = "Hello Audrey";
	while(1){
		int len = send(connfd, buf, sizeof(buf), 0);
		if(len > 0){
		    recv(connfd, buf, sizeof(buf), 0);
			printf("Echo : %s\n", buf);
		}else if(len == 0){
			close(connfd);
		}else{
			if(errno == EAGAIN)
				continue;
			break;
		}
		sleep(1);
	}

	return 0;
}
