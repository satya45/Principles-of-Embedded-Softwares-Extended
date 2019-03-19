#ifndef _TEMP_H
#define _TEMP_H
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>

#define TEMP_ADDR (0x48)
char *i2c_bus = "/dev/i2c-2";
int i2c_open;
int temp_data[2];
void *temp_thread(void *);
#endif