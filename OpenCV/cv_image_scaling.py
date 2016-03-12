#import CV libraries
import numpy
import cv2

img=cv2.imread("/home/udayan/Downloads/Lena.png", 0)    #read image, 0=read as grayscale, -1=read as color

#algorithm used for scaling can be changed, refer documentation
#fx & fy are scaling factors for x & y axes respectively
result_upsize=cv2.resize(img, None, fx=2, fy=2)    #scale up image

result_downsize=cv2.resize(img, None, fx=0.5, fy=0.5)    #scale down image

cv2.imshow('image',img)   #show image in a window named "image"

cv2.imshow('result_downsize',result_downsize)   #show image in a window named "result_downsize"

cv2.imshow('result_upsize',result_upsize)   #show image in a window named "result_upsize"

cv2.waitKey(0)     #waits for a specified time in milliseconds or till a key is pressed, 0=wait indefinitely or till a key is pressed

cv2.destroyAllWindows()   #delete all created windows
