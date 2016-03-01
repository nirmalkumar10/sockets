#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
int main(int argc, char *argv[])
{    
    int clientSocket,port;
    char buffer[1024];
    struct sockaddr_in serverAddr;
    socklen_t addr_size;
    FILE *input = stdin;
    clientSocket = socket(PF_INET, SOCK_STREAM, 0);

    if(argc < 2 ){
	printf("usage format cat file_name | ./netcat server-ip server-port\r\n");
	}
	port = atoi(argv[2]);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
							//   serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    inet_aton(argv[1],&serverAddr.sin_addr);
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

    addr_size = sizeof serverAddr;
    connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
	
    while ( fgets(buffer,1024,input) !=  NULL )
        send(clientSocket,buffer, 1024, 0);


    return 0;
}
