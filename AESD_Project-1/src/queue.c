
/**
 * @file queue.c
 * @author Siddhant Jajoo and Satya Mehta
 * @brief This file consists of all the functions related to queue initialization, sending,
 * receiving, closing and unlinking.
 * @version 0.1
 * @date 2019-03-28
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "queue.h"

/**
 * @brief - This function initializes and creates all the message queues required in the application.
 * 
 * @return int 
 */
int queue_init(void)
{
	struct mq_attr attr;

	//Assigning the appropriate values to the message queues
	attr.mq_flags = 0;
	attr.mq_maxmsg = 10;
	attr.mq_msgsize = sizeof(sensor_struct); //Change afterwards
	attr.mq_curmsgs = 0;

	heartbeat_mq = mq_open(HEARTBEAT_QUEUE, O_RDWR | O_CREAT, 0644, &attr);
	if (heartbeat_mq == -1)
	{
		error_log("ERROR: mq_open() for heartbeat queue; in queue_init() function", ERROR_DEBUG, P2);
	}

	log_mq = mq_open(LOG_QUEUE, O_RDWR | O_CREAT, 0644, &attr);
	if (log_mq == -1)
	{
		error_log("ERROR: mq_open() for logger queue; in queue_init() function", ERROR_DEBUG, P2);
	}

	sock_mq = mq_open(SOCK_QUEUE, O_RDWR | O_CREAT, 0644, &attr);
	if (sock_mq == -1)
	{
		error_log("ERROR: mq_open() for socket queue; in queue_init() function", ERROR_DEBUG, P2);
	}

	log_sock_mq = mq_open(LOG_SOCK_QUEUE, O_RDWR | O_CREAT, 0644, &attr);
	if (log_sock_mq == -1)
	{
		error_log("ERROR: mq_open() for log_sock queue; in queue_init() function", ERROR_DEBUG, P2);
	}
	return OK;
}

/**
 * @brief - This function is used to enqueue the specified structure in the specified message queue
 * as the parameter
 * 
 * @param mq - The message queue descriptor in which the data needs to be enqueued.
 * @param data_send - The structure object consisting data. This can be obtained from functions such as:
 * read_temp_data(), read_light_data(), read_error(), read_msg().
 *	
 * @param loglevel - This specifies the log level.
 */
void queue_send(mqd_t mq, sensor_struct data_send, uint8_t loglevel, uint8_t prio)
{
	if (loglevel & g_ll)
	{
		ssize_t res;
		res = mq_send(mq, (char *)&data_send, sizeof(sensor_struct), prio);
		if (res == -1)
		{
			//How to identify error due to which queue???? think!!!!!
			error_log("ERROR: mq_send(); in queue_send() function", ERROR_DEBUG, P2);
		}
	}
}
/**
 * @brief - This function dequeues the data from the specified message queue descriptor parameter.
 * 
 * @param mq - Message queue descriptor
 * @return sensor_struct - The structure local onject in which the data received is stored.
 */
sensor_struct queue_receive(mqd_t mq)
{
	sensor_struct data_rcv;
	ssize_t res;
	res = mq_receive(mq, (char *)&data_rcv, sizeof(sensor_struct), NULL);
	if (res == -1)
	{
		error_log("ERROR: mq_receive(); in queue_receive() function", ERROR_DEBUG, P2);
	}
	return data_rcv;
}

/**
 * @brief - This function closes all the message queues.
 * 
 * @return err_t 
 */
err_t queues_close(void)
{
	if (mq_close(heartbeat_mq))
	{
		error_log("ERROR: mq_close(heartbeat); in queues_close() function", ERROR_DEBUG, P2);
	}
	if (mq_close(log_mq))
	{
		error_log("ERROR: mq_close(logger); in queues_close() function", ERROR_DEBUG, P2);
	}
	if (mq_close(sock_mq))
	{
		error_log("ERROR: mq_close(socket); in queues_close() function", ERROR_DEBUG, P2);
	}
	if (mq_close(log_sock_mq))
	{
		error_log("ERROR: mq_close(logger_socket); in queues_close() function", ERROR_DEBUG, P2);
	}
	return OK;
}

/**
 * @brief - This function unlinks all the message queues.
 * 
 * @return err_t 
 */
err_t queues_unlink(void)
{
	if (mq_unlink(HEARTBEAT_QUEUE))
	{
		error_log("ERROR: mq_unlink(heartbeat); in queues_unlink() function", ERROR_DEBUG, P2);
	}

	if (mq_unlink(LOG_QUEUE))
	{
		error_log("ERROR: mq_unlink(logger); in queues_unlink() function", ERROR_DEBUG, P2);
	}

	if (mq_unlink(SOCK_QUEUE))
	{
		error_log("ERROR: mq_unlink(socket); in queues_unlink() function", ERROR_DEBUG, P2);
	}

	if (mq_unlink(LOG_SOCK_QUEUE))
	{
		error_log("ERROR: mq_unlink(logger_socket); in queues_unlink() function", ERROR_DEBUG, P2);
	}
}
