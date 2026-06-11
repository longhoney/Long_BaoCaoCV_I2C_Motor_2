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
const uint8_t master_address = 0x50;
// const uint8_t AGR12_I2C_ADDRESS = 0x50; // Địa chỉ I2C 7-bit (từ 0xA0/0xA1)
// const uint8_t CMD_MEASURE_HIGH = 0xAC; // Byte lệnh 1 [8]
// const uint8_t CMD_MEASURE_LOW = 0x12;  // Byte lệnh 2 [8]
// const int WAIT_TIME_MS = 80;           // Thời gian chờ sau khi gửi lệnh đo (ms) [8]
uint8_t _addressId = 0;   // Byte giá trị địa chỉ của slave
uint8_t _modeId = 0;    // Byte chế độ điều khiển: DC Motor hay RC Servo
uint8_t _index = 0;   // Byte quy định kênh sẽ điều khiển: A hoặc B
uint8_t _pwm = 0;   // Byte giá trị tốc độ PWM 0-255
uint8_t _dir = 0;   // Byte quy định chiều quay
uint8_t _crc = 0;   // Byte giá trị checksum
uint8_t calculated_crc = 0;
// Khai bao bien gop byte
// String dataHex = "";
// Khai bao bien luu toc do dang 0-100%
uint8_t speedPercent = 0;
/* ------------------------------------------------------------------------- */
/*                                   OBJECT                                  */
/* ------------------------------------------------------------------------- */
Makerlabvn_SimpleMotor demo;


void setup() {
  Serial.begin(115200);
  Wire.begin(64); // Khởi tạo I2C bus
  demo.setup(PIN_ENA, PIN_IN1, PIN_IN2, PIN_IN3, PIN_IN4, PIN_ENB);
  Serial.println("Khoi tao Slave MKE Creator...");
}

void loop() {
  if (readData()) {
    // Đã đọc thành công, kết quả được in trong hàm readPressure
  } else {
    Serial.println("Loi doc du lieu tu Master.");
  }
  delay(100); // Đọc mỗi 100 mili giây
}

