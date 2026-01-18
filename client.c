#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    struct sockaddr_in server;
    char buffer[1024];

    // 1. Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // 2. Server address
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    // 3. Connect to server
    connect(sockfd, (struct sockaddr*)&server, sizeof(server));

    // 4. Input
    printf("Enter string: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';

    // 5. Send data
    send(sockfd, buffer, strlen(buffer), 0);

    // 6. Receive response
    recv(sockfd, buffer, sizeof(buffer), 0);

    // 7. Output
    printf("Result from server: %s\n", buffer);

    // 8. Close socket
    close(sockfd);
    return 0;
}
