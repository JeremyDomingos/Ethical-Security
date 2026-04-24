#ifdef _WIN32
	#include <winsock2.h>
	#include <ws2tcpip.h>
	#pragma comment(lib, "win2_32.lib");
	
	typedef SOCKET sock_t;

	#define CLOSE_SOCK(s) close_socket(s)
	#define SOCK_ERR INVALID_SOCKET

#else
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>

	typedef int sock_t;

	#define CLOSE_SOCK(s) close(s)
	#define SOCK_ERR -1
#endif

	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>


	#define PORT 8080
	#define BACKLOG 5
	#define BUF_SZ 1024


int main(void) {

#ifdef _WIN32
	WSDATA wsa;

	if (WSAStartup(MAKEWORD(2,2), &wsa) != 0){
		fprintf(stderr, "WSAStartup() Failed")
		return 1;
	}
#endif


	sock_t server_fd = socket(AF_INET, SOCK_STREAM, 0);
	
	if (server_fd == SOCK_ERR){
		perror("socket");
		return 2;
	}

	int opt = 1; 
	setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));


	struct sockaddr_in addr;
	memeset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(PORT);


	if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) == SOCK_ERR){
		perror("bind");
		CLOSE_SOCK(server_fd);
		return 3;
	}


	listen(server_fd, BACKLOG);
	printf("[*] Server is listening on Port %d...\n", PORT);


	while(1){
		struct sockaddr_in client_addr;
		socklen_t client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
		
		if (client_fd == SOCK_ERR){
			perror("accept");
			continue;
		}

		char client_ip[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip));
		printf("[+] Connection from %s:%d\n", client_ip, ntohs(client_addr.sin_port));

		char buff[BUF_SZ] = {0};
		int bytes = recv(client_fd, buff, BUF_SZ - 1, 0);
		
		if (bytes > 0 ) {
			buff[]
		}	
	}
}
