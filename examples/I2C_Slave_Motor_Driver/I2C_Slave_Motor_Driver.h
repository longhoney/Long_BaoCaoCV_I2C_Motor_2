#ifndef _I2C_Slave_Motor_Driver_H_
#define _I2C_Slave_Motor_Driver_H_

/* ------------------------------------------------------------------------- */
/*                                  LIBRARY                                  */
/* ------------------------------------------------------------------------- */
#include "Arduino.h"
#include <Wire.h>
#include <Makerlabvn_SimpleMotor_LONG.h>

// #define MAX_I2C_MOTOR_DC_SIZE (2)

/* ------------------------------------------------------------------------- */
/*                                   CLASS                                   */
/* ------------------------------------------------------------------------- */

class I2C_Slave_Motor_Driver : public Makerlabvn_SimpleMotor_LONG
{
  public:
    // Vì đã kế thừa thư viện Makerlabvn_SimpleMotor_LONG nên có thể dùng lại các hàm sau đây:
      /* Makerlabvn_SimpleMotor(uint8_t paI2cAddress);

      void setup_(
      uint8_t pinEnA, uint8_t pinIn1, uint8_t pinIn2,
      uint8_t pinIn3, uint8_t pinIn4, uint8_t pinEnB
      );
      // ------------------------- HÀM ĐIỀU KHIỂN MOTOR ------------------------ 
      void motorA_fw_(int speed); // Điều khiển motor kênh A quay thuận
      void motorB_fw_(int speed); // Điều khiển motor kênh B quay thuận

      void motorA_bw_(int speed); // Điều khiển motor kênh A quay ngược
      void motorB_bw_(int speed); // Điều khiển motor kênh B quay ngược
      */
    
    // Các hàm mới của thư viện I2C_Slave_Motor_Driver
      void I2C_setup();
      void receiveEvent(uint8_t tempCount);
      void motor_ctrl();
      void printData();
      void check_crc();
      void cal_speed(uint8_t speedPWM);
  private:
    /* ----------------------- (BIẾN) CẤU HÌNH CÁC PIN ----------------------- */
    uint8_t _pinIn1;
    uint8_t _pinIn2;
    uint8_t _pinIn3;
    uint8_t _pinIn4;
    uint8_t _pinEnA;
    uint8_t _pinEnB;

    /* BIẾN DỮ LIỆU I2C TRONG FRAME TRUYỀN */
    struct SerialDataDcMotor
    {
      uint8_t _addressId;
      uint8_t _modeId;
      uint8_t _index;
      uint8_t _pwm; // pwm
      uint8_t _dir; // dir
      uint8_t _crc;
    } ;

    SerialDataDcMotor motorData;

    int speedPercent;
    uint8_t calculated_crc;
};

#endif