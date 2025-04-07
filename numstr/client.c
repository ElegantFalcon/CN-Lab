#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server;
    char buffer[BUFFER_SIZE];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&server, 0, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Enter a number: ");
    fgets(buffer, BUFFER_SIZE, stdin);

    // Remove newline if any
    buffer[strcspn(buffer, "\n")] = '\0';

    sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&server, sizeof(server));

    printf("Number sent to server.\n");

    close(sockfd);
    return 0;
}
