#import CV libraries
import numpy
import cv2

img=cv2.imread("/home/udayan/Downloads/Lena.png", 0)    #read image, 0=read as grayscale, -1=read as color

sub_img1=img[0:200, 0:200]          #define sub-image

sub_img2=img[200:400, 200:400]      #define sub-image

sum=cv2.add(sub_img1, sub_img2)            #add images, doing sub_img1+sub_img2 will cause modulo operation if sum exceeds 255; eg. 255+4=260 will cause pixel value to be set to 4 cause 260%255=4; using cv2.add() here would cause the value to saturate at 255 if it overflows

cv2.imshow('sub_img1',sub_img1)   #show image in a window named "sub_img1"

cv2.imshow('sub_img2',sub_img2)   #show image in a window named "sub_img2"

cv2.imshow('sum',sum)   #show image in a window named "sum"

cv2.waitKey(0)     #waits for a specified time in milliseconds or till a key is pressed, 0=wait indefinitely or till a key is pressed

cv2.destroyAllWindows()   #delete all created window
