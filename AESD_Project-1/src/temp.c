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
#include "gpio.h"

void *temp_thread(void * a)
{ 
    gpio_init(LED1);
    while(1)
    {
        for(int i = 0; i < 100000000; i++);
        gpio_ctrl(GPIO53, GPIO53_V, 1);
        for(int i = 0; i < 100000000; i++);
        gpio_ctrl(GPIO53, GPIO53_V, 0);
    }
   // read_temp_data();
    // read_temp_reg(THIGH_REG);
    // read_temp_reg(TLOW_REG);
    // read_temp_reg(CONFIG_REG);
    // //shutdown_mode();
    // read_temp_reg(CONFIG_REG);
    // write_tlow(50);
    // read_temp_reg(TLOW_REG);
    // write_thigh(70); //write Thigh register
    // read_temp_reg(THIGH_REG);

}

err_t read_temp_data(void)
{
    int temp;
    char temp_buff[2];
    int temp_data[2];
    temp_struct obj;
    write_pointer(TEMP_REG);
    if((i2c_open = open(I2C_BUS, O_RDWR)) < 0)
    {
        perror("Error opening I2C bus\n");
        return errno;
    }
    if (ioctl(i2c_open, I2C_SLAVE, TEMP_ADDR) < 0) 
    {
        perror("Failed to acquire bus");
        return errno;
    }
    if (read(i2c_open,temp_buff,2) != 2) 
    {
       perror("Failed to read from the i2c bus.\n");
       return errno;
    }
    temp_data[0] = (int)temp_buff[0]; //storing MSB
    temp_data[1] = (int)temp_buff[1]; //storing LSB
    obj.temp_c = (float)((temp_data[0] << 8 |temp_data[1]) >> 4) * 0.0625; //referred calculations from http://bildr.org/2011/01/tmp102-arduino/
   // obj.far = (obj.cel * 9.0/5.0) + 32;
    //obj.kel = obj.cel + 273.15;
    printf("Temperature in Celsius : %f\n", obj.temp_c);
    obj.id = temp_rcv;
   // printf("Temperature in Farheneit : %f\n", obj.far);
    //printf("Temperature in Kelvin : %f\n", obj.kel);
    return 0;
}

err_t read_temp_reg(uint8_t reg)
{
    int temp;
    write_pointer(reg);
    if (read(i2c_open,read_buff,2) != 2) 
    {
       perror("Failed to read from the i2c bus.\n");
       return errno;
    }
    printf("Data Read from %d register: %x\n", reg, (int)(read_buff[0]|read_buff[1]));
    write_pointer(TEMP_REG);
    return 0;
}

err_t shutdown_mode(void)
{

    int rc;
    read_temp_reg(CONFIG_REG);
    write_pointer(CONFIG_REG);
    read_buff[1] = read_buff[1]|0x01;
    char buff[3] = {CONFIG_REG, read_buff[1], read_buff[0]};
    if (rc = write(i2c_open,buff,3) != 3) 
    {
       perror("Failed to write to the i2c bus.\n");
       return errno;
    }
    printf("RC: %d\n", rc);
    read_temp_reg(CONFIG_REG);
    write_pointer(TEMP_REG);
    return 0;
}

err_t write_tlow(uint16_t data)
{
    int rc;
    int temp;
    temp = data & 0x00FF;
    data = data & 0xFF00;
    read_temp_reg(TLOW_REG);
    read_buff[1] = temp;
    read_buff[0] = data;
    write_pointer(TLOW_REG);
    char buff[3] = {TLOW_REG, read_buff[1], read_buff[0]};
    if (rc = write(i2c_open, &buff,3) != 3) 
    {
       perror("Failed to write to the i2c bus.\n");
       return errno;
    }
    write_pointer(TEMP_REG);

}
err_t write_thigh(uint16_t data)
{
    int rc;
    int temp;
    temp = data & 0x00FF;
    data = data & 0xFF00;
    read_temp_reg(THIGH_REG);
    read_buff[1] = temp;
    read_buff[0] = data;
    write_pointer(THIGH_REG);
    char buff[3] = {THIGH_REG, read_buff[1], read_buff[0]};
    if (rc = write(i2c_open, &buff,3) != 3) 
    {
       perror("Failed to write to the i2c bus.\n");
       return errno;
    }
    write_pointer(TEMP_REG);

}

err_t write_pointer(uint8_t reg)
{
    int rc;
    char buff[4] = {0x00, 0x01, 0x02, 0x03};
    if (rc = write(i2c_open,&buff[reg],1) != 1) 
    {
       perror("Failed to write to the i2c bus.\n");
       return errno;
    }
    return 0;

}
