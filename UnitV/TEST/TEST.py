from machine import UART
from fpioa_manager import fm
import time

# WICHTIG: Pins zuweisen!
fm.register(34, fm.fpioa.UART2_TX)  # TX Pin
fm.register(35, fm.fpioa.UART2_RX)  # RX Pin

uart = UART(UART.UART2, 115200)

while True:
    uart.write("HELLO\n")
    time.sleep(1)
