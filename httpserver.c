#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char ** argv){
    FILE *html_data;
    html_data = fopen("index.html", "r");
    char response_data[1024];
    fgets(response_data, 1024, html_data);

    char http_header[2048] = "HTTP/1.1 200 OK\r\n\n";
    strcat(http_header, response_data);
    printf("%s", http_header);

    int http_server;
    http_server = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8001);
    server_address.sin_addr.s_addr = INADDR_ANY;

    bind(http_server, (struct sockaddr *)&server_address, sizeof (server_address));

    listen(http_server, 5);

    int client_socket;
    while (1){
        client_socket = accept(http_server, NULL, NULL);
        send(client_socket, http_header, sizeof (http_header), 0);
        close(client_socket);
    }

    return 0;
}
