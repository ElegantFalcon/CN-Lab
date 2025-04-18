#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server, client;
    char buffer[BUFFER_SIZE];
    socklen_t len = sizeof(client);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&server, 0, sizeof(server));
    memset(&client, 0, sizeof(client));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    bind(sockfd, (const struct sockaddr *)&server, sizeof(server));
  
    printf("Server is running and waiting for time requests on port %d...\n", PORT);

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);

        int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client, &len);

        printf("Received request from client: %s\n", inet_ntoa(client.sin_addr));

        time_t current_time = time(NULL);
        char *time_str = ctime(&current_time);

        sendto(sockfd, time_str, strlen(time_str), 0, (struct sockaddr *)&client, len);
        printf("Sent time to client: %s", time_str);
    }

    close(sockfd);
    return 0;
}

