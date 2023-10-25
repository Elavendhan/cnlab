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


len=sizeof(serv_addr);
bzero(buffer,1024);

sockfd=socket(AF_INET,SOCK_DGRAM,0);
serv_addr.sin_family=AF_INET;
serv_addr.sin_port=htons(port);
serv_addr.sin_addr.s_addr=inet_addr(ip);

bzero(buffer,1024);
fgets(buffer,1024,stdin);
sendto(sockfd,buffer,1024,0,(struct sockaddr *)&serv_addr,sizeof(serv_addr));

bzero(buffer,1024);
recvfrom(sockfd,buffer,1024,0,(struct sockaddr *)&client_addr,&len);
printf("\nNET SALARY CALCULATED BY SERVER : %s",buffer);

close(sockfd);

}

