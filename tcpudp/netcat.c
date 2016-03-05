/*
File  : netcat.c
Author: Nirmal Kumar Venkatesan 
SJSU ID: 010690706

The client program connects to the server
specified in command line argument.
It reads data from stdin till EOF and
 closes its connection and exits
*/

#include "common.h"

int main(int argc, char *argv[])
{    
	int clientSocket,port,recvd;
	char buffer[1024];
	struct sockaddr_in serverAddr;
	socklen_t addr_size;
	FILE *input = stdin;
	clientSocket = socket(PF_INET, SOCK_STREAM, 0);

	if(argc < 2 ){
		printf("usage format cat <file_name> | ./netcat <server-ip> <server-port>\r\n");
	}

	port = atoi(argv[2]);
	
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	inet_aton(argv[1],&serverAddr.sin_addr);
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

	addr_size = sizeof(serverAddr);
	connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

	while ( !feof(input)){
		recvd =fread(buffer,1,sizeof(buffer),input);
	send(clientSocket,buffer, recvd, 0);
	}

	return 0;
}
