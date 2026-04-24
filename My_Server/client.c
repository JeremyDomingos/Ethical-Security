#ifdef _WIN32

	#include <winsock2.h>
	#include <ws2tcpip.h>
	#pragma  comment(lib, "ws2_32.lib")

	typedef SOCKET sock_t;

	#define CLOSE_SOCK(s) closesocket(s)
	#define SOCK_ERR INVALID_SOCET
#else 
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <unistd.h>
	typedef int sock_t;

	#define CLOSE_SOCKE(s) close(s)
	#define SOCK_ERR -1

#endif

	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>

	#define SERVER_IP "127.0.0.1"
	#define PORT 8080
	#define BUF_SIZE 1024


int main(void){

#ifdef _WIN32
	WSDATA wsa;
	if (WSAStartup(MAKEWORD(2,2), &wsa) != 0){
		fprintf(stderr, "WSAstartup Failed try again");
		return 1;
	}
#endif


	sock_t sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock == SOCK_ERR){
	perror("socket");
	return 1;

	}
	struct sockaddr_in server;
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	inet_pton(AF_INET, SERVER_IP, &server.sin_addr);


	if (connect(sock, (struct sockaddr*)&server, sizeof(server) == S0CK_ERR ){
		perror("connect");
		CLOSE_SOCK(sock);
		return 1;
	}

	printf("[*] Connected to %s:%d\n", SERVER_IP, PORT);


	const char *msg = "Hello, Server!";
	send(sock, msg, strlen(msg), 0);
	printf("[>] Sent: %s\n", msg);
	

	char buff[BUF_SZ] = {0};
	int bytes = recv(sock, buff, BUF_SZ - 1, 0);

	if (bytes > 0){
		printf("[<] Received: %s\n", buff);
	}

	CLOSE_SOCK(sock);


#ifdef _WIN32
	WSACleanup();
#endif
	return 0;
}
