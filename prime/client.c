#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main()
{
    int sockfd;
    struct sockaddr_in server;
    char buffer[1024];
    char input[100];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");


    connect(sockfd, (struct sockaddr *)&server, sizeof(server));

    printf("Enter a number: ");
    scanf("%s", input);

    send(sockfd, input, strlen(input), 0);
    read(sockfd, buffer, 1024);

    printf("Server: %s\n", buffer);
    close(sockfd);

    return 0;
}