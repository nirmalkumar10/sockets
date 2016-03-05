
#include "common.h"

#define MSGCOUNT 1
#define START_SEQ 30

int main(int argc,char *argv[])
{
	struct sockaddr_in server,client;
	struct timeval  tv1, tv2;
	socklen_t slen;
	int s, portno,msgsize,ack,msgcount,seqno;
	char *buf;
	double time_elapsed;
	msgcount = MSGCOUNT;
	portno = atoi(argv[2]);
	msgsize = atoi(argv[3]);
	slen = sizeof(server);
	seqno = START_SEQ;	
	
	buf = (char *)malloc((sizeof(char) * msgsize));
	buf[0] = (seqno & 0x00FF);
	buf[1] = ((seqno >> 8 ) & 0xFF);
	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)

	memset((char *) &server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(portno);
	if (inet_aton(argv[1], &server.sin_addr)==0) {
		fprintf(stderr, "inet_aton() failed\n");
		exit(1);
	}
	gettimeofday(&tv1, NULL);
	while(msgcount) {	
	sendto(s, buf,msgsize, 0,(struct sockaddr *)&server,slen);
	recvfrom(s,&ack,sizeof(ack),0,(struct sockaddr *)&client,&slen);
	msgcount--;
	}
	gettimeofday(&tv2, NULL);


	time_elapsed = (double) (tv2.tv_sec - tv1.tv_sec) + ((double)(tv2.tv_usec - tv1.tv_usec) / 1000000 )  ;
	printf("time elapsed :%f seconds",time_elapsed);
	printf("Total message size :%d\r\n",MSGCOUNT * msgsize);
	printf("Throughput :%f\r\n", (MSGCOUNT * msgsize) / time_elapsed);
	close(s);
	return 0;
}
