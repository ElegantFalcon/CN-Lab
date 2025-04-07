// Client Code
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUFFER_SIZE 1024

int main()
{
    int sockfd;
    struct sockaddr_in server;
    char buffer[BUFFER_SIZE];
    char *request_message = "TIME_REQUEST";

    sockfd = socket(AF_INET, SOCK_DGRAM, 0) ;

    memset(&server, 0, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    sendto(sockfd, request_message, strlen(request_message), 0, (struct sockaddr *)&server, sizeof(server));

    printf("Time request sent to server.\n");

    int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, NULL, NULL);


    buffer[n] = '\0'; // Null-terminate the received string
    printf("Current time from server: %s\n", buffer);

    close(sockfd);
    return 0;
}