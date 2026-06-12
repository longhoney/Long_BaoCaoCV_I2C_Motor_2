# Long_BaoCaoCV_I2C_Motor_2
Tiếp tục dự án từ ngày 7/6/2026

1. Thêm các thư viện cơ bản, hình ảnh và chương trình mẫu
2. Đặt câu hỏi định hướng
    - Nhánh điều khiển: (MASTER) [Uno] <<< I2C >>> (SLAVE) [STC8 <<< PWM >>> L9110] <<< Power >>> DC Motor
    - Ta cần viết chương trình theo đúng tính năng của MKE-M17: Slave nhận lệnh từ Master và điều khiển động cơ. Tôi dần nhận ra khi đang khảo sát kiểu truyền nhận
    - Chương trình Master truyền lệnh đã có sẵn trong thư mục chương trình mẫu của Thư viện Makerlabvn_I2C_Motor_Driver
3. Dùng Uno điều khiển L9110: thay đổi tốc độ ở cả 2 chiều quay -> Có thể thay thế bằng mạch [MKE Creator V2](https://hshop.vn/mach-makeredu-creator-arduino-uno-compatible) để tiết kiệm thời
4. Tạo thư viện Makerlabvn_SimpleMotor_LONG
    - Đổi tên đối tượng L298 4pin -> L9110
    - Bổ sung lệnh cấu hình chân ENA, ENB dạng OUTPUT
    - Tắt 2 lệnh cal_speed(speedA, speedB) trong 2 hàm car_fw() và car_bw()
    - Tổng hợp tại [Google Sheet](https://docs.google.com/spreadsheets/d/1pauv_eXI9WxPK2DNi59jDcf7WH-pYOTJTPTRPNfatLw/edit?usp=sharing)
5. Test lại thư viện Maklerlabvn_SimpleMotor_LONG với MKE Creator V2
    - MKE Creator V1 không nối 2 chân PWM cho mỗi kênh L9110
    - Xem tại sheet "MKE-Creator"
7. Lựa chọn chương trình Slave phù hợp với chương trình Master của thư viện MKL_I2C_Motor_Driver
8. Viết thư viện I2C Slave dựa theo nội dung của chương trình Slave, tham khảo cấu trúc thư viện của Makerlabvn_SimpleMotor và Makerlabvn_I2C_Motor_Driver
