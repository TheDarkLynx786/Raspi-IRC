#define PORT 6667

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/socket.h>


int main() {


        // Variables
        ssize_t valread;
        int client_fd;
        struct sockaddr_in serv_addr;
        char buffer[1024] = { 0 };

        // Create socket file descriptor for client
        client_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (client_fd < 0) {
                perror("Failed to create client socket FD");
                return 1;
        }

        // Zero struct and assign values (no binding in client)
        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);

        // Convert IPv4/IPv6 addresses from text to binary
        int addr_chk = inet_pton(AF_INET, "0.0.0.0", &serv_addr.sin_addr);
        if (addr_chk < 0) {
                perror("Invalid or unsupported address");
                return 1;
        }

        // Connect to server
        int status = connect(client_fd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
        if (status < 0) {
                perror("Failed to connect to server");
                return 1;
        }

        // Recieve server hello message
        valread = read(client_fd, buffer, sizeof(buffer) - 1);
        printf("%s\n", buffer);

        // Send User Message to Server
        memset(buffer, 0, sizeof(buffer));

        printf("\nEnter in a message:\n");
        scanf("%s", buffer);

        send(client_fd, buffer, sizeof(buffer), 0);

        // Close client connection
        close(client_fd);
        return 0;







        return 0;
}
