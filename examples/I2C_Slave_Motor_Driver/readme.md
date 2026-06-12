

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
### File .cpp