# Phần cứng
1. [Vietduino ESP32](https://hshop.vn/mach-phat-trien-vietduino-esp32)
2. [Động cơ bơm khí 370 Air Pump Motor 12VDC](https://hshop.vn/dong-co-dc-bom-370-air-pump-12vdc)
3. [Nguồn Power Adaptor AC-DC 12V 2A](https://hshop.vn/nguon-power-adaptor-ac-dc-12v-2a)
4. [Dây DC Cái 5.5 x 2.1mm Female DC Power Jack Wire](https://hshop.vn/day-dc-cai-5-5-2-1-mm)
5. [Mạch điều khiển tốc độ động cơ Mini PWM DC Motor Speed Controller 10A](https://hshop.vn/mach-dieu-khien-toc-do-dong-co-mini-pwm-dc-motor-speed-controller-10a)

# Phần mềm
1. ArduinoIDE
2. Driver [chip nạp code (CH340)](https://sparks.gogo.co.nz/ch340.html)
# Sơ đồ kết nối
![alt text](cirkit_ESP32_AGR12-1.png)

# Logic của chương trình
BƯỚC 1: Gửi lệnh đo lường (0xAC 0x12) (Xử lý lỗi truyền I2C nếu cần)

BƯỚC 2: Chờ 80ms để cảm biến hoàn tất phép đo

BƯỚC 3: Yêu cầu đọc 3 byte dữ liệu (DATA0, DATA1, CRC)

BƯỚC 4: Tính toán và kiểm tra CRC. CRC là kết quả của DATA0 XOR DATA1 [24, Bảng 5]

BƯỚC 5: Chuyển đổi dữ liệu thành giá trị áp suất
- Ghép 2 byte dữ liệu thành giá trị 16 bit (kPa * 10)
- Ép kiểu thành số nguyên có dấu 16 bit (Signed Short Int) để xử lý áp suất âm (nếu có, ví dụ AGR12xxPxx hoặc AGR12xxNxx)
- Chia cho 10.0 để có giá trị áp suất thực tế (kPa)

BƯỚC 6: Hiển thị kết quả
- Số byte ESP32 đọc được (biến count)
- Dữ liệu dạng HEX ESP32 đọc được từ cảm biến | CRC ESP32 tính lại
- Giá trị áp suất thực tế

# Hướng dẫn nạp code với ArduinoIDE
1. Trỏ đường dẫn sketch book đến thư mục chứa chương trình trong  File/Preferences
<img width="1225" height="816" alt="image" src="https://github.com/user-attachments/assets/b84f2bc1-ad83-437a-8b0b-108654035439" />

2. Chọn chương trình "I2C_AGR12_Pressure_Sensor_ESP32" tại File/Sketchbook/examples/
<img width="1920" height="688" alt="image" src="https://github.com/user-attachments/assets/b34f027a-6e8b-4565-a393-374b09190ff7" />


3. Board chọn ESP32 Dev Module, Chọn PORT tương ứng với cổng COM của mạch Arduino (kiểm tra tại Device Manager)
_Kiểm tra COM tại Device Manager_
<img width="1920" height="1380" alt="image" src="https://github.com/user-attachments/assets/8eec95d7-d04f-4ccf-81d9-743b45e8f141" />

_Chọn board_
<img width="1920" height="639" alt="image" src="https://github.com/user-attachments/assets/d323ddc1-c568-4d88-8881-768b71c61afd" />

4. Bấm Upload để nạp code
<img width="1920" height="700" alt="image" src="https://github.com/user-attachments/assets/3ed60d5e-e761-4b4c-9af3-400055308ade" />

