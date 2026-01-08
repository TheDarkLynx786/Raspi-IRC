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

	// Bind Port to Socket
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = INADDR_ANY;

	int bnd = bind(serv_fd, (struct sockaddr*) &addr, sizeof(addr));
	if (bind < 0) {
		perror("Error binding port");
		return 1;
	}
	
	// Close Socket
	close(serv_fd);
	return 0;
}
