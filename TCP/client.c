#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUF_SIZE 1024

int main() {
    int sock;
    char filename[BUF_SIZE], buffer[BUF_SIZE];
    struct sockaddr_in server;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr*)&server, sizeof(server));

    printf("Enter filename: ");
    scanf("%s", filename);

    write(sock, filename, strlen(filename));

    printf("\n📥 Receiving file:\n\n");

    while(read(sock, buffer, BUF_SIZE) > 0) {
        printf("%s", buffer);
        memset(buffer, 0, BUF_SIZE);
    }

    printf("\n\n✔ Transfer complete.\n");

    close(sock);
    return 0;
}
