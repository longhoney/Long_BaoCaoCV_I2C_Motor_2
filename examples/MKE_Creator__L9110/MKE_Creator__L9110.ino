// Định nghĩa chân cho L298 và MKE-Creator
#define PIN_ENA 6 //! D6 (~)
#define PIN_IN1 8 // M+
#define PIN_IN2 9 // M-
#define PIN_IN3 4 // M+
#define PIN_IN4 7 // M-
#define PIN_ENB 5 //! D5 (~)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(PIN_ENA, OUTPUT);
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  pinMode(PIN_IN3, OUTPUT);
  pinMode(PIN_IN4, OUTPUT);
  pinMode(PIN_ENB, OUTPUT);

  digitalWrite(PIN_ENA, LOW);
  digitalWrite(PIN_IN1, LOW);
  digitalWrite(PIN_IN2, LOW);
  digitalWrite(PIN_IN3, LOW);
  digitalWrite(PIN_IN4, LOW);
  digitalWrite(PIN_ENB, LOW);

  // Serial.println("Motor A quay thuận 100%"); motorA_fw(100);
  // Serial.println("Motor A quay thuận 30%"); motorA_fw(30);
  // Serial.println("Motor A quay nghịch 100%"); motorA_bw(100);
  Serial.println("Motor A quay nghịch 30% __"); motorA_bw(30);
}

void loop() {
  // put your main code here, to run repeatedly:

}

int calculate_speed(int speed) {
  // Đảm bảo giá trị tốc độ (%) nằm trong khoảng cho phép
  speed = constrain(speed, 0, 100);

  // Chuyển đổi giá trị tốc độ (%) sang (PWM)
  speed = map(speed, 0, 100, 0, 255);

  return speed;
}

void motorA_fw(int speed) {
  speed = calculate_speed(speed);
  digitalWrite(PIN_IN1, 1);
  digitalWrite(PIN_IN2, 0);
  analogWrite(PIN_ENA, speed);
}

void motorA_bw(int speed) {
  speed = calculate_speed(speed);
  digitalWrite(PIN_IN1, 0);
  digitalWrite(PIN_IN2, 1);
  analogWrite(PIN_ENA, speed);
}