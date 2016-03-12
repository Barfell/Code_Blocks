#import CV libraries
import numpy
import cv2

img=cv2.imread("/home/udayan/Downloads/rectangle.jpg", -1)    #read image, 0=read as grayscale, -1=read as color

img2gray=cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)    #convert to grayscale

ret, thresh=cv2.threshold(img2gray, 127, 255, cv2.THRESH_BINARY)       #threshold image; contour algorithms work best with binary images

contours, hierarchy=cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)      #find contour point coodrinates using cv2.CHAIN_APPROX_SIMPLE method; this function modifies source image

cv2.drawContours(img, contours, -1, (0, 255, 0), 3)       #draw the contours on the image; 1st argument=image variable, 2nd argument=contour coordinates, 3rd argument=index of which contour to draw (-1=all contours), 4th argument=color of drawn contour line, 5th argument=pixel width of drawn contour line

cv2.imshow('image', img)   #show image in a window named "image"

cv2.waitKey(0)     #waits for a specified time in milliseconds or till a key is pressed, 0=wait indefinitely or till a key is pressed

cv2.destroyAllWindows()   #delete all created windows

