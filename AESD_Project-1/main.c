
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include <sched.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "main.h"
#include "light.h"
#include "temp.h"
#include "logger.h"
#include "sockets.h"
#include "my_signal.h"
#include "queue.h"

#define BACKUP_FILENAME			("backup")

//Global Variables
pthread_t my_thread[4];
pthread_attr_t my_attributes;
char *filename;
char *backup = BACKUP_FILENAME;
char *a;



int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("ERROR: Input a filename to log data.\n");
		exit(EXIT_FAILURE);
	}
	
	
    filename = argv[1];
	
	
	sig_init();
	queue_init();
	
	
	
	if(remove(filename))
	{
		perror("ERROR: remove().\n");
	}
	
	queue_send();
    create_threads(filename);

    for(int i=0; i<4;i++)
	{
		if(pthread_join(my_thread[i], NULL))
		{	
			//Can use strerror(errno) to get the error message based on the error code
			perror("ERROR: Cannot Join Threads.\n");
			//Send termination signal.
		}
	}
}


void *temp_thread(void * filename)
{
	printf("In Temperature Thread.\n");
	int s = mq_send(log_mq, "Hello Siddhant", 100, 0);
	if (s == -1)
	{
		perror("ERROR : mq_send.\n");
	}
	while(1){}
}

void *light_thread(void *filename)
{
    printf("In light thread.\n");
}

void *logger_thread(void *filename)
{
	char buff[100];
	ssize_t x;
	x = mq_receive(log_mq,(char *)buff,100,NULL);
	if(x == -1)
	{
		perror("ERROR : mq_receive().\n");
	}
	FILE *logfile = fopen(filename, "a");
    fprintf(stdout,"In logger thread: %s.\n", buff);
    fprintf(logfile, "In logger Thread: %s.\n", buff);
    fclose(logfile);
}

void *sock_thread(void *filename)
{
    printf("In socket thread.\n");
}


int create_threads(char *filename)
{
    if(pthread_create(&my_thread[0],   				// pointer to thread descriptor
						(void *)&my_attributes,     // use default attributes
						temp_thread,				// thread function entry point
						(void *)0)) 				// parameters to pass in
	{
		
		perror("Temperature thread create failed\n");
		//Send Termination Signal
	}
    
	if(pthread_create(&my_thread[1],   				// pointer to thread descriptor
                  (void *)&my_attributes,     		// use default attributes
                  light_thread, 					// thread function entry point
                  (void *)0))	 					// parameters to pass in
				  
	{
		perror("Light thread create failed\n");
		exit(1);
	}
 
    if(pthread_create(&my_thread[2],   				// pointer to thread descriptor
                  (void *)&my_attributes,     		// use default attributes
                  logger_thread, 					// thread function entry point
                  (void *)filename))		 		// parameters to pass in
				  
	{
		perror("Logger thread create failed\n");
		exit(1);
	}
    if(pthread_create(&my_thread[3],   				// pointer to thread descriptor
                  (void *)&my_attributes,     		// use default attributes
                  sock_thread, 						// thread function entry point
                  (void *)filename))				// parameters to pass in
				  
	{
		perror("Logger thread create failed\n");
		exit(1);
	}
    return 0;
}




