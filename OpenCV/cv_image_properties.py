#import CV libraries
import numpy
import cv2

img=cv2.imread("/home/udayan/Downloads/Lena.png", 0)    #read image, 0=read as grayscale, -1=read as color

print "Shape of Image: " + str(img.shape)          #shape of image

print "No. of pixels in the Image: " + str(img.size)          #size of image

print "Datatype of Image Variable: " + str(img.dtype)          #datatype of image variable


