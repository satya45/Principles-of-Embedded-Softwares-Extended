

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
	if (argc != 3)
	{
		printf("ERROR: Wrong number of parameters.\n");
		printf("Input first parameter = name of log file; second parameter = log level: 'info' or 'warning' or 'error' or 'debug'.\n");
		exit(EXIT_FAILURE);
	}

	if ((strcmp(argv[1], "info") == 0) || (strcmp(argv[1], "warning") == 0) || (strcmp(argv[1], "error") == 0) || (strcmp(argv[1], "debug") == 0))
	{
		printf("ERROR: Filename not valid ; Choose another filename, cannot choose filename same as log levels.\n");
		exit(EXIT_FAILURE);
	}

	if ((strcmp(argv[2], "info") != 0) && (strcmp(argv[2], "warning") != 0) && (strcmp(argv[2], "error") != 0) && (strcmp(argv[2], "debug") != 0))
	{
		printf("ERROR: Invalid Log Level; Valid Log Levels: 'info' or 'warning' or 'error' or 'debug'.\n");
		exit(EXIT_FAILURE);
	}

	filename = argv[1];
	if (!(strcmp(argv[2], "info")))
	{
		g_ll = INFO;
	}
	else if (!(strcmp(argv[2], "debug")))
	{
		g_ll = DEBUG;
	}
	else if (!(strcmp(argv[2], "warning")))
	{
		g_ll = WARNING;
	}
	else if (!(strcmp(argv[2], "error")))
	{
		g_ll = ERROR;
	}

	temp_timerflag = 0;
	light_timerflag = 0;

	srand(time(NULL));
	sig_init();
	queue_init();
	i2c_init();

	if (pthread_mutex_init(&mutex_a, NULL))
	{
		error_log("ERROR: pthread_mutex_init(mutex_a); mutex_a not created");
	}

	if (pthread_mutex_init(&mutex_error, NULL))
	{
		error_log("ERROR: pthread_mutex_init(mutex_error); mutex_error not created");
	}

	if (remove(filename))
	{
		error_log("ERROR: remove(); cannot delete log file");
	}

	create_threads(filename);

	for (int i = 0; i < 4; i++)
	{
		if (pthread_join(my_thread[i], NULL))
		{
			error_log("ERROR: pthread_join(); cannot join thread");
			//Send termination signal.
		}
	}
}

void *temp_thread(void *filename)
{
	msg_log("In Temperature Thread.\n", DEBUG);

	timer_init(TIMER_TEMP);

	while (1)
	{
		if (temp_timerflag)
		{
			pthread_mutex_lock(&mutex_a);
			printf("In main loop: Temperature Timer event handled.\n");

			//Insert Mutex lock here
			temp_timerflag = 0;
			queue_send(log_mq, read_temp_data(TEMP_UNIT), INFO_DEBUG);

			//data_send.id = TEMP_RCV_ID;
			//data_send.sensor_data.temp_data.temp_c = rand();
			//queue_send(log_mq, data_send, INFO_DEBUG);

			//Insert mutex Unlock here
			pthread_mutex_unlock(&mutex_a);
		}
	}
}

void *light_thread(void *filename)
{
	msg_log("In light Thread.\n", DEBUG);

	timer_init(TIMER_LIGHT);

	while (1)
	{

		if (light_timerflag)
		{
			pthread_mutex_lock(&mutex_a);
			printf("In main loop: Light timer event handled.\n");
			//Insert Mutex lock here
			light_timerflag = 0;
			queue_send(log_mq, read_light_data(), INFO_DEBUG);

			//data_send.id = LIGHT_RCV_ID;
			//data_send.sensor_data.light_data.light = rand() % 10;
			//queue_send(log_mq, data_send, INFO_DEBUG);

			//Insert mutex Unlock here
			pthread_mutex_unlock(&mutex_a);
		}
	}
}

void *logger_thread(void *filename)
{
	msg_log("In logger Thread.\n", DEBUG);
	while (1)
	{
		log_data(queue_receive(log_mq));
	}
}

void *sock_thread(void *filename)
{
	msg_log("In socket Thread.\n", DEBUG);
}

err_t create_threads(char *filename)
{
	if (pthread_create(&my_thread[0],		   // pointer to thread descriptor
					   (void *)&my_attributes, // use default attributes
					   temp_thread,			   // thread function entry point
					   (void *)0))			   // parameters to pass in
	{

		error_log("ERROR: pthread_create(); in create_threads function, temp_thread not created");
		//Send Termination Signal
	}

	if (pthread_create(&my_thread[1],		   // pointer to thread descriptor
					   (void *)&my_attributes, // use default attributes
					   light_thread,		   // thread function entry point
					   (void *)0))			   // parameters to pass in

	{
		error_log("ERROR: pthread_create(); in create_threads function, light_thread not created");
	}

	if (pthread_create(&my_thread[2],		   // pointer to thread descriptor
					   (void *)&my_attributes, // use default attributes
					   logger_thread,		   // thread function entry point
					   (void *)filename))	  // parameters to pass in

	{
		error_log("ERROR: pthread_create(); in create_threads function, logger_thread not created");
	}
	if (pthread_create(&my_thread[3],		   // pointer to thread descriptor
					   (void *)&my_attributes, // use default attributes
					   sock_thread,			   // thread function entry point
					   (void *)filename))	  // parameters to pass in

	{
		error_log("ERROR: pthread_create(); in create_threads function, sock_thread not created");
	}

	return OK;
}

err_t i2c_init(void)
{
	if ((i2c_open = open(I2C_BUS, O_RDWR)) < 0)
	{
		error_log("ERROR: i2c_open(); in i2c_init() function");
	}
}

sensor_struct read_error(char *error_str)
{
	sensor_struct read_data;
	read_data.id = ERROR_RCV_ID;

	if (clock_gettime(CLOCK_REALTIME, &read_data.sensor_data.temp_data.data_time))
	{
		error_log("ERROR: clock_gettime(); in read_temp_data() function");
	}

	//Errno is thread safe , no mutex required.
	read_data.sensor_data.error_data.error_value = errno;

	//Cannot use a pointer, the below statement is wrong.
	//The below line will pass a pointer and no mutex is required as \
	everytime a new object will be created local to this function. \
	This will not change the value of the string at that particular pointer \
	as everytime this function is called a new objectwill be created giving \
	us a different pointer.
	strcpy(read_data.sensor_data.error_data.error_str, error_str);

	return read_data;
}

sensor_struct read_msg(char *msg_str)
{
	sensor_struct read_data;
	read_data.id = MSG_RCV_ID;

	//Cannot use a pointer , the below statement is wrong.
	//The below line will pass a pointer and no mutex is required as \
	everytime a new object will be created local to this function. \
	This will not change the value of the string at that particular pointer \
	as everytime this function is called a new objectwill be created giving \
	us a different pointer.
	strcpy(read_data.sensor_data.msg_data.msg_str, msg_str);

	//pthread_mutex_unlock(&mutex_error);
	return read_data;
}

void error_log(char *error_str)
{
	queue_send(log_mq, read_error(error_str), INFO_DEBUG);
}

void msg_log(char *str, uint8_t loglevel)
{
	queue_send(log_mq, read_msg(str), loglevel);
}