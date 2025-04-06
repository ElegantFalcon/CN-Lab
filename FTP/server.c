#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <string.h>

int main()
{
    int sockfd, newsock;
    char buffer[1024];
    char filename[1024];
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    if (listen(sockfd, 5) < 0) {
        perror("listen failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Server is waiting for client connection \n");

    if ((newsock = accept(sockfd, (struct sockaddr *)&client, &len)) < 0) {
        perror("accept failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    int bytes_received = recv(newsock, filename, sizeof(filename) - 1, 0);
    if (bytes_received < 0) {
        perror("recv failed");
        close(newsock);
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    filename[bytes_received] = '\0'; // Null-terminate the filename

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File not found: %s\n", filename);
        send(newsock, "File not found", strlen("File not found"), 0);
        close(newsock);
        close(sockfd);
        return 0;
    }

    printf("Sending file: %s\n", filename);
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (send(newsock, buffer, strlen(buffer), 0) < 0) {
            perror("send failed");
            break;
        }
    }
    fclose(file);

    close(newsock);
    close(sockfd);
  
    return 0;
}