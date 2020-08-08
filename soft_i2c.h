/**
 * *****************************************
 * 
 * Soft I2C Bus Interface; 
 * 
 * Speed: 100kbps, one pulse time: 5us
 * Duty cycles: 50%
 * Addr mode: 7bit
 * Have ack: yes
 * 
 * *****************************************
*/

#ifndef _H_SOFT_I2C
#define _H_SOFT_I2C

//--------- interface define --------

#include <soft_i2c_conf.h>

#if !defined(I2C_SCL_HIGH) || !defined(I2C_SCL_LOW)
#error "Macro 'I2C_SCL_HIGH()' and 'I2C_SCL_LOW()' must be implemented !"
#endif

#if !defined(I2C_SDA_HIGH) || !defined(I2C_SDA_LOW)
#error "Macro 'I2C_SDA_HIGH()' and 'I2C_SDA_LOW()' must be implemented !"
#endif

#if !defined(I2C_SCL_Read)
#error "Macro 'I2C_SCL_Read()' must be implemented !"
#endif

#if !defined(I2C_SDA_Read)
#error "Macro 'I2C_SDA_Read()' must be implemented !"
#endif

//------------------------

#ifdef I2C_USE_FAST_MODE

#if !defined(I2C_Delay500ns)
#error "Macro 'I2C_Delay500ns()' must be implemented !"
#endif

#define HalfPulseTime() I2C_Delay500ns() // 0.5 us
#else

#if !defined(I2C_Delay2_5us)
#error "Macro 'I2C_Delay2_5us()' must be implemented !"
#endif

#define HalfPulseTime() I2C_Delay2_5us() // 2.5 us
#endif

#define PulseTime()  HalfPulseTime(), HalfPulseTime()

//------------------------

typedef enum
{
    NACK = 0,
    ACK
} I2C_ACK;

typedef enum
{
    I2C_OK = 0,
    I2C_ERROR,
    I2C_BUSY
} I2C_RESULT;

typedef enum
{
    I2C_DIRECTION_EMITTER = 0,
    I2C_DIRECTION_RECEIVER
} I2C_Direction;

I2C_RESULT I2C_Start(void);

I2C_RESULT I2C_Stop(void);

I2C_ACK I2C_SendByte(uint8_t dat);

I2C_ACK I2C_Send7BitAddr(uint8_t addr, I2C_Direction direction);

uint8_t I2C_ReceiveByte(void);

#endif
