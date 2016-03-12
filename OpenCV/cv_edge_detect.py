#import CV libraries
import numpy
import cv2

img=cv2.imread("/home/udayan/Downloads/Lena.png", 0)    #read image, 0=read as grayscale, -1=read as color

edges=cv2.Canny(img, 50, 200)             #Canny edge detection

cv2.imshow('img', img)   #show image in a window named "img"

cv2.imshow('edges', edges)   #show image in a window named "edges"

cv2.waitKey(0)     #waits for a specified time in milliseconds or till a key is pressed, 0=wait indefinitely or till a key is pressed

cv2.destroyAllWindows()   #delete all created window

