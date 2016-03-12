#import CV libraries
import numpy
import cv2

#read images, 0=read as grayscale, -1=read as color
img1=cv2.imread("/home/udayan/Downloads/rectangle.jpg", -1)    
img2=cv2.imread("/home/udayan/Downloads/square.jpg", -1)   
img3=cv2.imread("/home/udayan/Downloads/circle.jpg", -1)

#convert to grayscale
img1_2gray=cv2.cvtColor(img1, cv2.COLOR_BGR2GRAY)    
img2_2gray=cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)  
img3_2gray=cv2.cvtColor(img3, cv2.COLOR_BGR2GRAY) 

#threshold images; contour algorithms work best with binary images
ret, thresh1=cv2.threshold(img1_2gray, 127, 255, cv2.THRESH_BINARY)       
thresh2=thresh1
ret, thresh3=cv2.threshold(img2_2gray, 127, 255, cv2.THRESH_BINARY_INV)     
ret, thresh4=cv2.threshold(img3_2gray, 127, 255, cv2.THRESH_BINARY)   

#find contour point coodrinates using cv2.CHAIN_APPROX_SIMPLE method; this function modifies source images
contours1, hierarchy=cv2.findContours(thresh1, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
contours2, hierarchy=cv2.findContours(thresh2, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)  
contours3, hierarchy=cv2.findContours(thresh3, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)  
contours4, hierarchy=cv2.findContours(thresh4, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)        

#perform contour matching (lower results=better match)
result1=cv2.matchShapes(contours1[0], contours2[0], 1, 0.0)   #rectangle-rectangle
print "Result (Rectangle-Rectangle): "+str(result1)

result2=cv2.matchShapes(contours1[0], contours3[0], 1, 0.0)   #rectangle-square
print "Result (Rectangle-Square): "+str(result2)

result3=cv2.matchShapes(contours1[0], contours4[0], 1, 0.0)   #rectangle-circle
print "Result (Rectangle-Circle): "+str(result3)

#show images
cv2.imshow('rectangle', img1)
cv2.imshow('square', img2)
cv2.imshow('circle', img3)

cv2.waitKey(0)     #waits for a specified time in milliseconds or till a key is pressed, 0=wait indefinitely or till a key is pressed

cv2.destroyAllWindows()   #delete all created windows

