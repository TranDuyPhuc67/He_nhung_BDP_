# BTL HỆ NHÚNG

## GIỚI THIỆU

__Đề bài__: _Copy lại nội dung đề bài được yêu cầu._

__Sản phẩm:__
1. Tính năng
2. Tính năng
3. Tính năng
- Ảnh chụp minh họa:\
  ![Ảnh minh họa](https://soict.hust.edu.vn/wp-content/uploads/logo-soict-hust-1-1024x416.png)

## TÁC GIẢ

- Tên nhóm: BDP
- Thành viên trong nhóm
  |STT|Họ tên|MSSV|Công việc|
  |--:|--|--|--|
  |1|Trần Duy Phúc|20225378|Lấy thiết bị, làm báo cáo|
  |2|Trịnh Văn Bin|20215530|Viết code, lắp mạch|
  |3|Nguyễn Việt Dũng|20210227|Viết code, lắp mạch|
## MÔI TRƯỜNG HOẠT ĐỘNG

- Liệt kê module CPU/dev kit. Ví dụ ESP32 Dev Module, hoặc STM32F429-DISC.
- Liệt kê các kit, module được sử dụng: ví dụ: stm32 cảm biến...

## SO ĐỒ SCHEMATIC

_Cho biết cách nối dây, kết nối giữa các linh kiện_ 
| Chân MicroSD card module | Chân kết nối tương ứng trên ESP32 |
| ------------------------ | --------------------------------- |
| 5V                       | 5V                                |
| CS                       | GPIO 5                            |
| MOSI                     | GPIO 23                           |
| CLK                      | GPIO 18                           |
| MISO                     | GPIO 19                           |
| GND                      | GND                               |


### TÍCH HỢP HỆ THỐNG

- Mô tả các thành phần phần cứng và vai trò của chúng: máy chủ, máy trạm, thiết bị IoT, MQTT Server, module cảm biến IoT...
- Mô tả các thành phần phần mềm và vai trò của chúng, vị trí nằm trên phần cứng nào: Front-end, Back-end, Worker, Middleware...

### ĐẶC TẢ HÀM

- Giải thích một số hàm quan trọng: ý nghĩa của hàm, tham số vào, ra

  ```C
    /**
     * Liệt kê nội dung thư mục trên thẻ SD, bao gồm cả tập tin và thư mục con.
     * Có thể duyệt đệ quy theo cấp độ `levels`.
     * 
     * @param fs       Đối tượng hệ thống tập tin (SD hoặc LittleFS).
     * @param dirname  Đường dẫn thư mục cần liệt kê.
     * @param levels   Số cấp thư mục con cần liệt kê thêm (0 = không đệ quy).
     */
    void listDir(fs::FS &fs, const char * dirname, uint8_t levels);

    /**
     * Tạo một thư mục mới tại đường dẫn được cung cấp.
     * 
     * @param fs    Đối tượng hệ thống tập tin.
     * @param path  Đường dẫn của thư mục cần tạo.
     */
    void createDir(fs::FS &fs, const char * path);

    /**
     * Xóa một thư mục trên thẻ SD.
     * 
     * @param fs    Đối tượng hệ thống tập tin.
     * @param path  Đường dẫn thư mục cần xóa.
     */
    void removeDir(fs::FS &fs, const char * path);

    /**
     * Đọc nội dung của một tập tin và in ra Serial Monitor.
     * 
     * @param fs    Đối tượng hệ thống tập tin.
     * @param path  Đường dẫn của tập tin cần đọc.
     */
    void readFile(fs::FS &fs, const char * path);

    /**
     * Ghi dữ liệu vào tập tin, xóa nội dung cũ nếu có.
     * 
     * @param fs       Đối tượng hệ thống tập tin.
     * @param path     Đường dẫn tập tin.
     * @param message  Dữ liệu cần ghi vào file.
     */
    void writeFile(fs::FS &fs, const char * path, const char * message);

    /**
     * Ghi thêm dữ liệu vào cuối tập tin (giữ nguyên nội dung cũ).
     * 
     * @param fs       Đối tượng hệ thống tập tin.
     * @param path     Đường dẫn tập tin.
     * @param message  Dữ liệu cần ghi thêm.
     */
    void appendFile(fs::FS &fs, const char * path, const char * message);
  
  /**
     * Đổi tên tập tin hoặc chuyển vị trí của nó trong hệ thống tập tin.
     * 
     * @param fs     Đối tượng hệ thống tập tin.
     * @param path1  Tên đường dẫn tập tin ban đầu.
     * @param path2  Tên đường dẫn tập tin mới.
     */
    void renameFile(fs::FS &fs, const char * path1, const char * path2);

  /**
     * Xoá một tập tin khỏi thẻ SD.
     * 
     * @param fs    Đối tượng hệ thống tập tin.
     * @param path  Đường dẫn tập tin cần xóa.
     */
    void deleteFile(fs::FS &fs, const char * path);

  /**
     * Kiểm tra hiệu năng đọc và ghi của hệ thống tập tin bằng cách 
     * đọc và ghi các khối dữ liệu 512 byte.
     * 
     * @param fs    Đối tượng hệ thống tập tin.
     * @param path  Đường dẫn tập tin dùng để kiểm tra.
     */
    void testFileIO(fs::FS &fs, const char * path);

 
  ```
  
### KẾT QUẢ

- Các ảnh chụp với caption giải thích.
- Hoặc video sản phẩm
