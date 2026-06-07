# Long_BaoCaoCV_I2C_Motor_2
Tiếp tục dự án từ ngày 7/6/2026

1. Thêm các thư viện cơ bản, hình ảnh và chương trình mẫu
2. Đặt câu hỏi định hướng
    - Nhánh điều khiển: (MASTER) [Uno] <<< I2C >>> (SLAVE) [STC8 <<< PWM >>> L9110] <<< Power >>> DC Motor
    - Ta cần viết chương trình theo đúng tính năng của MKE-M17: Slave nhận lệnh từ Master và điều khiển động cơ. Tôi dần nhận ra khi đang khảo sát kiểu truyền nhận
    - Chương trình Master truyền lệnh đã có sẵn trong thư mục chương trình mẫu của Thư viện Makerlabvn_I2C_Motor_Driver
