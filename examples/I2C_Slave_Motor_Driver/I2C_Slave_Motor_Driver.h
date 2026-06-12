#ifndef _I2C_Slave_Motor_Driver_H_
#define _I2C_Slave_Motor_Driver_H_

/* ------------------------------------------------------------------------- */
/*                                  LIBRARY                                  */
/* ------------------------------------------------------------------------- */
#include "Arduino.h"
#include <Wire.h>

#define MAX_I2C_MOTOR_DC_SIZE (2)

typedef struct
{
  uint8_t _addressId;
  uint8_t _modeId;
  uint8_t _index;
  uint8_t _pwm; // pwm
  uint8_t _dir; // dir
  uint8_t _checkSum;
} str_serial_data_dcMotor;

/* ------------------------------------------------------------------------- */
/*                                   CLASS                                   */
/* ------------------------------------------------------------------------- */

class I2C_Slave_Motor_Driver
{
  public:
  private:
    /* ----------------------- (BIẾN) CẤU HÌNH CÁC PIN ----------------------- */
    uint8_t _pinIn1;
    uint8_t _pinIn2;
    uint8_t _pinIn3;
    uint8_t _pinIn4;
    uint8_t _pinEnA;
    uint8_t _pinEnB;

    /* --------------------------- (HÀM) ĐẶT TỐC ĐỘ -------------------------- */

    /**
    * Đảm bảo giá trị tốc độ (%) nhận được trong khoảng 0% đến 100%
    * Đồng thời chuyển đổi tốc độ (%) sang thang (PWM) tương ứng
    */
    int calculate_speed(int speed);

};

#endif