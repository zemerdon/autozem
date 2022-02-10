import serial
import time
ser = serial.Serial('COM6', 115200)
time.sleep(0.1)
ser.write(b'L163')
ser.close()