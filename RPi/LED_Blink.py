import RPi.GPIO
import time

RPi.GPIO.setmode(RPi.GPIO.BCM)        #use Broadcom notation
RPi.GPIO.setup(17, RPi.GPIO.OUT)      #GPIO17 is OUTPUT

#blink LED
try:
	while True:
		RPi.GPIO.output(17, RPi.GPIO.HIGH)         #turn on LED
		time.sleep(1)          #wait a second 
		RPi.GPIO.output(17, RPi.GPIO.LOW)         #turn off LED
		time.sleep(1)          #wait a second

except KeyboardInterrupt:              #Ctrl+C is pressed
	analog_out.stop()              #stop PWM
	GPIO.cleanup()                 #release GPIO hardware resources
	exit()                         #exit program