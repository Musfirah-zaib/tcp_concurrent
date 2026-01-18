#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

void reverse(char str[]) {
    int i, j;
    char temp;
    for (i = 0, j = strlen(str)-1; i < j; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

int main() {
    int sockfd, newsock;
    struct sockaddr_in server;
    char buffer[1024];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr*)&server, sizeof(server));
    listen(sockfd, 5);

    printf("TCP Concurrent Server waiting...\n");

    while (1) {
        newsock = accept(sockfd, NULL, NULL);

        if (fork() == 0) {
            close(sockfd);
          
            recv(newsock, buffer, sizeof(buffer), 0);
            reverse(buffer);
            send(newsock, buffer, strlen(buffer), 0);

            close(newsock);
            _exit(0);
        }
        close(newsock);
    }
}
