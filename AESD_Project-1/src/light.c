#include "light.h"

char read_buff;
/*
void *light_thread(void *f)
{
    printf("In light thread");
    light_id();
    printf("Lux Data :%f\n", lux_data());
    read_light_reg(CNTRL_REG);
    printf("Data read in control reg %x\n", (int)read_buff);
    read_light_reg(TIMING_REG);
    printf("Data read in timing reg %x\n", (int)read_buff);
    write_timing_reg(HIGH_GAIN_MASK);
    read_light_reg(TIMING_REG);
    printf("Data read in timing reg %x\n", (int)read_buff);
    read_light_reg(INT_CTRL);
    printf("Data Read from Interr control reg %x\n", (int)read_buff);
    write_int_ctrl(INT_EN_MASK);
    read_light_reg(INT_CTRL);
    printf("Data Read from Interr control reg %x\n", (int)read_buff);
    uint16_t th = read_int_th(ADC0_TH_SEL);
    printf("Data read from the ADC0 threshold %x\n",th);
    write_int_th(0x50, ADC0_TH_SEL);
    th = read_int_th(ADC0_TH_SEL);
    printf("Data read from the ADC0 threshold %x\n",th);
    th = read_int_th(ADC1_TH_SEL);
    printf("Data read from the ADC1 threshold %x\n",th);
    write_int_th(0x50, ADC1_TH_SEL);
    th = read_int_th(ADC1_TH_SEL);
    printf("Data read from the ADC1 threshold %x\n",th);
}
*/

sensor_struct read_light_data(uint8_t id)
{
    sensor_struct read_data;
    if (ioctl(i2c_open, I2C_SLAVE, LIGHT_ADDR) < 0) 
    {
        error_log("ERROR: ioctl(); in read_light_data function");
    }
    write_command(CNTRL_REG);
    char buff = 0x03;
    if(write(i2c_open,&buff,1) != 1) 
    {
       error_log("ERROR: write(); in read_light_data function");
    }
    read_data.id = id;
    if (clock_gettime(CLOCK_REALTIME, &read_data.sensor_data.light_data.data_time))
    {
        error_log("ERROR: clock_gettime(); in read_light_data() function");
    }
    read_data.sensor_data.light_data.light = lux_data();
    return read_data;    
}

err_t light_id(void)
{
    if((i2c_open = open(I2C_BUS, O_RDWR)) < 0)
    {
        error_log("ERROR: open(); in light_id() function");
    }
    if (ioctl(i2c_open, I2C_SLAVE, LIGHT_ADDR) < 0) 
    {
        error_log("ERROR: ioctl(); in light_id() function");
    }
    write_command(CNTRL_REG);
    char buff = 0x03;
    if(write(i2c_open,&buff,1) != 1) 
    {
       error_log("ERROR: write(); in light_id() function");
    }
    write_command(ID_REG);
    char id;
    if (read(i2c_open,&id,1) != 1) 
    {
       error_log("ERROR: read(); in light_id() function");
    }
    printf("Light Id: %x\n", (int)id);
    return 0;
}

err_t write_command(uint8_t reg_addr)
{
    char buff = COMMAND_MASK|reg_addr;
    if(write(i2c_open,&buff,1) != 1) 
    {
       error_log("ERROR: write(); in write_command() function");
    }
    return 0;

}

uint16_t ADC_CH0(void)
{
    uint8_t lsb, msb;
    uint16_t ch0;
    write_command(ADC0_L);
    if (read(i2c_open,&lsb,1) != 1) 
    {
       error_log("ERROR: read(lsb); in ADC_CH0() function");
    }
    write_command(ADC0_H);
    if (read(i2c_open,&msb,1) != 1) 
    {
       error_log("ERROR: read(msb); in ADC_CH0() function");
    }
    msb = msb << 8;
    ch0 = msb|lsb;
    return ch0;

}

uint16_t read_adc0(void)
{
    uint16_t data;
    if((i2c_open = open(I2C_BUS, O_RDWR)) < 0)
    {
        error_log("ERROR: open(); in light_id() function");
    }
    if (ioctl(i2c_open, I2C_SLAVE, LIGHT_ADDR) < 0) 
    {
        error_log("ERROR: ioctl(); in light_id() function");
    }
    data = ADC_CH0();
    return data;

}

