# Các bước thực hiện trong trong chương trình 
- Bước 1: Yêu cầu đọc 6 bytes từ master
- Bước 2: Tính toán và kiểm tra CRC. CRC là tổng các dữ liệu truyền đi: [ADDRESS_ID] + [MODE_ID] + [INDEX] + [PWM] + [DIR]
- Bước 3: Chuyển đổi speedPWM sang speedPercent
    - PWM: kiểm tra nằm trong 0-255? Chuyển đổi thành 0-100% để phù hợp với thư viện SimpleMotor
- Bước 4: Hiển thị frame đã nhận được
- Bước 5: Điều khiển motor theo lệnh của Master
    - Index: Điều khiển motorA hay motorB
    - dir: 1 = quay thuan -> motorA_fw hoặc motorB_fw

### DC Motor
Address: 0x40 = 64

ModeId: 1

Index: 0 (MA) va 1 (MB)

PWM: 0 -> 255

Dir: 1 (thuan) va 0 (nghich)

[CHECKSUM_LOWBYTE] = [ADDRESS_ID] + [MODE_ID] + [INDEX] + [PWM] + [DIR]

# Cấu trúc chung của 1 thư viện
_Slave nên khai báo biến dạng cấu trúc như của master_
### File .h
1. Khai báo thư viện + các biến cố định (#define hoặc enum hoặc typedef enum)
2. Class chính của thư viện

Class Makerlabvn_SimpleMotor kế thừa từ class kxnTask, có 2 thuộc tính private và 1 thuộc tính public
    
    - Nó muốn dùng lại các chức năng của kxnTask
    - Thuộc tính private đầu tiên khai báo các biến nội bộ để giao tiếp I2C
    - Thuộc tính private thứ hai  khai báo chân sử dụng trong thư viện và hàm đặt tốc độ (0-100% sang 0-255 PWM)
    - Thuộc tính pulic: 
        - Đối tượng Makerlabvn_SimpleMotor: 4pin, 6pin, I2C
        - Hàm cấu hình địa chỉ I2C, hàm cấu hình chân
        - Hàm điều khiển motor
        - Hàm điều khiển xe

class Makerlabvn_I2C_Motor_Driver có 1  thuộc tính private và 1 thuộc tính public

    - Thuộc tính public: Khai báo các hàm điều khiển DC Motor và hàm điều khiển RC Servo
    - Thuộc tính private
_Mẫu của thư viện MKL_SimpleMotor_
_Mẫu của thư viện MKL_I2C_Motor_Driver_
### File .cpp
