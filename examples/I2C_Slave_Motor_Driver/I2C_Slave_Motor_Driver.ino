#include <Wire.h>
#include "Makerlabvn_SimpleMotor.h"

/* ------------------------------------------------------------------------- */
/*                                   DEFINE                                  */
/* ------------------------------------------------------------------------- */
// Creator
#define PIN_ENA 5    //! (~)
#define PIN_IN1 7
#define PIN_IN2 4
#define PIN_IN3 9
#define PIN_IN4 8
#define PIN_ENB 6    //! (~)

// Định nghĩa I2C Constants
// const uint8_t master_address = 0x50;
uint8_t _addressId = 0;   // Byte giá trị địa chỉ của slave
uint8_t _modeId = 0;    // Byte chế độ điều khiển: DC Motor hay RC Servo
uint8_t _index = 0;   // Byte quy định kênh sẽ điều khiển: A hoặc B
uint8_t _pwm = 0;   // Byte giá trị tốc độ PWM 0-255
uint8_t _dir = 0;   // Byte quy định chiều quay
uint8_t _crc = 0;   // Byte giá trị checksum
uint8_t calculated_crc = 0;
// Khai bao bien luu toc do dang 0-100%
int speedPercent = 0;
/* ------------------------------------------------------------------------- */
/*                                   OBJECT                                  */
/* ------------------------------------------------------------------------- */
Makerlabvn_SimpleMotor demo;


void setup() {
  Serial.begin(115200);
  Wire.begin(64); // Khởi tạo I2C bus
  Wire.onReceive(receiveEvent); // register event
  demo.setup(PIN_ENA, PIN_IN1, PIN_IN2, PIN_IN3, PIN_IN4, PIN_ENB);
  Serial.println("Khoi tao Slave MKE Creator............");
  // motor_ctrl();
}

void loop() {
  // motor_ctrl();
  delay(1000); // Đọc mỗi 100 mili giây
}

// Bước 1: Yêu cầu đọc 6 bytes từ master
void receiveEvent(uint8_t tempCount) {
  Serial.println("count: " + String(tempCount));
  if (tempCount == 6) {
    _addressId = Wire.read();   // Byte giá trị địa chỉ của slave
    _modeId = Wire.read();    // Byte chế độ điều khiển: DC Motor hay RC Servo
    _index = Wire.read();   // Byte quy định kênh sẽ điều khiển: A hoặc B
    _pwm = Wire.read();   // Byte giá trị tốc độ PWM 0-255
    _dir = Wire.read();   // Byte quy định chiều quay
    _crc = Wire.read();   // Byte giá trị checksum
    
    // Bước 2: Tính toán và kiểm tra CRC
      // CRC  là tổng có các dữ liệu truyền đi [ADDRESS_ID] + [MODE_ID] + [INDEX] + [PWM] + [DIR]
      calculated_crc = _addressId + _modeId + _index + _pwm + _dir;
      if (calculated_crc != _crc) {
        Serial.print("Loi CRC! Du lieu khong hop le. CRC nhan: ");
        Serial.print(_crc, HEX);
        Serial.print(", CRC tinh: ");
        Serial.println(calculated_crc, HEX);
        // return false;
      }

    // Bước 3: Chuyển đổi speedPWM sang speedPercent
      cal_speed(_pwm);
    
    // Bước 4: Hiển thị frame đã nhận được
      printData();

     // Bước 5:  Điều khiển động cơ theo lệnh của Master
      motor_ctrl();

  } else {
    Serial.println("Chi nhan duoc: " + String(tempCount) + " byte" + "(yeu cau 6 byte).");
    return false;
  }
}

// Định nghĩa Bước 5: Điều khiển động cơ theo lệnh của Master
  void motor_ctrl() {
  // - Index: Điều khiển motorA hay motorB
  // - dir: 1 = quay thuan -> motorA_fw hoặc motorB_fw
  if (_modeId == 1 && _index == 0 && _dir == 1) {
    // motorA_fw
    Serial.print("Động cơ A quay thuận, tốc độ: "); Serial.print(speedPercent); Serial.println("%");
    demo.motorA_fw(speedPercent);
  } else if (_modeId == 1 && _index == 0 && _dir == 0) {
    Serial.print("Động cơ A quay nghịch, tốc độ: "); Serial.print(speedPercent); Serial.println("%");
    demo.motorA_bw(speedPercent);
  } else if (_modeId == 1 && _index == 1 && _dir == 1) {
    Serial.print("Động cơ B quay thuận, tốc độ: "); Serial.print(speedPercent); Serial.println("%");
    demo.motorB_fw(speedPercent);
  } else if (_modeId == 1 && _index == 1 && _dir == 0) {
    Serial.print("Động cơ B quay nghịch, tốc độ: "); Serial.print(speedPercent); Serial.println("%");
    demo.motorB_bw(speedPercent);
  }
}
// Định nghĩa Bước 3: Chuyển đổi speedPWM -> Percentspeed
  // - PWM: kiểm tra nằm trong 0-255? Chuyển đổi thành 0-100% để phù hợp với thư viện SimpleMotor
  void cal_speed(uint8_t speedPWM) {
    speedPWM = constrain(speedPWM,0,255);
    speedPercent = map(speedPWM,0,255,0,100);
    // return speedPercent;
  }

// Hàm in dữ liệu
  void printData(){
    Serial.print("Frame đã nhận: ");
    Serial.print(_addressId, HEX); Serial.print(" "); Serial.print(_modeId, HEX); Serial.print(" "); Serial.print(_index, HEX); Serial.print(" ");
    Serial.print(_pwm, HEX); Serial.print(" "); Serial.print(_dir, HEX); Serial.print(" "); Serial.println(_crc, HEX);
    Serial.print("CRC tinh lai: "); Serial.println(calculated_crc, HEX);
  }