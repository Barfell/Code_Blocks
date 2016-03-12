#import CV libraries
import numpy
import cv2

img=cv2.imread("/home/udayan/Downloads/Lena.png", 0)    #read image, 0=read as grayscale, -1=read as color

print "Pixel Value: " + str(img[100, 100])     #print intensity value at of pixel at coordinate (100, 100)

img[100, 100]=0           #manipulate pixel value

print "New Pixel Value: " + str(img[100, 100])     #print intensity value at of pixel at coordinate (100, 100)

roi=img[273:333, 100:160]          #define region of importance, just a slicing operation

cv2.imshow('roi',roi)   #show image in a window named "roi"

cv2.waitKey(0)     #waits for a specified time in milliseconds or till a key is pressed, 0=wait indefinitely or till a key is pressed

cv2.destroyAllWindows()   #delete all created window
