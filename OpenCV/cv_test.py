import time
import numpy
import cv2

#motor control function
def motor_ctrl(angle):
	if ((angle>=175 and angle<=180) or (angle>=0 and angle<=5)):
		print "GO STRAIGHT"
	elif (angle<175 and angle>=90):
		print "TURN LEFT"
	elif (angle>5 and angle<=90):
		print "TURN RIGHT"

#############################################main program#############################################
img=cv2.imread("/home/udayan/Downloads/Straight3.png", -1)    #read image, 0=read as grayscale, -1=read as color

img2gray=cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)    #convert to grayscale

edges=cv2.Canny(img, 50, 200)             #Canny edge detection; Hough line transform APIs only take binary images

########################general Hough Transform########################
lines=cv2.HoughLines(edges, 1, numpy.pi/180, 105)         #calc Hough transform for lines; 1st argument=input image, 2nd & 3rd arguments: rho & angle accuracies respectively, 4th argument=threshold i.e. which means minimum vote it should get for it to be considered as a line
               
motor_ctrl(int(lines[0, 0, 1]*57.3))   #make decision, 180/numpy.pi=57.3

#######################################################################
######################################################################################################
