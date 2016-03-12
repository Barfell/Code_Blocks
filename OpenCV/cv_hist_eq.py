#import CV libraries
import numpy
import cv2

img=cv2.imread("/home/udayan/Downloads/Lena.png", 0)    #read image, 0=read as grayscale, -1=read as color

equ1=cv2.equalizeHist(img)        #global histogram equalization

#adaptive histogram equalization
clahe=cv2.createCLAHE(clipLimit=2.0, tileGridSize=(8,8))     #create adaptive histogram equalization object, contrast limit=2, block size=8x8
equ2=clahe.apply(img)

cv2.imshow('img', img)   #show image in a window named "img"

cv2.imshow('equ1', equ1)   #show image in a window named "equ1"

cv2.imshow('equ2', equ2)   #show image in a window named "equ2"

cv2.waitKey(0)     #waits for a specified time in milliseconds or till a key is pressed, 0=wait indefinitely or till a key is pressed

cv2.destroyAllWindows()   #delete all created window

