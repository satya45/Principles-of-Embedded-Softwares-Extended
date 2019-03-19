#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <stdint.h>
#include <sys/time.h>
#include "light.h"
#include "temp.h"
#include "logger.h"
#include "sockets.h"


#define SENSOR_THREADS (3)
