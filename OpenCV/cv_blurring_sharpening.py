#import CV libraries
import numpy
import cv2

img=cv2.imread("/home/udayan/Downloads/Lena.png", 0)    #read image, 0=read as grayscale, -1=read as color

#blurring
blur1=cv2.blur(img, (5, 5))    #averaging using a 5x5 kernel
blur2=cv2.GaussianBlur(img, (5, 5), 0)     #Gaussian blurring using 5x5 kernel; effective against Gaussian noise

#sharpening
laplacian=cv2.Laplacian(img, cv2.CV_32F)     #using a laplacian filter
sobel=cv2.Sobel(img, cv2.CV_32F, 1, 1, ksize=5)     #using a 5x5 sobel filter, x & y derivatives are of the 1st order here

cv2.imshow('img', img)   #show image in a window named "img"

cv2.imshow('laplacian', laplacian)   #show image in a window named "laplacian"

cv2.imshow('sobel', sobel)   #show image in a window named "sobel"

cv2.imshow('blur1', blur1)   #show image in a window named "blur1"

cv2.imshow('blur2', blur2)   #show image in a window named "blur2"

cv2.waitKey(0)     #waits for a specified time in milliseconds or till a key is pressed, 0=wait indefinitely or till a key is pressed

cv2.destroyAllWindows()   #delete all created window

