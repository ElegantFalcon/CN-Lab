// Server Code: Convert number digits to words
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUFFER_SIZE 1024

const char *digit_words[] = {
    "zero", "one", "two", "three", "four",
    "five", "six", "seven", "eight", "nine"
};

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

    printf("Server is running on port %d...\n", PORT);

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);

        int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client, &len);
        buffer[n] = '\0'; // Null-terminate

        printf("Received number from client: %s\n", buffer);

        // Convert digits to words
        printf("Converted to words: ");
        for (int i = 0; i < strlen(buffer); i++) {
            if (buffer[i] >= '0' && buffer[i] <= '9') {
                printf("%s ", digit_words[buffer[i] - '0']);
            }
        }
        printf("\n");
    }

    close(sockfd);
    return 0;
}
