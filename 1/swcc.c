#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>


void main(int argc, char* argv[])
{
int sockfd,newsockfd,port,n;
struct sockaddr_in serv_addr,cnt_addr;
socklen_t len;
char *ip="127.0.0.1";
char buffer[1024];

port=atoi(argv[1]);
sockfd=socket(AF_INET,SOCK_DGRAM,0);
serv_addr.sin_family=AF_INET;
serv_addr.sin_port=htons(port);
serv_addr.sin_addr.s_addr=inet_addr(ip);

int ws=5;
int packet=0;
int lp=20;

len=sizeof(serv_addr);

while(packet<=lp)
{
for(int i=0;i<ws && packet<=lp;i++)
{
printf("\nSENDING PACKET : %d",packet);
//send(sockfd,&packet,sizeof(packet),0);
sendto(sockfd,&packet,sizeof(packet),0,(struct sockaddr *)&serv_addr,len);
packet++;
}


for(int i=0;i<ws && packet<=lp;i++)
{
int ack;
//recv(sockfd,&ack,sizeof(ack),0);
recvfrom(sockfd,&ack,sizeof(ack),0,(struct sockaddr *)&serv_addr,&len);
printf("\nRECEIVED ACK FOR PACKET : %d",ack);
}



}
packet=-1;
//send(sockfd,&packet,sizeof(packet),0);
sendto(sockfd,&packet,sizeof(packet),0,(struct sockaddr *)&serv_addr,len);

close(sockfd);
}

