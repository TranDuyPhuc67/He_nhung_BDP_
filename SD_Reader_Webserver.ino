
#include <WiFi.h>
#include <WebServer.h>
#include <SD.h>
#include <SPI.h>

const char *ssid = "";
const char *password = "";

WebServer server(80);

#define SD_CS 5 // Chip Select cho thẻ SD
// tạo giao diện chính
void handleRoot()
{
    String html = "<html><head><title>ESP32 SD File Manager</title></head><body>";
    html += "<h1>ESP32 SD File Manager</h1>";
    // html += "<form action='/upload' method='POST' enctype='multipart/form-data'>";
    // html += "Select file: <input type='file' name='upload'><br>";
    // html += "<input type='submit' value='Upload'></form>";
    html += "<h1>Write to SD Card</h1>";
    html += "<form action='/write' method='POST'>";
    html += "File name (with .txt): <input name='filename'><br>";
    html += "Content:<br><textarea name='content' rows='10' cols='40'></textarea><br>";
    html += "<input type='submit' value='Save'></form>";
    html += "<h2>Files on SD Card:</h2><ul>";
    File root = SD.open("/");
    while (true)
    {
        File entry = root.openNextFile();
        if (!entry)
            break;
        html += "<li><a href='/download?file=" + String(entry.name()) + "'>" + String(entry.name()) + "</a>";
        html += " <a href='/delete?file=" + String(entry.name()) + "'>[Delete]</a></li>";
        entry.close();
    }
    html += "</ul></body></html>";
    server.send(200, "text/html", html);
}
// hàm ghi file mới
void handleWriteFile()
{
    if (!server.hasArg("filename") || !server.hasArg("content"))
    {
        server.send(400, "text/plain", "Missing filename or content");
        return;
    }

    String filename = "/" + server.arg("filename");
    String content = server.arg("content");

    File file = SD.open(filename, FILE_WRITE);
    if (!file)
    {
        server.send(500, "text/plain", "Failed to open file for writing");
        return;
    }

    file.print(content);
    file.close();

    String response = "<html><body><h2>File written successfully!</h2>";
    response += "<a href='/'>Go Back</a></body></html>";
    server.send(200, "text/html", response);
}
// File uploadFile;

// void handleFileUpload() {
//   HTTPUpload& upload = server.upload();

//   if (upload.status == UPLOAD_FILE_START) {
//     String filename = "/" + upload.filename;
//     Serial.println("Upload Start: " + filename);
//     uploadFile = SD.open(filename, FILE_WRITE);
//   } else if (upload.status == UPLOAD_FILE_WRITE) {
//     // Ghi phần dữ liệu đang được tải lên
//     if (uploadFile) {
//       uploadFile.write(upload.buf, upload.currentSize);
//     }
//   } else if (upload.status == UPLOAD_FILE_END) {
//     if (uploadFile) {
//       uploadFile.close();
//       Serial.println("Upload End: File size: " + String(upload.totalSize));
//     }
//     server.send(200, "text/html", "<h2>Upload thành công!</h2><a href='/'>Quay lại</a>");
//   }
// }
// hàm xem nội dung file
void handleDownload()
{
    if (!server.hasArg("file"))
    {
        server.send(400, "text/plain", "File not specified");
        return;
    }
    String path = "/" + server.arg("file");
    Serial.print(path);
    File file = SD.open(path);
    if (!file)
    {
        server.send(404, "text/plain", "File not found !");
        return;
    }
    // while(file.available()){
    //   server.streamFile(file, "application/octet-stream");
    // }
    String content = "";
    while (file.available())
    {
        content += (char)file.read(); // hoặc file.readStringUntil('\n') nếu cần từng dòng
    }
    file.close();
    String response = "<html><body><h2>File : " + String(path) + "</h2>";
    response += "<p>" + content + "</p>";
    response += "<form action='/write' method='POST'>";
    response += "<input type='hidden' name='filename' value='" + server.arg("file") + "'>";
    response += "<textarea name='content' rows='15' cols='60'>" + content + "</textarea><br>";
    response += "<input type='submit' value='Save'>";
    response += "</form></body></html>";
    server.send(200, "text/html", response); // hoặc "text/html" nếu là HTML
}
// hàm xóa file
void handleDelete()
{
    if (!server.hasArg("file"))
    {
        server.send(400, "text/plain", "File not specified");
        return;
    }
    String path = "/" + server.arg("file");
    if (!SD.exists(path))
    {
        server.send(404, "text/plain", "File not found");
        return;
    }
    SD.remove(path);
    server.sendHeader("Location", "/");
    server.send(303);
}

void setup()
{
    Serial.begin(115200);

    // Kết nối WiFi
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected! IP: " + WiFi.localIP().toString());

    // Khởi tạo SD
    if (!SD.begin(5))
    {
        Serial.println("Card Mount Failed");
        return;
    }
    uint8_t cardType = SD.cardType();

    if (cardType == CARD_NONE)
    {
        Serial.println("No SD card attached");
        return;
    }

    Serial.print("SD Card Type: ");
    if (cardType == CARD_MMC)
    {
        Serial.println("MMC");
    }
    else if (cardType == CARD_SD)
    {
        Serial.println("SDSC");
    }
    else if (cardType == CARD_SDHC)
    {
        Serial.println("SDHC");
    }
    else
    {
        Serial.println("UNKNOWN");
    }

    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    Serial.printf("SD Card Size: %lluMB\n", cardSize);

    // Đăng ký route
    server.on("/", handleRoot);
    server.on("/upload", HTTP_POST, []() {}, handleFileUpload);
    server.on("/write", HTTP_POST, handleWriteFile);
    server.on("/download", handleDownload);
    server.on("/delete", handleDelete);

    server.begin();
    Serial.println("HTTP server started.");
}

void loop()
{
    server.handleClient();
}
