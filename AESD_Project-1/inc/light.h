#ifndef _LIGHT_H
#define _LIGHT_H
#include <stdio.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <math.h>
#include <unistd.h>
#include "main.h"


#define LIGHT_ADDR          0x39
#define CNTRL_REG           0x00
#define TIMING_REG          0x01
#define INT_CTRL            0x06
#define ADC0_L              0x0C
#define ADC0_H              0x0D
#define ADC1_L              0x0E
#define ADC1_H              0x0F
#define ID_REG              0x0A
#define ADC0_TH_SEL         0x00
#define ADC1_TH_SEL         0x01
#define ADC0_INT_TH_L       0x02
#define ADC0_INT_TH_H       0x03
#define ADC1_INT_TH_L       0x04
#define ADC1_INT_TH_H       0x05

#define COMMAND_MASK        0x80
#define LOW_GAIN_MASK       0x00
#define HIGH_GAIN_MASK      0x10
#define INT_13_7_MASK       0x00
#define INT_101_MASK        0x01
#define INT_402_MASK        0X02
#define INT_EN_MASK         0x10
#define INT_DIS_MASK        0x00


err_t light_id(void);
err_t write_command(uint8_t);
uint16_t ADC_CH0(void);
uint16_t ADC_CH1(void); 
float lux_data(void);
err_t read_light_reg(uint8_t);
err_t write_timing_reg(uint8_t);
err_t write_int_ctrl(uint8_t);
uint16_t read_int_th(uint8_t);
err_t write_int_th(uint16_t, uint8_t);
sensor_struct read_light_data(uint8_t);
uint16_t read_adc0(void);
#endif