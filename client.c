#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<netinet/in.h>
#include<arpa/inet.h>

const char* server = "127.0.0.1";
const int port = 9001;
const int blockSize = 24;

int fullSend(int socket, unsigned char* buffer, unsigned int buflen) {
    unsigned int bytes_total = 0;
    int bytes_sent = send(socket, buffer, buflen, 0);
    while(bytes_sent > 0) {
        bytes_total += bytes_sent;
        if(bytes_total >= buflen) {
            return 0;
        }
        bytes_sent = send(socket, buffer+bytes_total, buflen-bytes_total, 0);
    }
    return -1;
}

int main() {
    /*
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
    */
    // Connected successfully fgets() for filepath to what we send
    char filepath[512];
    strcpy(filepath, "/Users/conner/Desktop/BubbleSort.playground/Contents.swift");
    /*
    fgets(filepath, 512, stdin);
    // Trim newline
    filepath[strlen(filepath)-1] = '\0';
    */
    
    // Now that we have the path to our file, open it
    FILE* file = fopen(filepath, "rb");
    if(!file) {
        fprintf(stderr, "Failed to open file: %s\n", filepath);
        return -1;
    }
    
    // Read the file contents 2kb at a time, send them to server
    unsigned char buf[blockSize];
    
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    rewind(file);
    
    for(int i=0;i<fsize;i+=blockSize) {
        fread(buf, blockSize, 1, file);
        printf("%s", buf);
        //fullSend(dest, buf, blockSize);
        fseek(file, i, SEEK_SET);
    }
    printf("LOOP EXIT\n");
    fclose(file);
}
