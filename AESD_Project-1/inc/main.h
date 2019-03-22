#ifndef _MAIN_H
#define _MAIN_H

#include <stdint.h>
#include <stdio.h>
#include <time.h>

typedef uint32_t err_t;

typedef enum
{
	temp_rcv;
	light_rcv;
	errror_rcv
}event;

typedef struct  
{
	event id;
    float temp_c;
    struct timespec data_time;
    uint8_t logger_level;
    
}temp_struct;

typedef struct
{
	event id;
	float light;
	struct timespec data_time;
	uint8_t logger_level;
}light_struct;



//Function Declarations
int create_threads(char *filename);
void *temp_thread(void *);
void *light_thread(void *);
void *logger_thread(void * filename);
void *sock_thread(void *filename);

#endif
