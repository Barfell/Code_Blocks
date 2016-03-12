#import CV libraries
import numpy
import cv2

img=cv2.imread("/home/udayan/Downloads/Lena.png", 0)    #read image, 0=read as grayscale, -1=read as color

#threshold image using various techniques, OpenCV also supports  Otsu's adaptive thresholding
ret,thresh1 = cv2.threshold(img,127,255,cv2.THRESH_BINARY)     #common type 
ret,thresh2 = cv2.threshold(img,127,255,cv2.THRESH_BINARY_INV)    #common type 
ret,thresh3 = cv2.threshold(img,127,255,cv2.THRESH_TRUNC)
ret,thresh4 = cv2.threshold(img,127,255,cv2.THRESH_TOZERO)
ret,thresh5 = cv2.threshold(img,127,255,cv2.THRESH_TOZERO_INV)

cv2.imshow('img',img)   #show image in a window named "img"

cv2.imshow('thresh1',thresh1)   #show image in a window named "thresh1"

cv2.imshow('thresh2',thresh2)   #show image in a window named "thresh2"

cv2.imshow('thresh3',thresh3)   #show image in a window named "thresh3"

cv2.imshow('thresh4',thresh4)   #show image in a window named "thresh4"

cv2.imshow('thresh5',thresh5)   #show image in a window named "thresh5"

cv2.waitKey(0)     #waits for a specified time in milliseconds or till a key is pressed, 0=wait indefinitely or till a key is pressed

cv2.destroyAllWindows()   #delete all created window

