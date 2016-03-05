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

#define MSGCOUNT 1
#define START_SEQ 30

int main(int argc,char *argv[])
{
	struct sockaddr_in server, si_other;
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
	slen = sizeof(si_other);	

	buf = (char *)malloc((sizeof(char) * msgsize));

	if ((s=socket(PF_INET, SOCK_DGRAM, 0))==-1)

	memset((char *) &server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(portno);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(s, (struct sockaddr *)&server, sizeof(server))==-1)
		printf("bind error \n");

	while(msgcount) {
		recvd = recvfrom(s,buf, msgsize, 0,(struct sockaddr *)&si_other,&slen);
		seqno = (buf[1] << 8 | buf[0]) ;
		debug_print("sequence number:%d\r\n",seqno);
		debug_print("recieved:%d bytes\n",recvd);
		usleep(slptime * 1000);	
		ack = seqno;	
		sendto(s,&ack,sizeof(ack),0,(struct sockaddr *)&si_other,slen);
		msgcount--;
	}
	debug_print("Received packet from %s:%d\n\n\n", 
			inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
	free(buf);	
	close(s);
	return 0;
}
