/*
  Build for Arduino Uno/ MKE-Creator
  Use 4 PWM pins // L298 6 Pins
*/
//Khai báo thư viện
#include "Makerlabvn_SimpleMotor_LONG.h"

// Định nghĩa chân cho L9110
// #define PIN_IN1 6 //! D6   (~) --> A-IB
// #define PIN_IN2 5 //! D5   (~) --> A-IA
// #define PIN_IN3 10 //! D10 (~) --> B-IA
// #define PIN_IN4 11 //! D11 (~) --> B-IB



// Định nghĩa chân cho MKE-Creator // KHONOG THAY DOI TOC DO DUOC
// Định nghĩa chân cho L298
#define PIN_ENA 6 //! D6 (~)
#define PIN_IN1 8 
#define PIN_IN2 9 
#define PIN_IN3 4 
#define PIN_IN4 7 
#define PIN_ENB 5 //! D5 (~)


//Khai báo đối tượng d9110 thuộc class Makerlabvn_SimpleMotor
Makerlabvn_SimpleMotor_LONG d9110; //Not I2C 
// Makerlabvn_SimpleMotor_LONG d9110(64); // For I2C

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Start Test, input from 0 (OFF) to 8");
  Serial.println("Baud 115200, No line ending");
  d9110.setup(PIN_IN1, PIN_IN2, PIN_IN3, PIN_IN4); //4pin
  // d9110.setup(PIN_ENA, PIN_IN1, PIN_IN2, PIN_IN3, PIN_IN4, PIN_ENB); //6pin
  // d9110.setup(64); // For I2C
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    int tempInput = Serial.read();

    switch (tempInput) {
      case '0':
        // digitalWrite(2, HIGH);
        Serial.println("Hai động cơ đứng yên");
        d9110.motorA_stop();
        d9110.motorB_stop();
        break;
      case '1':
        // digitalWrite(3, HIGH);
        Serial.println("Điều khiển động cơ kênh A - Quay thuận 100%");
        d9110.motorA_fw(100);
        d9110.motorB_stop();
        //delay(5000);
        break;
      case '2':
        // digitalWrite(3, HIGH);
        Serial.println("Điều khiển động cơ kênh A - Quay thuận 30%");
        d9110.motorA_fw(30);
        d9110.motorB_stop();
        
        // Serial.println("Xoay trái tốc độ 10%.");
        // d9110.car_rotateL(30);
        // delay(5000);
        break;
      case '3':
        // digitalWrite(4, HIGH);
        Serial.println("Điều khiển động cơ kênh A - Quay ngược 100%");
        d9110.motorA_bw(100);
        d9110.motorB_stop();
        break;
      case '4':
        // digitalWrite(4, HIGH);
        Serial.println("Điều khiển động cơ kênh A - Quay ngược 60%");
        d9110.motorA_bw(60);
        d9110.motorB_stop();
        // Serial.println("Xoay phải tốc độ 50%.");
        // d9110.car_rotateR(20);
        // delay(5000);
        break;
      case '5':
        // digitalWrite(5, HIGH);
        Serial.println("Điều khiển động cơ kênh B - Quay thuận 100%");
        d9110.motorB_fw(100);
        d9110.motorA_stop();
        break;
      case '6':
        // digitalWrite(5, HIGH);
        Serial.println("Điều khiển động cơ kênh B - Quay thuận 50%");
        d9110.motorB_fw(50);
        d9110.motorA_stop();
        break;
      case '7':
        // digitalWrite(6, HIGH);
        Serial.println("Điều khiển động cơ kênh B - Quay ngược 100%");
        d9110.motorB_bw(100);
        d9110.motorA_stop();
        break;
      case '8':
        // digitalWrite(6, HIGH);
        Serial.println("Điều khiển động cơ kênh B - Quay ngược 50%");
        d9110.motorB_bw(50);
        d9110.motorA_stop();
        break;
      default:
        // d9110.motorA_stop();
        // d9110.motorB_stop();
        break;
        
    }
  }

}