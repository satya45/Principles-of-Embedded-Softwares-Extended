#ifndef _QUEUE_H
#define _QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>
#include <mqueue.h>
#include <errno.h>

#define HEARTBEAT_QUEUE			("/mq1")
#define LOG_QUEUE				("/mq2")
#define SOCK_QUEUE				("/mq3")
#define LOG_SOCK_QUEUE			("/mq4")


mqd_t heartbeat_mq;
mqd_t log_mq;
mqd_t sock_mq;
mqd_t log_sock_mq;
char x[100];

//function declarations
int queue_init(void);
void queue_send(void);


#endif
