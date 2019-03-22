
#include "queue.h"


int queue_init(void)
{
	struct mq_attr attr;
	
	attr.mq_flags=0;
	attr.mq_maxmsg=10;
	attr.mq_msgsize=100;			//Change afterwards
	attr.mq_curmsgs=0;
	
	heartbeat_mq = mq_open(HEARTBEAT_QUEUE, O_RDWR | O_CREAT, 0644, &attr);
	if(heartbeat_mq == -1)
	{
		perror("ERROR : mq_open()");
		return (errno);
	}
	
	log_mq = mq_open(LOG_QUEUE, O_RDWR | O_CREAT, 0644, &attr);
	if(log_mq == -1)
	{
		perror("ERROR : mq_open()");
		return (errno);
	}
	
	sock_mq = mq_open(SOCK_QUEUE, O_RDWR | O_CREAT, 0644, &attr);
	if(sock_mq == -1)
	{
		perror("ERROR : mq_open()");
		return (errno);
	}
	
	log_sock_mq = mq_open(LOG_SOCK_QUEUE, O_RDWR | O_CREAT, 0644, &attr);
	if(log_sock_mq == -1)
	{
		perror("ERROR : mq_open()");
		return (errno);
	}
}

void queue_send(void)
{
	mq_send(log_mq, x, 100, 0);
	
}
