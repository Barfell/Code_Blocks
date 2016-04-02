import serial
from time import sleep

#setup serial comm
port="/dev/ttyACM0"            #serial port
serial_arduino=serial.Serial(port, 9600)          #start serial comm@9600bps
serial_arduino.flushInput()                       #clear i/p buffer

try:
	while True:
		if(serial_arduino.inWaiting()>0):               #check for incoming data
			input=serial_arduino.readline()             #get data
			#using serial_arduino.read() display each byte separately on a newline in the terminal
			#using serial_arduino.readline() reads all the bytes till it encounters a "/n" and then displays the bytes together on 1 line
			print(input)                            #display received data
		serial_arduino.write("S".encode("ascii"))      #send data to the arduino in ASCII format
		sleep(1)       #wait a second

except KeyboardInterrupt:              #Ctrl+C is pressed
	exit()                         #exit program