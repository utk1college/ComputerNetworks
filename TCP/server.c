#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUF_SIZE 1024

int main() {
    int server_fd, client_fd;
    char filename[BUF_SIZE], buffer[BUF_SIZE];
    FILE *fp;

    struct sockaddr_in server, client;
    socklen_t client_len = sizeof(client);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&server, sizeof(server));
    listen(server_fd, 5);

    printf("📡 TCP Server running... Waiting for connection...\n");

    client_fd = accept(server_fd, (struct sockaddr*)&client, &client_len);

    read(client_fd, filename, BUF_SIZE);
    printf("📨 Client requested: %s\n", filename);

    fp = fopen(filename, "r");
    if(fp == NULL) {
        write(client_fd, "ERROR: File Not Found!", 23);
        close(client_fd);
        close(server_fd);
        return 0;
    }

    while(fgets(buffer, BUF_SIZE, fp)) {
        write(client_fd, buffer, strlen(buffer));
    }

    printf("📤 File sent successfully.\n");

    fclose(fp);
    close(client_fd);
    close(server_fd);
    return 0;
}
