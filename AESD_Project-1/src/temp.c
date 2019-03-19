#include "temp.h"


void *temp_thread(void * a)
{
    if(i2c_open = open(i2c_bus, O_RDWR) < 0)
    {
        perror("Error opening I2C bus\n");
    }
    if (ioctl(i2c_open, I2C_SLAVE, TEMP_ADDR) < 0) 
    {
        perror("Failed to acquire bus");
        exit(1);
    }
    if (read(i2c_open,,2) != 2) {
       perror("Failed to read from the i2c bus.\n");

}
}