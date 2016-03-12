#import CV libraries
import numpy
import cv2

img=cv2.imread("/home/udayan/Downloads/blue_ball.jpg", -1)    #read image, 0=read as grayscale, -1=read as color

hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)     # Convert RGB to HSI

#define range of blue color in HSI, numpy array needed for this
lower_blue=numpy.array([50,170,10])
upper_blue=numpy.array([179,255,255])    #maximum values of HSI respectively

mask=cv2.inRange(hsv, lower_blue, upper_blue) #Threshold the HSI image to get only blue colors

#Bitwise-AND mask and original image
result=cv2.bitwise_and(img, img, mask=mask)

cv2.imshow('img', img)   #show image in a window named "img"

cv2.imshow('mask', mask)   #show image in a window named "mask"

cv2.imshow('result', result)   #show image in a window named "result"

cv2.waitKey(0)     #waits for a specified time in milliseconds or till a key is pressed, 0=wait indefinitely or till a key is pressed

cv2.destroyAllWindows()   #delete all created window
