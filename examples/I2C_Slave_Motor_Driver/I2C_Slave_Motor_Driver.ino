#include "I2C_Slave_Motor_Driver.h"

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

/* ------------------------------------------------------------------------- */
/*                                   OBJECT                                  */
/* ------------------------------------------------------------------------- */
I2C_Slave_Motor_Driver demo;

void setup() {
  Serial.begin(115200);
  Serial.println("Start");
  demo.I2C_setup();
  demo.setup(PIN_ENA, PIN_IN1, PIN_IN2, PIN_IN3, PIN_IN4, PIN_ENB);
}

void loop() {
  
}