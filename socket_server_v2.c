#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>

int main()
{
    char server_mesg[256] = "'You have reached the server'";

    // create server socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // define the server address
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9002);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);   //0x000000000

    // bind the socket to specified IP address and port
    int bind_status = bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    
    if (bind_status == -1)
        printf("There was an error when binding the socket to specified IP address and port.\n");

    listen(server_socket, 5);    // server socket listens on other sockets from client side

    int client_socket;
    // the server accepts a socket from an incoming client connection
    struct sockaddr_in client_addr;
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(9001);
    client_addr.sin_addr.s_addr = ntohl(0xC0A80005);
    //client_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    int client_addr_len;
    client_addr_len = sizeof(client_addr);
    //client_socket = accept(server_socket, NULL, NULL);
    client_socket = accept(server_socket, (struct sockaddr *) &client_addr, &client_addr_len);

    int count = send(client_socket, server_mesg, sizeof(server_mesg), 0);
    printf("The server sent %s to the client.\n", server_mesg);
    printf("%d bytes in total\n", count);

    close(server_socket);
    close(client_socket);
    return 0;
}
