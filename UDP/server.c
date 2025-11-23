#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 6000
#define BUF_SIZE 1024

int main() {
    int sock;
    char filename[BUF_SIZE], buffer[BUF_SIZE];
    FILE *fp;

    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    bind(sock,(struct sockaddr*)&server,sizeof(server));

    printf("📡 UDP Server running...\n");

    recvfrom(sock, filename, BUF_SIZE, 0, (struct sockaddr*)&client, &len);
    printf("Client requested: %s\n", filename);

    fp = fopen(filename, "r");
    if(!fp) {
        sendto(sock, "ERROR: File Not Found!", 23, 0, (struct sockaddr*)&client, len);
        return 0;
    }

    while(fgets(buffer, BUF_SIZE, fp)) {
        sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr*)&client, len);
        usleep(1000);
    }

    sendto(sock, "EOF", 3, 0, (struct sockaddr*)&client, len);
    printf("📤 File sent successfully.\n");

    fclose(fp);
    close(sock);
    return 0;
}
