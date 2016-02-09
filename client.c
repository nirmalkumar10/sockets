#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char ** argv)
{
	int port;
	int sock = -1;
	struct sockaddr_in address; /*  An IP socket address is defined as a combination of an IP interface address and a 16-bit port number*/
	struct hostent * host;
	int len;
	
	/* checking commandline parameter */
	if (argc != 4)
	{
		printf("usage: %s hostname port text\n", argv[0]);
		return -1;
	}

	/* obtain port number */
	if (sscanf(argv[2], "%d", &port) <= 0)
	{
		fprintf(stderr, "%s: error: wrong parameter: port\n", argv[0]);
		return -2;
	}

	/* create socket */
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock <= 0)
	{
		fprintf(stderr, "%s: error: cannot create socket\n", argv[0]);
		return -3;
	}

	/* connect to server */
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	host = gethostbyname(argv[1]);
	if (!host)
	{
		fprintf(stderr, "%s: error: unknown host %s\n", argv[0], argv[1]);
		return -4;
	}
	memcpy(&address.sin_addr, host->h_addr_list[0], host->h_length);
	printf("host address:%d:%d\r\n", host->h_addr_list[0][0],host->h_length);
	if (connect(sock, (struct sockaddr *)&address, sizeof(address)))   /* tries to connect this socket with the socket (IP address and port										   ) of the remote host.*/ /*3-Way handshake ? */
	{
		fprintf(stderr, "%s: error: cannot connect to host %s\n", argv[0], argv[1]);
		return -5;
	}
/*we have not bind our client socket on a particular port as client generally use port assigned by kernel as client can have its socket associated with any port */
/*Once the sockets are connected, the server sends the data (date+time) on clients socket through clients socket descriptor and client can read it through normal read call on the its socket descriptor.*/
	/* send text to server */
	len = strlen(argv[3]);
	write(sock, &len, sizeof(int));
	write(sock, argv[3], len);

	/* close socket */
	close(sock);

	return 0;
}

