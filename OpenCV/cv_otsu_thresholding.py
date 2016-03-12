#import CV libraries
import numpy
import cv2

img=cv2.imread("/home/udayan/Downloads/Lena.png", 0)    #read image, 0=read as grayscale, -1=read as color

ret1,thresh1=cv2.threshold(img, 127, 255, cv2.THRESH_BINARY)     #global thresholding
ret2,thresh2=cv2.threshold(img, 0, 255, cv2.THRESH_BINARY+cv2.THRESH_OTSU)      #global thresholding using Otsu's Binarization

cv2.imshow('img',img)   #show image in a window named "img"

cv2.imshow('thresh1',thresh1)   #show image in a window named "thresh1"

cv2.imshow('thresh2',thresh2)   #show image in a window named "thresh2"

cv2.waitKey(0)     #waits for a specified time in milliseconds or till a key is pressed, 0=wait indefinitely or till a key is pressed

cv2.destroyAllWindows()   #delete all created window

