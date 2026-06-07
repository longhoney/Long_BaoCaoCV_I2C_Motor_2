// 2026-06-07

#define PIN_IN1 4 //! D4     --> A-IB
#define PIN_IN2 5 //! D5 (~) --> A-IA
#define PIN_IN3 6 //! D6 (~) --> B-IA
#define PIN_IN4 7 //! D7     --> B-IB

// int speed = 50;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  L9110setup();
  Serial.println("Điều khiển xe...");
  // Serial.println("Đi thẳng tốc độ 100%.");
  // car_fw(100, 100);
  Serial.println("Đi thẳng tốc độ 50%.");
  car_fw(50, 50);
  // Serial.println("Đi lùi tốc độ 30%.");
  // car_bw(30, 30);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void L9110setup() {
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  pinMode(PIN_IN3, OUTPUT);
  pinMode(PIN_IN4, OUTPUT);

  digitalWrite(PIN_IN1, LOW);
  digitalWrite(PIN_IN2, LOW);
  digitalWrite(PIN_IN3, LOW);
  digitalWrite(PIN_IN4, LOW);
}

// Định nghĩa các hàm sẽ sử dụng trong chương trình


void car_fw(int speedA, int speedB) {
  // Xử lý giá trị tốc độ nhận được
  // speedA = calculate_speed(speedA);
  // speedB = calculate_speed(speedB);
  motorA_fw(speedA); // Điều khiển motor kênh A quay thuận    //phai nhap so ??%
  motorB_fw(speedB); // Điều khiển motor kênh B quay thuận
}

void car_bw(int speedA, int speedB) {
  // Xử lý giá trị tốc độ nhận được
  // speedA = calculate_speed(speedA);
  // speedB = calculate_speed(speedB);
  motorA_bw(speedA); // Điều khiển motor kênh A quay ngược
  motorB_bw(speedB); // Điều khiển motor kênh B quay ngược
}

void motorA_fw(int speed) {
  speed = calculate_speed(speed);
  digitalWrite(PIN_IN1, LOW);
  analogWrite(PIN_IN2, speed); // ~PWM
}

void motorA_bw(int speed) {
  speed = calculate_speed(speed);
  digitalWrite(PIN_IN1, HIGH);
  analogWrite(PIN_IN2, 255 - speed); // ~PWM
}

void motorB_fw(int speed) {
  // Xử lý giá trị tốc độ nhận được
  speed = calculate_speed(speed);
  digitalWrite(PIN_IN4, LOW);
  analogWrite(PIN_IN3, speed); // ~PWM
}

void motorB_bw(int speed) {
  // Xử lý giá trị tốc độ nhận được
  speed = calculate_speed(speed);
  digitalWrite(PIN_IN4, HIGH);
  analogWrite(PIN_IN3, 255 - speed); // ~PWM
}

int calculate_speed(int speed) {
  // Đảm bảo giá trị tốc độ (%) nằm trong khoảng cho phép
  speed = constrain(speed, 0, 100);

  // Chuyển đổi giá trị tốc độ (%) sang (PWM)
  speed = map(speed, 0, 100, 0, 255);

  return speed;
}
