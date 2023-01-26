#include <stdio.h>
#include<string.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<unistd.h>	//write

int main(int argc , char *argv[])
{
	int socket_desc;
	struct sockaddr_in server;
	int n;
	char buf[256];
	
	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
	
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(8888);
	
	//Connect
	if(connect(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("bind failed");
		return 1;
	}
	puts("bind done");
  
	//generate random number
	bzero(buf, sizeof(buf));
	
	bzero(buf, 256);
	n = read(socket_desc, buf, 255);
	if(n < 0)
		perror("Error socket");
	printf("Random Number: %s\n", buf);
	close(socket_desc);
	
	return 0;
}
