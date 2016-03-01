#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc,char *argv[])
{
	int ssock, newSocket,port;
	char buffer[1024];
	struct sockaddr_in serverAddr;
	struct sockaddr_in serverStorage;
	socklen_t addr_size;

	if(argc < 2)
	{
	printf("Usage format ./netcatd port_number \r\n");
	exit(0);
	}
	port = atoi(argv[1]);
	ssock = socket(PF_INET, SOCK_STREAM, 0);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

	bind(ssock, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

	if(listen(ssock,1)== 0)
		fprintf(stderr,"Listening\n");
	else
		printf("Error\n");

	addr_size = sizeof serverStorage;
	newSocket = accept(ssock, (struct sockaddr *) &serverStorage, &addr_size);
	fprintf(stderr,"client ip:%s\n",inet_ntoa(serverStorage.sin_addr));
	fprintf(stderr,"client port:%d\n",serverStorage.sin_port);
	while(recv(newSocket,buffer,1024,0))
		puts(buffer);

	close(newSocket);
	return 0;
}
