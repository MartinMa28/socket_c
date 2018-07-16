#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>

int main()
{
    // create a socket, 0 means using TCP by default
    int net_socket;
    net_socket = socket(AF_INET, SOCK_STREAM, 0);

    // specify an address for the socket
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9002);
    server_addr.sin_addr.s_addr = htonl(0xC0A80009);   
    //server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int connection_status = connect(net_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    // check for error with the connection
    if(connection_status == -1)
        printf("There was an error making a connection to the remote socket.\n");
    
    char connect_info[256] = "connect to server\n";
    send(net_socket, connect_info, sizeof(connect_info), 0);
    printf("client reached the server\n");
    int rand_buf[10];
    int count = recv(net_socket, rand_buf, sizeof(rand_buf), 0);
    int i;
    for(i=0;i<10;i++)
    {
        printf("%d\n", rand_buf[i]);
    }
    printf("%d bytes in total\n", count);

    // close the socket
    close(net_socket);

    return 0;
}


