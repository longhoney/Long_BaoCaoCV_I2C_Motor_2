// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

String dataHex = "";

void setup() {
  Wire.begin(64);                // join I2C bus with address #8 //dia chi I2C cua Slave dang thap phan
  Wire.onReceive(receiveEvent); // register event //con tro ham
  Serial.begin(115200);           // start serial for output //UArt1
}

void loop() {
  delay(1000);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) { //dem Byte nhan ve
  //dataHex = "";
  while (Wire.available()) { // loop through all but the last //sanSang //chua 1 byte
    byte c = Wire.read(); // receive byte as a character
    // Serial.print(c,HEX);         // print the character in Hex format
    // Serial.print(c);
    // Serial.print(" ");  //leave space
   
    // In HEX và ghép chuỗi
    dataHex += String(c, HEX);
  }
  // Chuyển thành chữ HOA cho dễ so sánh
  dataHex.toUpperCase();
  
  Serial.print("Nhan duoc: ");
  Serial.println(dataHex);
  dataHex = "" ;
}