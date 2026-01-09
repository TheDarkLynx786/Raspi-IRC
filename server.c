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
	int serv_fd;
	struct sockaddr_in addr;
	socklen_t addr_len = sizeof(addr);
	char buffer[1024] = { 0 };
	char* serv_msg = "Server Msg: Hello, you are connected!";
	ssize_t read_value;

	// Create server (and file descriptor)
	serv_fd = socket(AF_INET, SOCK_STREAM, 0);
	
	if (serv_fd < 0) {
		perror("Error creating server.");
		return 1;
	}
	
	// Set Socket Options
	int opt = 1;
	int sockopt = setsockopt(serv_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	if (sockopt < 0) {
		perror("Failed to set socket options");
		close(serv_fd);
		return 1;
	}

	
	// Zero address struct (good practice apparently)
	memset(&addr, 0, sizeof(addr));
	
	// Bind Port to Socket
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = INADDR_ANY;

	int bnd = bind(serv_fd, (struct sockaddr*) &addr, sizeof(addr));
	if (bnd < 0) {
		perror("Error binding port");
		return 1;
	}

	// Listen for Client
	int listen_check = listen(serv_fd, 5); // Backlog Queue set to 5
	if (listen_check < 0) {
		perror("Failed to listen for any clients");
		return 1;
	}

	// Accept client connection
	int client_socket = accept(serv_fd, (struct sockaddr*)&addr, &addr_len);
	if (client_socket < 0) {
		perror("Failed to accept client connection");
		return 1;
	}

	// Send client server message
	send(client_socket, serv_msg, strlen(serv_msg), 0);

	// Read Message sent from client and print
	read_value = read(client_socket, buffer, sizeof(buffer) - 1);
	printf("Client Msg:\n%s\n", buffer);

	
	// Close Socket and Client Conenction
	close(client_socket);
	close(serv_fd);
	return 0;
}
