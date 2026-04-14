#include <M5Unified.h>

HardwareSerial SerialCam(2);

String incoming = "";

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);

  SerialCam.begin(115200, SERIAL_8N1, 13, 14);

  M5.Display.fillScreen(BLACK);
  M5.Display.setTextSize(2);
  M5.Display.setCursor(0, 0);
}

void loop() {
  while (SerialCam.available()) {
    char c = SerialCam.read();

    // Zeilen sammeln
    if (c == '\n') {
      M5.Display.println(incoming);
      incoming = "";
    } else {
      incoming += c;
    }
  }
}