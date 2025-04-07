#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

int main() {
    int sockfd, newsock;
    char buffer[1024];
    char filename[1024];
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&server, sizeof(server));
    listen(sockfd, 5);
    printf("Server is waiting for client connection\n");

    newsock = accept(sockfd, (struct sockaddr *)&client, &len);
    recv(newsock, filename, sizeof(filename), 0);
    
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        send(newsock, "File not found", strlen("File not found"), 0);
    } else {
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            send(newsock, buffer, strlen(buffer), 0);
        }
        fclose(file);
    }

    close(newsock);
    close(sockfd);
    return 0;
}