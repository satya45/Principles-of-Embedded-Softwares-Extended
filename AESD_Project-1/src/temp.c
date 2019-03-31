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

uint16_t read_temp_reg(uint8_t reg)
{
    int temp;
    uint8_t data[2];
    uint16_t final;
    write_pointer(reg);
    if (read(i2c_open, &data, 2) != 2)
    {
        error_log("ERROR: read(); in read_temp_reg() function", ERROR_DEBUG, P2);
    }
    printf("DATA : %x", data[0]|data[1]);
    final = data[0] & 0xFF00;
    final = final | data[1];
    write_pointer(TEMP_REG);
    return final;
}
/**
 * @brief Set Shutdown mode
 * 
 * @return err_t 
 */

uint16_t read_config()
{
    int rc;
    uint8_t data; 
    write_pointer(CONFIG_REG);
    rc = read(i2c_open, &data, 1);
    printf("No of bytes read %d\n\n", rc);
    printf("READ MSB %x", data);
    // printf("READ LSB %x", data[1]);
    return data;
}

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

err_t write_config(uint16_t data)
{
    int temp, rc;
    uint8_t buff[3];
    temp = (uint8_t)data >> 8;
    buff[0] = CONFIG_REG;
    buff[1] = temp;
    buff[2] = (uint8_t)data;
    write_pointer(CONFIG_REG);
    if ((rc = write(i2c_open, buff, 3)) != 3)
    {
        error_log("ERROR: write(); in write_config function", ERROR_DEBUG, P2);
        perror("In write config");
    }
    printf("Written %x", buff[1]|buff[2]);
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
    uint8_t buff[3] = {TLOW_REG, read_buff[1], read_buff[0]};
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
    uint8_t buff[3] = {THIGH_REG, read_buff[1], read_buff[0]};
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

    if (ioctl(i2c_open, I2C_SLAVE, TEMP_ADDR) < 0)
    {
        error_log("ERROR: ioctl(); in write_pointer() function", ERROR_DEBUG, P2);
    }

    if ((rc = write(i2c_open, &reg, 1)) != 1)
    {
        error_log("ERROR: write(); in write_pointer() function", ERROR_DEBUG, P2);
    }
    return 0;
}
