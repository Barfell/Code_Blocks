#import CV libraries
import numpy
import cv2

img=cv2.imread("/home/udayan/Downloads/Lena.png", -1)    #read image, 0=read as grayscale, -1=read as color

cv2.rectangle(img,(128,384),(384,128),(0,0,255),3)   #draw a rectangle on the image, 1st argument=image variable, 2nd & 3rd arguments=coordinates of top-left & bottom right corners of rectangle, 4th argument=color of rectangle edge, 5th argument=pixel width of rectangle edge

cv2.imshow('image',img)   #show image in a window named "image"

cv2.waitKey(0)     #waits for a specified time in milliseconds or till a key is pressed, 0=wait indefinitely or till a key is pressed

cv2.destroyAllWindows()   #delete all created window
