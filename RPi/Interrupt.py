import RPi.GPIO as GPIO
from time import sleep

#ISR
def interrupt_routine(pin):
	print("Interrupt Detected")
	sleep(1)                #wait a second

#setup interrupt
GPIO.setmode(GPIO.BCM)          #use Broadcom notation
GPIO.setup(17, GPIO.IN)         #GPIO17 is input
GPIO.add_event_detect(17, GPIO.FALLING)           #falling edge interrupt on GPIO17
GPIO.add_event_callback(17, interrupt_routine)               #link ISR to te interrupt

try:
	while True:
		x=1

except KeyboardInterrupt:              #Ctrl+C is pressed
	GPIO.cleanup()                 #release GPIO hardware resources
	exit()                         #exit program