
#include "queue.h"

int queue_init(void)
{
	struct mq_attr attr;

	attr.mq_flags = 0;
	attr.mq_maxmsg = 10;
	attr.mq_msgsize = sizeof(sensor_struct); //Change afterwards
	attr.mq_curmsgs = 0;

	heartbeat_mq = mq_open(HEARTBEAT_QUEUE, O_RDWR | O_CREAT, 0644, &attr);
	if (heartbeat_mq == -1)
	{
		error_log("ERROR: mq_open() for heartbeat queue; in queue_init() function");
	}

	log_mq = mq_open(LOG_QUEUE, O_RDWR | O_CREAT, 0644, &attr);
	if (log_mq == -1)
	{
		error_log("ERROR: mq_open() for logger queue; in queue_init() function");
	}

	sock_mq = mq_open(SOCK_QUEUE, O_RDWR | O_CREAT, 0644, &attr);
	if (sock_mq == -1)
	{
		error_log("ERROR: mq_open() for socket queue; in queue_init() function");
	}

	log_sock_mq = mq_open(LOG_SOCK_QUEUE, O_RDWR | O_CREAT, 0644, &attr);
	if (log_sock_mq == -1)
	{
		error_log("ERROR: mq_open() for log_sock queue; in queue_init() function");
	}
}

void queue_send(mqd_t mq, sensor_struct data_send, uint8_t loglevel)
{
	if (loglevel & g_ll)
	{
		ssize_t res;
		res = mq_send(mq, (char *)&data_send, sizeof(sensor_struct), 0);
		if (res == -1)
		{
			//How to identify error due to which queue???? think!!!!!
			error_log("ERROR: mq_send(); in queue_send() function");
		}
	}
}

sensor_struct queue_receive(mqd_t mq)
{
	sensor_struct data_rcv;
	ssize_t res;
	res = mq_receive(mq, (char *)&data_rcv, sizeof(sensor_struct), NULL);
	if (res == -1)
	{
		error_log("ERROR: mq_receive(); in queue_receive() function");
	}
	return data_rcv;
}

err_t queues_close(void)
{
	if (mq_close(heartbeat_mq))
	{
		error_log("ERROR: mq_close(heartbeat); in queues_close() function");
	}
	if (mq_close(log_mq))
	{
		error_log("ERROR: mq_close(logger); in queues_close() function");
	}
	if (mq_close(sock_mq))
	{
		error_log("ERROR: mq_close(socket); in queues_close() function");
	}
	if (mq_close(log_sock_mq))
	{
		error_log("ERROR: mq_close(logger_socket); in queues_close() function");
	}
	return OK;
}

err_t queues_unlink(void)
{
	if (mq_unlink(HEARTBEAT_QUEUE))
	{
		error_log("ERROR: mq_unlink(heartbeat); in queues_unlink() function");
	}

	if (mq_unlink(LOG_QUEUE))
	{
		error_log("ERROR: mq_unlink(logger); in queues_unlink() function");
	}

	if (mq_unlink(SOCK_QUEUE))
	{
		error_log("ERROR: mq_unlink(socket); in queues_unlink() function");
	}

	if (mq_unlink(LOG_SOCK_QUEUE))
	{
		error_log("ERROR: mq_unlink(logger_socket); in queues_unlink() function");
	}
}
