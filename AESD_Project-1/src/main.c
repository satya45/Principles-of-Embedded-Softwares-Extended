#include "main.h"
pthread_t my_thread[4];
pthread_attr_t my_attributes;

int create_threads(char *f)
{
    if(pthread_create(&my_thread[0],   // pointer to thread descriptor
                  (void *)&my_attributes,     // use default attributes
                  temp_thread,// thread function entry point
                  (void *)0 // parameters to pass in
				  ))
	{
		perror("Temperature thread create failed\n");
		exit(1);
		
	}
    
	if(pthread_create(&my_thread[1],   // pointer to thread descriptor
                  (void *)&my_attributes,     // use default attributes
                  light_thread, // thread function entry point
                  (void *)0 // parameters to pass in
				  ))
	{
		perror("Light thread create failed\n");
		exit(1);
	}
    if(pthread_create(&my_thread[2],   // pointer to thread descriptor
                  (void *)&my_attributes,     // use default attributes
                  logger_thread, // thread function entry point
                  (void *)&f // parameters to pass in
				  ))
	{
		perror("Logger thread create failed\n");
		exit(1);
	}
    if(pthread_create(&my_thread[3],   // pointer to thread descriptor
                  (void *)&my_attributes,     // use default attributes
                  sock_thread, // thread function entry point
                  (void *)&f // parameters to pass in
				  ))
	{
		perror("Logger thread create failed\n");
		exit(1);
	}
    return 0;
}

int main(int argc, char *argv[])
{
    char *f = argv[1];
    create_threads(f);
    for(int i=0; i<4;i++)
	{
		pthread_join(my_thread[i], NULL);
	}
}