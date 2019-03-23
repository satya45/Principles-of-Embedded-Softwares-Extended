#ifndef _TEMP_H
#define _TEMP_H
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include "main.h"
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#define TEMP_ADDR (0x48)
#define TEMP_REG (0)
#define CONFIG_REG (1)
#define THIGH_REG (3)
#define TLOW_REG (2)

char read_buff[2];

//Function Declarations
void *temp_thread(void *);
err_t read_temp_reg(uint8_t);
err_t read_temp_data(void);
err_t write_pointer(uint8_t);
err_t shutdown_mode(void);
err_t write_tlow(uint16_t);
err_t write_thigh(uint16_t);
#endif