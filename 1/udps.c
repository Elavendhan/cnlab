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

bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));


while(1)
{

bzero(buffer,1024);
len=sizeof(serv_addr);
recvfrom(sockfd,buffer,1024,0,(struct sockaddr *)&serv_addr,&len);
//n=read(sockfd,buffer,1024);
printf("\nClient ---> %s",buffer);

bzero(buffer,1024);
fgets(buffer,1024,stdin);
sendto(sockfd,buffer,1024,0,(struct sockaddr *)&serv_addr,sizeof(serv_addr));


if(!strncmp("bye",buffer,3))
{
break;
}
}

//close(newsockfd);
//close(sockfd);
}
