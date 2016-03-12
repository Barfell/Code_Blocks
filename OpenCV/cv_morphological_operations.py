#import CV libraries
import numpy
import cv2

img=cv2.imread("/home/udayan/Downloads/J.png", 0)    #read image, 0=read as grayscale, -1=read as color

ret,thresh=cv2.threshold(img, 127, 255, cv2.THRESH_BINARY)     #threshold image

kernel=cv2.getStructuringElement(cv2.MORPH_RECT, (5,5))    #get 5x5 structuring element, can use MORPH_ELLIPSE or MORPH_CROSS as well for a different structuring element, here kernel will be=[[1, 1, 1, 1, 1], [1, 1, 1, 1, 1], [1, 1, 1, 1, 1], [1, 1, 1, 1, 1], [1, 1, 1, 1, 1]]

dilation=cv2.dilate(thresh, kernel, iterations=1)      #dilation operation

erosion=cv2.erode(thresh, kernel, iterations=1)	      #erosion operation

opening=cv2.morphologyEx(thresh, cv2.MORPH_OPEN, kernel)      #opening operation, useful in removing noise in the background(black regions)

closing=cv2.morphologyEx(thresh, cv2.MORPH_CLOSE, kernel)     #closing operation, useful in removing noise in the foreground(white regions)

gradient=cv2.morphologyEx(thresh, cv2.MORPH_GRADIENT, kernel)     #calc morphological gradient=difference between dilation and erosion of image

tophat=cv2.morphologyEx(thresh, cv2.MORPH_TOPHAT, kernel)    #calc top hat=difference between input image and opening of image

blackhat=cv2.morphologyEx(thresh, cv2.MORPH_BLACKHAT, kernel)     #calc black hat=difference between input image and closing of image

cv2.imshow('thresh', thresh)   #show image in a window named "thresh"

cv2.imshow('dilation', dilation)   #show image in a window named "dilation"

cv2.imshow('erosion', erosion)   #show image in a window named "erosion"

cv2.imshow('opening', opening)   #show image in a window named "opening"

cv2.imshow('closing', closing)   #show image in a window named "closing"

cv2.imshow('gradient', gradient)   #show image in a window named "gradient"

cv2.imshow('tophat', tophat)   #show image in a window named "tophat"

cv2.imshow('blackhat', blackhat)   #show image in a window named "blackhat"

cv2.waitKey(0)     #waits for a specified time in milliseconds or till a key is pressed, 0=wait indefinitely or till a key is pressed

cv2.destroyAllWindows()   #delete all created window

