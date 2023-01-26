#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int socket_desc, new_socket;
    struct sockaddr_in server, client_addr;
    char buf[256];
    int n;
    int r_num;
    
//Create socket
socket_desc = socket(AF_INET , SOCK_STREAM , 0);
if (socket_desc == -1)
{
	printf("Could not create socket");
}

//Prepare the sockaddr_in structure
server.sin_family = AF_INET;
server.sin_addr.s_addr = INADDR_ANY;
server.sin_port = htons(8888);

//Bind
if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
{
	puts("bind failed");
}
puts("bind done");

//Listen
listen(socket_desc , 3);

//Accept and incoming connection
puts("Waiting for incoming connections...");
socklen_t c_length = sizeof(client_addr);
new_socket = accept(socket_desc, (struct sockaddr *)&client_addr, (socklen_t*)&c_length);
if (new_socket<0)
{
perror("accept failed");
}

//Generate random number
srand(time(NULL));
r_num = (rand() % 900) + 100;

sprintf(buf, "%d", r_num);

n = write(new_socket, buf, sizeof(buf));

close(new_socket);
close(socket_desc);

return 0;

}
