#include <M5Unified.h>

HardwareSerial SerialCam(2);

#define HEADER1 0xAA
#define HEADER2 0x55

uint8_t *buf = NULL;

void setup() {
  Serial.begin(115200); 

  auto cfg = M5.config();
  M5.begin(cfg);

  SerialCam.begin(115200, SERIAL_8N1, 13, 14);

  buf = (uint8_t*)malloc(20000);
  M5.Display.fillScreen(BLACK);
}

bool waitForHeader() {
  while (SerialCam.available() >= 2) {
    if (SerialCam.read() == HEADER1) {
      if (SerialCam.read() == HEADER2) {
        return true;
      }
    }
  }
  return false;
}

void loop() {
  if (!waitForHeader()) return;

  while (SerialCam.available() < 2);
  uint16_t len = SerialCam.read() | (SerialCam.read() << 8);
  Serial.println(len);

  if (len > 20000) return;

  int i = 0;
  while (i < len) {
    if (SerialCam.available()) {
      buf[i++] = SerialCam.read();
    }
  }

  M5.Display.drawJpg(buf, len, 0, 0);
}