bool readData() {
  // Bước 1: Yêu cầu đọc 6 bytes từ master
  uint8_t tempCount = Wire.requestFrom(master_address, 6);
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
      // Thực hiện qua hàm cal_speed()
    
    // Bước 4: Hiển thị frame đã nhận được
      printData();

    // Bước 5: Điều khiển động cơ theo lệnh của Master
      // - Index: Điều khiển motorA hay motorB
      // - dir: 1 = quay thuan -> motorA_fw hoặc motorB_fw
      if (_index == 0 && _dir == 1) {
        // motorA_fw
        Serial.println("Động cơ A quay thuận, tốc độ: " + String(speedPercent) + "%");
        demo.motorA_fw(speedPercent);
      } else if (_index == 0 && _dir == 0) {
        Serial.println("Động cơ A quay nghịch, tốc độ: " + String(speedPercent) + "%");
        demo.motorA_bw(speedPercent);
      } else if (_index == 1 && _dir == 1) {
        Serial.println("Động cơ B quay thuận, tốc độ: " + String(speedPercent) + "%");
        demo.motorB_fw(speedPercent);
      } else if (_index == 1 && _dir == 0) {
        Serial.println("Động cơ B quay nghịch, tốc độ: " + String(speedPercent) + "%");
        demo.motorB_bw(speedPercent);
      }
  } else {
    Serial.println("Chi nhan duoc: " + String(tempCount) + " byte" + "(yeu cau 6 byte).");
    return false;
  }
  
}
/*bool readPressure() {
  // BƯỚC 1: Gửi lệnh đo lường (0xAC 0x12) [8]
  Wire.beginTransmission(AGR12_I2C_ADDRESS);
  Wire.write(CMD_MEASURE_HIGH); 
  Wire.write(CMD_MEASURE_LOW); 
  uint8_t error = Wire.endTransmission(); 

  if (error != 0) {
    // Xử lý lỗi truyền I2C nếu cần
    Serial.print("Loi I2C khi gui lenh: ");
    Serial.println(error);
    return false;
  }
  
  // BƯỚC 2: Chờ 80ms để cảm biến hoàn tất phép đo [8]
  delay(WAIT_TIME_MS);

  // BƯỚC 3: Yêu cầu đọc 3 byte dữ liệu (DATA0, DATA1, CRC) [8]
  uint8_t tempCount = Wire.requestFrom(AGR12_I2C_ADDRESS, 3);
  // if (Wire.requestFrom(AGR12_I2C_ADDRESS, 3) == 3) {
  Serial.println("count: " + String(tempCount));
  if (tempCount == 3) {
    uint8_t data0 = Wire.read(); // Byte dữ liệu áp suất cao (DATA0) [8]
    uint8_t data1 = Wire.read(); // Byte dữ liệu áp suất thấp (DATA1) [8]
    uint8_t crc = Wire.read();   // Byte CRC kiểm tra [8]

    // BƯỚC 4: Tính toán và kiểm tra CRC
    // CRC là kết quả của DATA0 XOR DATA1 [24, Bảng 5]
    uint8_t calculated_crc = data0 ^ data1; 
    
    if (calculated_crc != crc) {
      Serial.print("Loi CRC! Du lieu khong hop le. CRC nhan: ");
      Serial.print(crc, HEX);
      Serial.print(", CRC tinh: ");
      Serial.println(calculated_crc, HEX);
      // return false;
    }

    // BƯỚC 5: Chuyển đổi dữ liệu thành giá trị áp suất 
    
    // Ghép 2 byte dữ liệu thành giá trị 16 bit (kPa * 10)
    // kPa = (DATA0 << 8) | DATA1; [10]
    uint16_t raw_pressure_data = (data0 << 8) | data1;
    
    // Ép kiểu thành số nguyên có dấu 16 bit (Signed Short Int) 
    // để xử lý áp suất âm (nếu có, ví dụ AGR12xxPxx hoặc AGR12xxNxx) [10]
    int16_t signed_raw_data = (int16_t)raw_pressure_data; 
    
    // Chia cho 10.0 để có giá trị áp suất thực tế (kPa) [10]
    float pressure_kPa = (float)signed_raw_data / 10.0;
    
    // BƯỚC 6: Hiển thị kết quả
    Serial.print("Raw: ");
    Serial.print(signed_raw_data);
    Serial.print(" (0x");
    Serial.print(data0, HEX);
    Serial.print(data1, HEX);
    Serial.print(") | Ap suat: ");
    Serial.print(pressure_kPa, 1);
    Serial.println(" kPa");

    return true;

  } else {
    Serial.println("Khong nhan du du lieu (yeu cau 3 byte). " + String(tempCount));
    return false;
  }
}*/

/*void i2c_50Khz()
{
  
  Wire.begin(); 
  // *** THIẾT LẬP TỐC ĐỘ I2C ***
  Wire.setClock(50000); 
  
  Serial.println("Khoi tao cam bien AGR12 I2C voi toc do 50 kHz...");
}*/

// Triển khai Bước 3: Chuyển đổi speedPWM -> Percentspeed
  // - PWM: kiểm tra nằm trong 0-255? Chuyển đổi thành 0-100% để phù hợp với thư viện SimpleMotor
  uint8_t cal_speed(uint8_t speedPWM) {
    speedPWM = constrain(speedPWM, 0, 255);
    speedPercent = map(speedPWM, 0, 255, 0, 100);
    return speedPercent;
  }

// Hàm in dữ liệu
  void printData() {
    // uint8_t _addressId = Wire.read();   // Byte giá trị địa chỉ của slave
    // uint8_t _modeId = Wire.read();    // Byte chế độ điều khiển: DC Motor hay RC Servo
    // uint8_t _index = Wire.read();   // Byte quy định kênh sẽ điều khiển: A hoặc B
    // uint8_t _pwm = Wire.read();   // Byte giá trị tốc độ PWM 0-255
    // uint8_t _dir = Wire.read();   // Byte quy định chiều quay
    // uint8_t _crc = Wire.read();   // Byte giá trị checksum
    Serial.print("Frame đã nhận: ");
    Serial.print(_addressId, HEX); Serial.print(" "); Serial.print(_modeId, HEX); Serial.print(" "); Serial.print(_index, HEX); Serial.print(" ");
    Serial.print(_pwm, HEX); Serial.print(" "); Serial.print(_dir, HEX); Serial.print(" "); Serial.println(_crc, HEX);
    Serial.print("CRC tinh lai: "); Serial.println(calculated_crc, HEX);
  }