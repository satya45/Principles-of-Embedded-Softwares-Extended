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


/**
 * @brief Read Temperature
 * 
 * @param temp_unit 
 * @param id 
 * @return sensor_struct 
 */
sensor_struct read_temp_data(uint8_t temp_unit, uint8_t id)
{
    int temp;
    char temp_buff[2];
    int temp_data[2];
    sensor_struct read_data;
    write_pointer(TEMP_REG); //select temperature register

    if (read(i2c_open, temp_buff, 2) != 2)
    {
        error_log("ERROR: read(); in read_temp_data() function", ERROR_DEBUG, P2);
    }
    temp_data[0] = (int)temp_buff[0]; //storing MSB
    temp_data[1] = (int)temp_buff[1]; //storing LSB

    read_data.id = id;
    if (clock_gettime(CLOCK_REALTIME, &read_data.sensor_data.temp_data.data_time))
    {
        error_log("ERROR: clock_gettime(); in read_temp_data() function", ERROR_DEBUG, P2);
    }
    read_data.sensor_data.temp_data.temp_c = (float)((temp_data[0] << 8 | temp_data[1]) >> 4) * 0.0625; //referred calculations from http://bildr.org/2011/01/tmp102-arduino/
    if (temp_unit == 1)
    {
        read_data.sensor_data.temp_data.temp_c = read_data.sensor_data.temp_data.temp_c + 273; //Kelvin Computations
    }
    else if (temp_unit == 2)
    {
        read_data.sensor_data.temp_data.temp_c = ((9.0 / 5.0) * (read_data.sensor_data.temp_data.temp_c)) + 32; //Farhenheit calculations
    }
    return read_data;
}

/**
 * @brief Can be used to read any temperature register
 * 
 * @param reg 
 * @return err_t 
 */

err_t read_temp_reg(uint8_t reg)
{
    int temp;
    write_pointer(reg);
    if (read(i2c_open, read_buff, 2) != 2)
    {
        error_log("ERROR: read(); in read_temp_reg() function", ERROR_DEBUG, P2);
    }
    printf("Data Read from %d register: %x\n", reg, (int)(read_buff[0] | read_buff[1]));
    write_pointer(TEMP_REG);
    return 0;
}
/**
 * @brief Set Shutdown mode
 * 
 * @return err_t 
 */

err_t shutdown_mode(void)
{

    int rc;
    read_temp_reg(CONFIG_REG);
    write_pointer(CONFIG_REG);
    read_buff[1] = read_buff[1] | 0x01;
    char buff[3] = {CONFIG_REG, read_buff[1], read_buff[0]};
    if ((rc = write(i2c_open, buff, 3)) != 3)
    {
        error_log("ERROR: write(); in shutdown_mode() function", ERROR_DEBUG, P2);
    }
    printf("RC: %d\n", rc);
    read_temp_reg(CONFIG_REG);
    write_pointer(TEMP_REG);
    return 0;
}

/**
 * @brief Write to the tlow register
 * inside the sensor
 * @param data 
 * @return err_t 
 */

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
    if ((rc = write(i2c_open, &buff, 3)) != 3)
    {
        error_log("ERROR: write(); in write_tlow() function", ERROR_DEBUG, P2);
    }
    write_pointer(TEMP_REG);
}

/**
 * @brief Wrte to thigh register
 *inside the sensor.
 * @param data 
 * @return err_t 
 */
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
    if ((rc = write(i2c_open, &buff, 3)) != 3)
    {
        error_log("ERROR: write(); in write_thigh() function", ERROR_DEBUG, P2);
    }
    write_pointer(TEMP_REG);
}


/**
 * @brief Write to pointer register avaialable inside the sensor.
 * 
 * @param reg 
 * @return err_t 
 */
err_t write_pointer(uint8_t reg)
{
    int rc;
    char buff[4] = {0x00, 0x01, 0x02, 0x03};

    if (ioctl(i2c_open, I2C_SLAVE, TEMP_ADDR) < 0)
    {
        error_log("ERROR: ioctl(); in write_pointer() function", ERROR_DEBUG, P2);
    }

    if ((rc = write(i2c_open, &buff[reg], 1)) != 1)
    {
        error_log("ERROR: write(); in write_pointer() function", ERROR_DEBUG, P2);
    }
    return 0;
}
