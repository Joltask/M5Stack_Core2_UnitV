from machine import UART
from fpioa_manager import fm
import sensor, image, time

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time=2000)

fm.register(34, fm.fpioa.UART2_TX)  # TX Pin
fm.register(35, fm.fpioa.UART2_RX)  # RX Pin

# UART
uart = UART(UART.UART2, 115200)

while True:
    img = sensor.snapshot()

    jpg = img.compress(quality=50)
    buf = jpg.to_bytes()
    length = len(buf)

    uart.write(b'\xAA\x55')
    uart.write(bytes([length & 0xFF, (length >> 8) & 0xFF]))
    uart.write(buf)
