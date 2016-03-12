#import CV libraries
import numpy
import cv2

img=cv2.imread("/home/udayan/Downloads/Lena.png", -1)    #read image, 0=read as grayscale, -1=read as color

img2gray=cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)    #convert to grayscale

img2rgb=cv2.cvtColor(img2gray, cv2.COLOR_GRAY2BGR)   #convert to color; it will look the same as the grayscale one visually but it will have separate color channels

print "Grayscale Image Dimensions: "+str(img2gray.shape)      #shape of image
print "RGB Image Dimensions: "+str(img2rgb.shape)	      #shape of image


cv2.imshow('original',img)   #show image in a window named "original"

cv2.imshow('img2gray',img2gray)   #show image in a window named "img2gray"

cv2.imshow('img2rgb',img2rgb)   #show image in a window named "img2rgb"

cv2.waitKey(0)     #waits for a specified time in milliseconds or till a key is pressed, 0=wait indefinitely or till a key is pressed

cv2.destroyAllWindows()   #delete all created window
