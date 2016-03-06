/*
File        : spdtestd.c
Author      :Nirmal Kumar Venkatesan
SJSU ID     :010690706
Description :UDP server reads a message of specified
	     size and sleeps for specified time to simulate
	     network latency and sends ack to client it
	     received the message from.	
*/

#include "common.h"

#define MSGCOUNT 30
#define START_SEQ 30

int main(int argc,char *argv[])
{
	struct sockaddr_in server, client;
	socklen_t slen;
	int s, portno,msgsize,slptime,ack,msgcount,seqno,recvd;
	char *buf;
	if(argc < 4 ){ 
		printf("usage : ./spdtestd portno messagesize sleeptime \n" );
		exit(0);
	}

	msgcount = MSGCOUNT;
	portno = atoi(argv[1]);
	msgsize = atoi(argv[2]);
	slptime = atoi(argv[3]);
	slen = sizeof(client);	

	buf = (char *)malloc((sizeof(char) * msgsize));        /* Allocated buffer of specified size from user */

	if ((s=socket(PF_INET, SOCK_DGRAM, 0))==-1)
		perror("error in creating socket\n");

	memset((char *) &server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(portno);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(s, (struct sockaddr *)&server, sizeof(server))==-1)
		printf("bind error \n");

	while(msgcount) {
		recvd = recvfrom(s,buf, msgsize, 0,(struct sockaddr *)&client,&slen);
		seqno = (buf[1] << 8 | buf[0]);                                       /*LSB from first byte and MSB from second byte is used */
		debug_print("sequence number:%d\r\n",seqno);
		debug_print("received:%d bytes\n",recvd);
		usleep(slptime * 1000);	
		ack = seqno;	
		sendto(s,&ack,sizeof(ack),0,(struct sockaddr *)&client,slen);
		msgcount--;
	}
	debug_print("Received packet from %s:%d\n\n\n", 
			inet_ntoa(client.sin_addr), ntohs(client.sin_port));
	free(buf);	
	close(s);
	return 0;
}
