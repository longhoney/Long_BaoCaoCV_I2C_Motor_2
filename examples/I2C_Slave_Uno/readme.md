Master gửi tốc độ dạng PWM 0-255 (HEX) --> Tắt hàm cal_speed trên motorA_fw() luôn

- Bước 1: Yêu cầu đọc 6 bytes từ master
- Bước 2: Tính toán và kiểm tra CRC
- Bước 3: Phân tích nội dung Master gửi để thực hiện lệnh
    - Index: Điều khiển motorA hay motorB
    - dir: 1 = quay thuan -> motorA_fw hoặc motorB_fw
    - PWM: kiểm tra nằm trong 0-255? OK thì đưa vào biến speed của hàm motorA_fw hoặc motorB_fw
- Bước 4: Điều khiển động cơ theo lệnh của Master
- Bước 5: Hiển thị kết quả
    - Nhận được frame này
    - Động cơ A/B quay thuận/nghịch tốc độ xx%