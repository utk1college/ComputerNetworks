#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 6000
#define BUF_SIZE 1024

int main() {
    int sock;
    char filename[BUF_SIZE], buffer[BUF_SIZE];

    struct sockaddr_in server;
    socklen_t len = sizeof(server);

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Enter filename: ");
    scanf("%s", filename);

    sendto(sock, filename, strlen(filename), 0, (struct sockaddr*)&server, len);

    printf("\n📥 Receiving file:\n\n");

    while(1) {
        recvfrom(sock, buffer, BUF_SIZE, 0, (struct sockaddr*)&server, &len);
        if(strcmp(buffer,"EOF")==0) break;
        printf("%s", buffer);
        memset(buffer,0,BUF_SIZE);
    }

    printf("\n✔ Transfer complete.\n");

    close(sock);
    return 0;
}