uint16_t ADC_CH1(void)
{
    uint8_t lsb, msb;
    uint16_t ch1;
    write_command(ADC1_L);
    if (read(i2c_open,&lsb,1) != 1) 
    {
       error_log("ERROR: read(lsb); in ADC_CH1() function");
    }
    write_command(ADC1_H);
    if (read(i2c_open,&msb,1) != 1) 
    {
       error_log("ERROR: read(msb); in ADC_CH1() function");
    }
    msb = msb << 8;
    ch1 = msb|lsb;
    return ch1;
}

float lux_data(void)
{
    uint16_t adc0, adc1;
    adc0 = ADC_CH0();
    adc1 = ADC_CH1();
    float final_adc = (float)(adc1/adc0);
    float lux_data;
    if( 0 < final_adc <= 0.50)
    {
        lux_data = (0.0304 * adc0) - ((0.062 * adc0) * (pow((adc1/adc0), 1.4)));
    }
    else if (0.5 < final_adc <= 0.61)
    {
        lux_data = (0.0224 * adc0) - (0.031 * adc1);
    }
    else if (0.61 < final_adc <= 0.8)
    {
        lux_data = (0.0128 * adc0) - (0.0153 * adc1);
    }
    else if (0.8 < final_adc <= 1.3)
    {
        lux_data = (0.00146 * adc0) - (0.00112*adc1);
    }
    else if(final_adc > 1.30)
    {
        lux_data = 0;
    }
    return lux_data;
    //return adc0;
}

err_t read_light_reg(uint8_t reg)
{
    write_command(reg);
    if (read(i2c_open, &read_buff,1) != 1) 
    {
       error_log("ERROR: read(); in read_light_reg() function");
    }
    return 0;

}

err_t write_timing_reg(uint8_t data)
{
    write_command(TIMING_REG);
    read_light_reg(TIMING_REG);
    data = data | read_buff;
    if(write(i2c_open,&data,1) != 1) 
    {
       error_log("ERROR: write(); in write_timing_reg() function");
    }
    return 0;
}

err_t write_int_ctrl(uint8_t data)
{
    write_command(INT_CTRL);
    read_light_reg(INT_CTRL);
    data = data | read_buff;
    if(write(i2c_open,&data,1) != 1) 
    {
      error_log("ERROR: write(); in write_int_reg() function");
    }
    return 0;

}

uint16_t read_int_th(uint8_t reg)
{
    uint16_t data;
    uint8_t temp;
    if(reg == 0)
    {
        read_light_reg(ADC0_INT_TH_L);
        temp = read_buff;
        read_light_reg(ADC0_INT_TH_H);
        data = read_buff;
        data = data << 8;
        data = data | temp;

    }
    if(reg == 1)
    {
        read_light_reg(ADC1_INT_TH_L);
        temp = read_buff;
        read_light_reg(ADC1_INT_TH_H);
        data = read_buff;
        data = data << 8;
        data = data | temp;

    }
    return data;
}

err_t write_int_th(uint16_t data, uint8_t reg)
{
    uint8_t temp;
    if(reg == 0)
    {
        write_command(ADC0_INT_TH_L);
        temp = data & 0x00FF;
        if(write(i2c_open,&temp,1) != 1) 
        {
            error_log("ERROR: write(); reg = 0; in write_int_th() function");
        }
        write_command(ADC0_INT_TH_H);
        temp = data >> 8;
        if(write(i2c_open,&temp,1) != 1) 
        {
            error_log("ERROR: write(); reg = 0; in write_int_th() function");
        }
    }
    if(reg == 1)
    {
        write_command(ADC1_INT_TH_L);
        temp = data & 0x00FF;
        if(write(i2c_open,&temp,1) != 1) 
        {
           error_log("ERROR: write(); reg = 1; in write_int_th() function");
        }
        write_command(ADC1_INT_TH_H);
        temp = data >> 8;
        if(write(i2c_open,&temp,1) != 1) 
        {
            error_log("ERROR: write(); reg = 1; in write_int_th() function");
        }
    }
    return 0;
}