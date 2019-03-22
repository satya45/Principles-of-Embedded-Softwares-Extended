#ifndef _TEMP_H
#define _TEMP_H
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>

#define TEMP_ADDR (0x48)
#define TEMP_REG (0)
#define CONFIG_REG (1)
#define THIGH_REG (3)
#define TLOW_REG (2)

//Function Declarations
void *temp_thread(void *);
int read_data(uint8_t);
int read_temp_data(void);
int write_pointer(uint8_t);
int shutdown_mode(void);
#endif
