#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {
    int network_socket;
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int connection = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    if(connection == -1){
        printf("Connection Failed!!\n");
    }
    char response[256];
    recv(network_socket, &response, sizeof(response), 0);

    printf("%s\n", response);

    close(network_socket);
    return 0;
}
