#import CV libraries
import numpy
import cv2

cap = cv2.VideoCapture(0)    #create a camera object

ret, frame = cap.read()      #capture a frame

cv2.imshow('image', frame)   #show frame in a window named "image"

cv2.waitKey(0)     #waits for a specified time in milliseconds or till a key is pressed, 0=wait indefinitely or till a key is pressed

cap.release()           #release camera

cv2.destroyAllWindows()   #delete all created windows
