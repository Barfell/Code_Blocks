import RPi.GPIO as GPIO
from time import sleep

#setup PWM
GPIO.setmode(GPIO.BCM)                         #use Broadcom notation
GPIO.setup(17, GPIO.OUT)                       #GPIO17 is output
analog_out=GPIO.PWM(17, 100)                   #setup GPIO17 for PWM at 100Hz
analog_out.start(0)                            #start PWM at 0% duty cycle

try:
	while True:
		for dc in range(0, 101, 5):
			analog_out.ChangeDutyCycle(dc)             #change duty cycle
			sleep(0.1)                                 #wait for 0.1 second
		for dc in range(100, -1, -5):
			analog_out.ChangeDutyCycle(dc)             #change duty cycle
			sleep(0.1)                                 #wait for 0.1 second

except KeyboardInterrupt:              #Ctrl+C is pressed
	analog_out.stop()              #stop PWM
	GPIO.cleanup()                 #release GPIO hardware resources
	exit()                         #exit program