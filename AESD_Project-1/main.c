

//#include <string.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "main.h"
#include "light.h"
#include "temp.h"
#include "logger.h"
#include "sockets.h"
#include "my_signal.h"
#include "queue.h"
#include "timer.h"

//Global Variables
pthread_t my_thread[4];
//pthread_mutex_t mutex_a;
pthread_attr_t my_attributes;
char *a;

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("ERROR: Input a filename to log data.\n");
		exit(EXIT_FAILURE);
	}

	filename = argv[1];
	temp_timerflag = 0;
	light_timerflag = 0;

	srand(time(NULL));
	sig_init();
	queue_init();
	i2c_init();

	if (pthread_mutex_init(&mutex_a, NULL))
	{
		perror("ERROR: pthread_mutex_init(mutex_a); mutex_a not created.\n ");
	}

	if (pthread_mutex_init(&mutex_error, NULL))
	{
		perror("ERROR: pthread_mutex_init(mutex_error); mutex_error not created.\n ");
	}

	if (remove(filename))
	{
		error_log("ERROR: remove(); cannot delete log file");
	}

	//queue_send();
	create_threads(filename);

	for (int i = 0; i < 4; i++)
	{
		if (pthread_join(my_thread[i], NULL))
		{
			//Can use strerror(errno) to get the error message based on the error code
			perror("ERROR: Cannot Join Threads.\n");
			//Send termination signal.
		}
	}
}

void *temp_thread(void *filename)
{
	printf("In Temperature Thread.\n");

	timer_init(TIMER_TEMP);
	sensor_struct data_send;

	while (1)
	{
		//if (timer_event == TEMP_EVENT)
		if (temp_timerflag)
		{
			pthread_mutex_lock(&mutex_a);
			printf("In main loop: Temperature Timer event handled.\n");
			//Insert Mutex lock here
			temp_timerflag = 0;
			//timer_event &= (~TEMP_EVENT);
			//queue_send(read_temp_data(TEMP_UNIT));

			 
			//data_send.id = TEMP_RCV_ID;
			//data_send.sensor_data.temp_data.temp_c = rand();
			//queue_send(data_send);
			

			//Insert mutex Unlock here
			pthread_mutex_unlock(&mutex_a);
		}
	}
}

void *light_thread(void *filename)
{
	printf("In light thread.\n");
	sensor_struct data_send;
	timer_init(TIMER_LIGHT);

	while (1)
	{

		//if (timer_event == LIGHT_EVENT)
		if (light_timerflag)
		{

			pthread_mutex_lock(&mutex_a);
			printf("In main loop: Light timer event handled.\n");
			//Insert Mutex lock here
			light_timerflag = 0;
			//timer_event &= (~LIGHT_EVENT);
			queue_send(read_light_data());

			//data_send.id = LIGHT_RCV_ID;
			//data_send.sensor_data.light_data.light = rand() % 10;
			//queue_send(data_send);

			//Insert mutex Unlock here
			pthread_mutex_unlock(&mutex_a);
		}
	}

	/*
	while (1)
	{
		sleep(3);
		data_send.id = LIGHT_RCV_ID;
		data_send.sensor_data.light_data.light = rand() % 10;
		queue_send(data_send);
	}
	*/
}

void *logger_thread(void *filename)
{
	printf("In logger Thread.\n");
	while (1)
	{
		log_data(queue_receive(log_mq));
	}
}

void *sock_thread(void *filename)
{
	printf("In socket thread.\n");
}

err_t create_threads(char *filename)
{
	if (pthread_create(&my_thread[0],		   // pointer to thread descriptor
					   (void *)&my_attributes, // use default attributes
					   temp_thread,			   // thread function entry point
					   (void *)0))			   // parameters to pass in
	{

		perror("Temperature thread create failed\n");
		return errno;
		//Send Termination Signal
	}

	if (pthread_create(&my_thread[1],		   // pointer to thread descriptor
					   (void *)&my_attributes, // use default attributes
					   light_thread,		   // thread function entry point
					   (void *)0))			   // parameters to pass in

	{
		perror("Light thread create failed\n");
		return errno;
	}

	if (pthread_create(&my_thread[2],		   // pointer to thread descriptor
					   (void *)&my_attributes, // use default attributes
					   logger_thread,		   // thread function entry point
					   (void *)filename))	  // parameters to pass in

	{
		perror("Logger thread create failed\n");
		return errno;
	}
	if (pthread_create(&my_thread[3],		   // pointer to thread descriptor
					   (void *)&my_attributes, // use default attributes
					   sock_thread,			   // thread function entry point
					   (void *)filename))	  // parameters to pass in

	{
		perror("Logger thread create failed\n");
		return errno;
	}

	return OK;
}

err_t i2c_init(void)
{
	if ((i2c_open = open(I2C_BUS, O_RDWR)) < 0)
	{
		perror("Error opening I2C bus\n");
		return errno;
	}
}

sensor_struct read_error(char *error_str)
{
	//pthread_mutex_lock(&mutex_error);
	//perror(error_str);
	sensor_struct data_send;
	data_send.id = ERROR_RCV_ID;

	//Errno is thread safe , no mutex required.
	data_send.sensor_data.error_data.error_value = errno;
	
	//The below line will pass a pointer and no mutex is required as \
	everytime a new object will be created local to this function. \
	This will not change the value of the string at that particular pointer \
	as everytime this function is called a new objectwill be created giving \
	us a different pointer. 
	data_send.sensor_data.error_data.error_str = error_str; 

	//pthread_mutex_unlock(&mutex_error);
	return data_send;
}

void error_log(char *error_str)
{
	queue_send(read_error(error_str));
}