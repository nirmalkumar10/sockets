/*
File   :netcatd.c
Author :Nirmal Kumar Venkatesan
SJSU ID:010690706

Description: The server listens on a port, 
reads data from client and writes it to stdout

 */

#include "common.h"


int main(int argc,char *argv[])
{
	int ssock, newSocket,port,i,n;
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
		debug_print("%s","Listening\n");
	else
		debug_print("%s","Error\n");

	addr_size = sizeof(serverStorage);

	newSocket = accept(ssock, (struct sockaddr *) &serverStorage, &addr_size);

	fprintf(stderr,"client ip:%s\n",inet_ntoa(serverStorage.sin_addr));
	fprintf(stderr,"client port:%d\n",serverStorage.sin_port);

	while((n = recv(newSocket,buffer,1024,0)))
		for(i=0 ; i<n;i++)
			printf("%c",buffer[i]);

	close(newSocket);
	return 0;
}
