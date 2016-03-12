#import CV libraries
import numpy
import cv2

img=cv2.imread("/home/udayan/Downloads/Lena.png", 0)    #read image, 0=read as grayscale, -1=read as color

#OpenCV also supports  Otsu's adaptive thresholding
ret,thresh1=cv2.threshold(img,127,255,cv2.THRESH_BINARY)    #global thresholding
thresh2=cv2.adaptiveThreshold(img, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY, 11, 2)    #threshold value is the mean of neighbourhood area
thresh3=th3 = cv2.adaptiveThreshold(img, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY, 11, 2)   #threshold value is the weighted sum of neighbourhood values where weights are a gaussian window

cv2.imshow('img',img)   #show image in a window named "img"

cv2.imshow('thresh1',thresh1)   #show image in a window named "thresh1"

cv2.imshow('thresh2',thresh2)   #show image in a window named "thresh2"

cv2.imshow('thresh3',thresh3)   #show image in a window named "thresh3"

cv2.waitKey(0)     #waits for a specified time in milliseconds or till a key is pressed, 0=wait indefinitely or till a key is pressed

cv2.destroyAllWindows()   #delete all created window

