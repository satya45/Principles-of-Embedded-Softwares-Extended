/**
 * @file gpio.c
 * @Satya Mehta & Siddhant Jajoo
 * @brief 
 * Function to initialize GPIO and control USR LED on Beaglebone
 * @version 0.1
 * @date 2019-03-22
 * Some part referred from https://stackoverflow.com/questions/34261512/gpio-on-beaglebone-black
 * Tested using command lines.
 * @copyright Copyright (c) 2019
 * 
 */
#include "gpio.h"


err_t gpio_init(uint8_t pin)
{
    FILE *fptr;
    fptr = fopen("/sys/class/gpio/export", "w");
    if(fptr == NULL)
    {
        perror("File open failed in GPIO init\n");
        return errno;
    }
    fseek(fptr,0,SEEK_SET); //set cursor to 0th position
    fprintf(fptr,"%d", pin);
    if(fclose(fptr) != 0)
    {
        perror("Fclose failed in Gpio init\n");
        return errno;
    }
}

err_t gpio_ctrl(char * directory, char *value, uint8_t onoff)
{
    FILE *fptr;
    fptr = fopen(directory, "w");
    if(fptr == NULL)
    {
        perror("File open failed in GPIO opening direction\n");
        return errno;
    }
    fseek(fptr,0,SEEK_SET); //set cursor to 0th position
    fprintf(fptr,"%s","out"); //set gpio pin to output
    if(fclose(fptr) != 0)
    {
        perror("Fclose failed in Gpio direction\n");
        return errno;
    }
    fptr = fopen(value, "w");
    if(fptr == NULL)
    {
        perror("File open failed in GPIO opening direction\n");
        return errno;
    }
    fseek(fptr,0,SEEK_SET); //set cursor to 0th position
    fprintf(fptr,"%d",onoff); //set gpio pin value to high
    if(fclose(fptr) != 0)
    {
        perror("Fclose failed in Gpio setting value\n");
        return errno;
    }

}