#include "soft_i2c.h"

#define I2C_Init() I2C_SDA_HIGH(), I2C_SCL_HIGH()

void I2C_Start(void)
{
    I2C_Init();
    HalfPulseTime();
    I2C_SDA_LOW();
    HalfPulseTime();
    I2C_SCL_LOW();
    HalfPulseTime();
}

void I2C_Stop(void)
{
    I2C_SDA_LOW();
    I2C_SCL_HIGH();
    HalfPulseTime();
    I2C_SDA_HIGH();
    HalfPulseTime();
}

I2C_ACK I2C_Send7BitAddr(uint8_t addr, I2C_Direction direction)
{
    return I2C_SendByte(addr | (uint8_t)direction);
}

I2C_ACK I2C_SendByte(uint8_t dat)
{
    uint8_t i;

    for (i = 0; i < 8; i++)
    {
        if (dat & 0x80)
        {
            I2C_SDA_HIGH();
        }
        else
        {
            I2C_SDA_LOW();
        }

        dat <<= 1;

        I2C_SCL_HIGH();
        PulseTime();
        I2C_SCL_LOW();
        PulseTime();
    }

    // free SDA pin and wait
    I2C_SDA_HIGH();
    HalfPulseTime();

    // get ACK
    I2C_SCL_HIGH();
    HalfPulseTime();
    i = I2C_SDA_Read();
    HalfPulseTime();
    I2C_SCL_LOW();
    PulseTime();

    return (I2C_ACK)(i == 0);
}

uint8_t I2C_ReceiveByte(void)
{
    uint8_t i, dat = 0;

    // set input mode
    I2C_SDA_HIGH();
    HalfPulseTime();

    for (i = 0; i < 8; i++)
    {
        I2C_SCL_HIGH();
        HalfPulseTime();
        dat <<= 1;
        dat |= I2C_SDA_Read();
        HalfPulseTime();
        I2C_SCL_LOW();
        PulseTime();
    }

    // send ACK
    I2C_SDA_LOW();
    HalfPulseTime();
    I2C_SCL_HIGH();
    PulseTime();
    I2C_SCL_LOW();
    PulseTime();

    return dat;
}
