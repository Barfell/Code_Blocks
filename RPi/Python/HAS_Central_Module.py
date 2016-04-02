import requests
import serial
from time import sleep
from time import ctime

#setup serial comm
port="/dev/ttyACM0"            #serial port
serial_arduino=serial.Serial(port, 9600)          #start serial comm@9600bps
serial_arduino.flushInput()                       #clear i/p buffer

while True:
	#get time data
	time_data=ctime()
	serial_arduino.write(time_data[11:13].encode("ascii"))      #hours
	serial_arduino.write(time_data[14:16].encode("ascii"))      #minutes

	#day of the week
	if "Sun" in time_data:
		serial_arduino.write("1".encode("ascii"))
	if "Mon" in time_data:
		serial_arduino.write("2".encode("ascii"))
	if "Tue" in time_data:
		serial_arduino.write("3".encode("ascii"))
	if "Wed" in time_data:
		serial_arduino.write("4".encode("ascii"))
	if "Thu" in time_data:
		serial_arduino.write("5".encode("ascii"))
	if "Fri" in time_data:
		serial_arduino.write("6".encode("ascii"))
	if "Sat" in time_data:
		serial_arduino.write("7".encode("ascii"))

	serial_arduino.write(time_data[8:10].encode("ascii"))     #date

	#month
	if "Jan" in time_data:
		serial_arduino.write("1".encode("ascii"))
	if "Feb" in time_data:
		serial_arduino.write("2".encode("ascii"))
	if "Mar" in time_data:
		serial_arduino.write("3".encode("ascii"))
	if "Apr" in time_data:
		serial_arduino.write("4".encode("ascii"))
	if "May" in time_data:
		serial_arduino.write("5".encode("ascii"))
	if "Jun" in time_data:
		serial_arduino.write("6".encode("ascii"))
	if "Jul" in time_data:
		serial_arduino.write("7".encode("ascii"))
	if "Aug" in time_data:
		serial_arduino.write("8".encode("ascii"))
	if "Sep" in time_data:
		serial_arduino.write("9".encode("ascii"))
	if "Oct" in time_data:
		serial_arduino.write("10".encode("ascii"))
	if "Nov" in time_data:
		serial_arduino.write("11".encode("ascii"))
	if "Dec" in time_data:
		serial_arduino.write("12".encode("ascii"))

	serial_arduino.write(time_data[22:].encode("ascii"))        #year
	
	#download weather data
	json_data=requests.get("http://api.wunderground.com/api/5a08e133d2cfd498/conditions/q/IN/Bengaluru.json")    #get weather data
	weather=json_data.json        #extract data in a hierarchal dictionary

	observation=weather["current_observation"]["weather"]     #this key contains the comment about the weather

	if ("cloud" in observation.lower()) or ("overcast" in observation.lower()):
		serial_arduino.write("C".encode("ascii"))

	if ("clear" in observation.lower()) or ("wind" in observation.lower()):
		serial_arduino.write("A".encode("ascii"))

	if ("rain" in observation.lower()) or ("shower" in observation.lower()) or ("thunder" in observation.lower()):
		serial_arduino.write("R".encode("ascii"))

	if "sun" in observation.lower():
		serial_arduino.write("S".encode("ascii"))

	if "haz" in observation.lower():
		serial_arduino.write("H".encode("ascii"))

	sleep(10)           #wait for 10 seconds