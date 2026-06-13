/* ------------------------------------------------------------------------- */
/*                                  LIBRARY                                  */
/* ------------------------------------------------------------------------- */

#include "I2C_Slave_Motor_Driver.h"

/* ------------------------------------------------------------------------- */
/*                        HÀM TẠO + HÀM ĐIỀU KHIỂN MOTÔR                     */
/* ------------------------------------------------------------------------- */

// Vì đã kế thừa thư viện Makerlabvn_SimpleMotor_LONG nên không cần triển khai lại
// các hàm tạo và hàm điều khiển motor trong thư viên MKL_SimpleMotor

/* ------------------------------------------------------------------------- */
/*                            HÀM CỦA I2C SLAVE                              */
/* ------------------------------------------------------------------------- */

// Khai báo instance
I2C_Slave_Motor_Driver* I2C_Slave_Motor_Driver::instance = nullptr;

I2C_Slave_Motor_Driver::I2C_Slave_Motor_Driver() {
    instance = this;
}

void I2C_Slave_Motor_Driver::I2C_setup() {
  Wire.begin(64); // Khởi tạo I2C bus
  Wire.onReceive(I2C_Slave_Motor_Driver::receiveEvent); // register event
}

void I2C_Slave_Motor_Driver::receiveEvent(int tempCount)
{
    if(instance != nullptr)
    {
        instance->receiveEventInternal(tempCount);
    }
}

void I2C_Slave_Motor_Driver::receiveEventInternal(int tempCount) {
  Serial.println("count: " + String(tempCount));
  if (tempCount == 6) {
    motorData._addressId = Wire.read();   // Byte giá trị địa chỉ của slave
    motorData._modeId = Wire.read();    // Byte chế độ điều khiển: DC Motor hay RC Servo
    motorData._index = Wire.read();   // Byte quy định kênh sẽ điều khiển: A hoặc B
    motorData._pwm = Wire.read();   // Byte giá trị tốc độ PWM 0-255
    motorData._dir = Wire.read();   // Byte quy định chiều quay
    motorData._crc = Wire.read();   // Byte giá trị checksum
    
    // Bước 2: Tính toán và kiểm tra CRC
      // CRC  là tổng có các dữ liệu truyền đi [ADDRESS_ID] + [MODE_ID] + [INDEX] + [PWM] + [DIR]
      check_crc();

    // Bước 3: Chuyển đổi speedPWM sang speedPercent
      cal_speed(motorData._pwm);
    
    // Bước 4: Hiển thị frame đã nhận được
      printData();

     // Bước 5:  Điều khiển động cơ theo lệnh của Master
      motor_ctrl();

  } else {
    Serial.println("Chi nhan duoc: " + String(tempCount) + " byte" + "(yeu cau 6 byte).");
    // return false;
    return; 
  }
}

void I2C_Slave_Motor_Driver::motor_ctrl() {
  // - Index: Điều khiển motorA hay motorB
  // - dir: 1 = quay thuan -> motorA_fw hoặc motorB_fw
  if (motorData._modeId == 1 && motorData._index == 0 && motorData._dir == 1) {
    // motorA_fw
    Serial.print("Động cơ A quay thuận, tốc độ: "); Serial.print(speedPercent); Serial.println("%");
    motorA_fw(speedPercent);
  } else if (motorData._modeId == 1 && motorData._index == 0 && motorData._dir == 0) {
    Serial.print("Động cơ A quay nghịch, tốc độ: "); Serial.print(speedPercent); Serial.println("%");
    motorA_bw(speedPercent);
  } else if (motorData._modeId == 1 && motorData._index == 1 && motorData._dir == 1) {
    Serial.print("Động cơ B quay thuận, tốc độ: "); Serial.print(speedPercent); Serial.println("%");
    motorB_fw(speedPercent);
  } else if (motorData._modeId == 1 && motorData._index == 1 && motorData._dir == 0) {
    Serial.print("Động cơ B quay nghịch, tốc độ: "); Serial.print(speedPercent); Serial.println("%");
    motorB_bw(speedPercent);
  }
}

void I2C_Slave_Motor_Driver::cal_speed(uint8_t speedPWM) {
  speedPWM = constrain(speedPWM,0,255);
  speedPercent = map(speedPWM,0,255,0,100);
}

void I2C_Slave_Motor_Driver::check_crc() {
  calculated_crc = motorData._addressId + 
                   motorData._modeId + 
                   motorData._index +
                   motorData._pwm +
                   motorData._dir;

  if (calculated_crc != _crc) {
    Serial.print("Loi CRC! Du lieu khong hop le. CRC nhan: ");
    Serial.print(_crc, HEX);
    Serial.print(", CRC tinh: ");
    Serial.println(calculated_crc, HEX);
    // return false;
    return;
  }
}

void I2C_Slave_Motor_Driver::printData() {
  Serial.print("Frame đã nhận: ");
    Serial.print(motorData._addressId, HEX); Serial.print(" "); Serial.print(motorData._modeId, HEX); Serial.print(" "); 
    Serial.print(motorData._index, HEX); Serial.print(" "); Serial.print(motorData._pwm, HEX); Serial.print(" "); 
    Serial.print(motorData._dir, HEX); Serial.print(" "); Serial.println(motorData._crc, HEX);
    Serial.print("CRC tinh lai: "); Serial.println(calculated_crc, HEX);
}