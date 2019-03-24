
#include "queue.h"


int queue_init(void)
{
	struct mq_attr attr;
	
	attr.mq_flags=0;
	attr.mq_maxmsg=10;
	attr.mq_msgsize=sizeof(sensor_struct);			//Change afterwards
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

void queue_send(sensor_struct data_send)
{
	ssize_t res;
	res = mq_send(log_mq,(char *)&data_send,sizeof(sensor_struct),0);
	if(res == -1)
	{
		perror("ERROR : mq_send() temperature data.\n");
	}
	//return data_rcv;
	
}


sensor_struct queue_receive(mqd_t mq)
{
	sensor_struct data_rcv;
	ssize_t res;
	res = mq_receive(mq,(char *)&data_rcv,sizeof(sensor_struct),NULL);
	if(res == -1)
	{
		perror("ERROR : mq_receive().\n");
	}
	return data_rcv;
}

err_t queues_close(void)
{
	if(mq_close(heartbeat_mq))
	{
		perror("ERROR: mq_close(heartbeat_mq).\n");
		return errno;
	}
	if(mq_close(log_mq))
	{
		perror("ERROR: mq_close(log_mq).\n");
		return errno;
	}
	if(mq_close(sock_mq))
	{
		perror("ERROR: mq_close(sock_mq).\n");
		return errno;
	}
	if(mq_close(log_sock_mq))
	{
		perror("ERROR: mq_close(log_sock_mq).\n");
		return errno;
	}
	return OK;
}

err_t queues_unlink(void)
{
	if(mq_unlink(HEARTBEAT_QUEUE))
	{
		perror("ERROR: mq_unlink(HEARTBEAT_QUEUE).\n");
		return errno;
	}
	
	if(mq_unlink(LOG_QUEUE))
	{
		perror("ERROR: mq_unlink(LOG_QUEUE).\n");
		return errno;
	}
	
	if(mq_unlink(SOCK_QUEUE))
	{
		perror("ERROR: mq_unlink(SOCK_QUEUE).\n");
		return errno;
	}
	
	if(mq_unlink(LOG_SOCK_QUEUE))
	{
		perror("ERROR: mq_unlink(LOG_SOCK_QUEUE).\n");
		return errno;
	}
}
