#import CV libraries
import numpy
import cv2

img=cv2.imread("/home/udayan/Downloads/Lena.png", 0)    #read image, 0=read as grayscale, -1=read as color

#kernels, in-built APIs are available for blurring and sharpening too (more preferable)
kernel_avg=numpy.ones((3,3),numpy.float32)/9   #3x3 averaging kernel
kernel_1_der=numpy.array([[0, -1, 0], [-1, 4, -1], [0, -1, 0]])    #3x3 derivative kernel
kernel_2_der=numpy.array([[-1, -1, -1], [-1, 8, -1], [-1, -1, -1]])    #3x3 derivative kernel

#2D convolution
result1=cv2.filter2D(img, -1, kernel_avg)
result2=cv2.filter2D(img, -1, kernel_1_der)
result3=cv2.filter2D(img, -1, kernel_2_der)

cv2.imshow('img',img)   #show image in a window named "img"

cv2.imshow('result1',result1)   #show image in a window named "result1"

cv2.imshow('result2',result3)   #show image in a window named "result2"

cv2.imshow('result3',result3)   #show image in a window named "result2"

cv2.waitKey(0)     #waits for a specified time in milliseconds or till a key is pressed, 0=wait indefinitely or till a key is pressed

cv2.destroyAllWindows()   #delete all created window

