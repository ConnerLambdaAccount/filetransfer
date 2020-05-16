#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<netinet/in.h>
#include<arpa/inet.h>

const char* server = "10.0.1.5";
const int port = 9001;

int main() {
	int dest = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(dest == -1) {
		fprintf(stderr, "failed to create socket\n");
		return -1;
	}

	struct sockaddr_in serverinfo;
	serverinfo.sin_family = AF_INET;
	serverinfo.sin_addr.s_addr = inet_addr(server);
	serverinfo.sin_port = htons(port);

	if(connect(dest, (struct sockaddr*)&serverinfo, sizeof(serverinfo)) != 0) {
		fprintf(stderr, "Failed to connect to server\n");
		return -1;
	}

	send(dest, "Hello World!", strlen("Hello World!"), 0);	
}
