#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>



void main(int argc, char *argv[])
{

int sockfd,nwsockfd;
struct sockaddr_in serv_addr,client_addr;
char buffer[1024];
socklen_t len;
char *ip="127.0.0.1";

int port=atoi(argv[1]);

sockfd=socket(AF_INET,SOCK_DGRAM,0);
serv_addr.sin_family=AF_INET;
serv_addr.sin_port=htons(port);
serv_addr.sin_addr.s_addr=inet_addr(ip);

len=sizeof(client_addr);
int b,hra,dt,pt,epf;

bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));



bzero(buffer,0);
recvfrom(sockfd,buffer,1024,0,(struct sockaddr *)&client_addr,&len);

sscanf(buffer,"%d %d %d %d %d",&b,&hra,&dt,&pt,&epf);
int n=b+hra+dt-pt-epf;
printf("%d",n);
bzero(buffer,1024);
sprintf(buffer,"RESULT : %d",n);
sendto(sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&client_addr,sizeof(client_addr));



close(sockfd);
}
