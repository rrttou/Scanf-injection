// Client side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define BUF_SIZE 60
#define PORT	 8080
#define MAXLINE 1024

// Driver code
int main() {
	int sockfd;
	char buffer[MAXLINE];
    char buf[BUF_SIZE+1];
	struct sockaddr_in	 servaddr;
    int retVal=0;
   

	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	
	int n, len;
	
    printf("Enter your message now :\n");
    retVal=scanf("%s",buf);			// Get input from user
    if(retVal<0) {perror("Input error"); exit(1);}	// Make sure input OK

    while(strcmp(buf,"Bye")!=0){
        sendto(sockfd, buf, BUF_SIZE,
            MSG_CONFIRM, (const struct sockaddr *) &servaddr,
                sizeof(servaddr));
        printf("Message sent.\n");
            
        n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                    MSG_WAITALL, (struct sockaddr *) &servaddr,
                    &len);
        buffer[n] = '\0';
	    printf("Server : %s\n", buffer);

        printf("\nEnter your message now :\n");
        retVal=scanf("%s",buf);			// Get input from user
        if(retVal<0) {perror("Input error"); exit(1);}	// Make sure input OK
    }
    sendto(sockfd, buf, BUF_SIZE,
    MSG_CONFIRM, (const struct sockaddr *) &servaddr,
         sizeof(servaddr));
    printf("Closing the communication\n");

	close(sockfd);
	return 0;
}
