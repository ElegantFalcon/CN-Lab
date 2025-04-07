#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>

#define PORT 8080

bool is_prime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

int main() {
    int sockfd, newsock;
    struct sockaddr_in server,client;
    socklen_t len = sizeof(client);
    char buffer[1024];
    char response[1024];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    bind(sockfd, (struct sockaddr *)&server, sizeof(server));
    listen(sockfd, 3);
    
    printf("Server is listening on port %d...\n", PORT);

    newsock = accept(sockfd, (struct sockaddr *)&client, &len);
    read(newsock, buffer, 1024);
    
    int number = atoi(buffer);
    
    if (is_prime(number)) {
        snprintf(response, sizeof(response), "%d is a prime number.", number);
    } else {
        snprintf(response, sizeof(response), "%d is not a prime number.", number);
    }

    send(newsock, response, strlen(response), 0);
    printf("Processed request for number: %d\n", number);

    close(newsock);
    close(sockfd);
    return 0;
}