#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<WinSock2.h>

int main()
{
    char server_mesg[256] = "You have reached the server.";

    // create server socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // define the server address
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = 9001;
    server_addr.sin_addr.s_addr = INADDR_ANY;   //0x000000000

    // bind the socket to specified IP address and port
    int bind_status = bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    
    if (bind_status == -1)
        printf("There was an error when binding the socket to specified IP address and port.\n");

    listen(server_socket, 5);    // server socket listens on other sockets from client side

    int client_socket;
    // the server accepts a socket from an incoming client connection
    //client_socket = accept(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    client_socket = accept(server_socket, NULL, NULL);

    int count = send(client_socket, server_mesg, sizeof(server_mesg), 0);
    printf("The server sent %s to the client.\n", server_mesg);
    printf("%d bytes in total\n", count);

    close(server_socket);
    return 0;
}
