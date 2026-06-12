#ifndef _I2C_Slave_Motor_Driver_H_
#define _I2C_Slave_Motor_Driver_H_

#include "Arduino.h"
#include <Wire.h>

typedef struct
{
  uint8_t addressId;
  uint8_t modeId;
  uint8_t index;
  uint8_t pwm; // pwm
  uint8_t dir; // dir
  uint8_t checkSum;
} str_serial_data_dcMotor;

class I2C_Slave_Motor_Driver
{
  public:
  private:
};

#endif