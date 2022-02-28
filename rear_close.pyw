import serial				# tells python to use serial library
import time				# tells python to use time library
ser = serial.Serial('COM6', 115200)	# sets the serial comm port and baud rate
time.sleep(0.1)				# wait 0.1s
ser.write(b'L163')			# send command over serial
ser.close()				# closes serial port