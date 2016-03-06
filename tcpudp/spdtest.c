/*
File        : spdtest.c
Author      :Nirmal Kumar Venkatesan
SJSU ID     :010690706
Description :UDP client writes a message of specified size
             to the server and waits for an ack from server.
	     Calculates throughput based on total message sent over
	     the specified delay.  	
*/

#include "common.h"

#define MSGCOUNT 30
#define START_SEQ 30

int main(int argc,char *argv[])
{
	struct sockaddr_in server,client;
	struct timeval  tv1, tv2;
	socklen_t slen;
	int s, portno,msgsize,ack,msgcount,seqno,total_message_size;
	char *buf;
	double time_elapsed;

	msgcount = MSGCOUNT;
	portno = atoi(argv[2]);
	msgsize = atoi(argv[3]);
	slen = sizeof(server);
	seqno = START_SEQ;	

	buf = (char *)malloc((sizeof(char) * msgsize));

	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
		perror("Error in creating socket\n");

	memset((char *) &server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(portno);
	if (inet_aton(argv[1], &server.sin_addr)==0) {
		fprintf(stderr, "inet_aton() failed\n");
		exit(1);
	}
	gettimeofday(&tv1, NULL);
	while(msgcount) {	
		buf[0] = (seqno & 0x00FF);                           /* LSB of sequence number in first byte of buffer */
		buf[1] = ((seqno >> 8 ) & 0xFF);                     /*MSB of sequence number in second byte of buffer */
		sendto(s, buf,msgsize, 0,(struct sockaddr *)&server,slen);
		recvfrom(s,&ack,sizeof(ack),0,(struct sockaddr *)&client,&slen);
		debug_print("Ack received:%d\n",ack);
		seqno++;
		msgcount--;
	}
	gettimeofday(&tv2, NULL);


	time_elapsed = (double) (tv2.tv_sec - tv1.tv_sec) + ((double)(tv2.tv_usec - tv1.tv_usec) / 1000000 )  ;
	debug_print("time elapsed :%f seconds",time_elapsed);
	debug_print("Total message size :%d\r\n",MSGCOUNT * msgsize);

	total_message_size = (MSGCOUNT * msgsize * 8);

	if(total_message_size > 1000){
		total_message_size = (total_message_size /1000);
		printf("Throughput :%f Kbps \n",total_message_size / time_elapsed );
	}

	if(total_message_size > 1000000){
		total_message_size = (total_message_size /1000000);
		printf("Throughput :%f Mbps \n",total_message_size / time_elapsed );
	}
	if(total_message_size > 1000000000){
		total_message_size = (total_message_size /1000000000);
		printf("Throughput :%f Gbps \n",total_message_size / time_elapsed );
	}
	close(s);
	return 0;
}
