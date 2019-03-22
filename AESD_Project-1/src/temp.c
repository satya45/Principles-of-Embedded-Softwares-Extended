 /**
 * @file temp.c
 * @author Satya Mehta & Siddhant Jajoo
 * @brief Functions and variables related to Temperature Sensor 
 * @version 0.1
 * @date 2019-03-19
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "temp.h"

char *i2c_bus = "/dev/i2c-2";
int i2c_open;
char read_buff[2];
void *temp_thread(void * a)
{ 
    read_temp_data();
    read_data(THIGH_REG);
    read_data(TLOW_REG);
    read_data(CONFIG_REG);
    shutdown_mode();
}

int read_temp_data(void)
{
    int temp;
    char temp_buff[2];
    int temp_data[2];
    struct temp obj;
    write_pointer(TEMP_REG);
    if((i2c_open = open(i2c_bus, O_RDWR)) < 0)
    {
        perror("Error opening I2C bus\n");
    }
    if (ioctl(i2c_open, I2C_SLAVE, TEMP_ADDR) < 0) 
    {
        perror("Failed to acquire bus");
        exit(1);
    }
    if (read(i2c_open,temp_buff,2) != 2) 
    {
       perror("Failed to read from the i2c bus.\n");
    }
    temp_data[0] = (int)temp_buff[0]; //storing MSB
    temp_data[1] = (int)temp_buff[1]; //storing LSB
    obj.cel = (float)((temp_data[0] << 8 |temp_data[1]) >> 4) * 0.0625; //referred calculations from http://bildr.org/2011/01/tmp102-arduino/
    obj.far = (obj.cel * 9.0/5.0) + 32;
    obj.kel = obj.cel + 273.15;
    printf("Temperature in Celsius : %f\n", obj.cel);
    printf("Temperature in Farheneit : %f\n", obj.far);
    printf("Temperature in Kelvin : %f\n", obj.kel);
}

int read_data(uint8_t reg)
{
    int temp;
    write_pointer(reg);
    // if((i2c_open = open(i2c_bus, O_RDWR)) < 0)
    // {
    //     perror("Error opening I2C bus\n");
    // }
    // if (ioctl(i2c_open, I2C_SLAVE, TEMP_ADDR) < 0) 
    // {
    //     perror("Failed to acquire bus");
    //     exit(1);
    // }
    if (read(i2c_open,read_buff,2) != 2) 
    {
       perror("Failed to read from the i2c bus.\n");
    }
    printf("Data Read from %d register: %d\n", reg, (int)(read_buff[0]|read_buff[1]));
}

int shutdown_mode(void)
{
    int rc;
    read_data(CONFIG_REG);
    char config_data[2];
    write_pointer(CONFIG_REG);
    config_data[1] = read_buff[1]|0x01;
    config_data[0] = read_buff[0];
    //config_data[0] = CONFIG_REG;
    printf("%d\n", config_data[0] | config_data[1] | config_data[2]);
    if (rc = write(i2c_open,config_data,2) != 2) 
    {
       perror("Failed to write to the i2c bus.\n");
       return 1;
    }
    printf("RC: %d\n", rc);
    read_data(CONFIG_REG);
}


int write_pointer(uint8_t reg)
{
    int rc;
    char buff[4] = {0x00, 0x01, 0x02, 0x03};
    if (ioctl(i2c_open, I2C_SLAVE, TEMP_ADDR) < 0) 
    {
        perror("Failed to acquire bus");
        return 1;
        exit(1);
    }
    if (rc = write(i2c_open,&buff[reg],1) != 1) 
    {
       perror("Failed to write to the i2c bus.\n");
       return 1;
    }
    printf("Written %d bytes\n", rc);
    return 0;

}