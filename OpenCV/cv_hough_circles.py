#import CV libraries
import numpy
import cv2

img=cv2.imread("/home/udayan/Downloads/opencv.png", 0)    #read image, 0=read as grayscale, -1=read as color
img=cv2.resize(img, None, fx=0.5, fy=0.5)    #scale down image

img2rgb=cv2.cvtColor(img, cv2.COLOR_GRAY2BGR)      #convert to color; it will look the same as the grayscale one visually but it will have separate color channels

circles=cv2.HoughCircles(img, cv2.cv.CV_HOUGH_GRADIENT, 1, 50, param1=50, param2=30, minRadius=50, maxRadius=0)   #calc hough transform for circles
#1st argument=8-bit grayscale image
#2nd argument=method used for transform (only cv2.cv.CV_HOUGH_GRADIENT supported)
#3rd argument=inverse ratio of the accumulator resolution to the image resolution; for example, if dp=1 , the accumulator has the same resolution as the input image; if dp=2 , the accumulator has half as big width and height
#4th argument=min. distance between the centers of the detected circles (if the parameter is too small, multiple neighbor circles may be falsely detected in addition to a true one, if it is too large, some circles may be missed)
#5th argument=for CV_HOUGH_GRADIENT , it is the higher threshold of the two passed to the Canny() edge detector
#6th argument=for CV_HOUGH_GRADIENT , it is the accumulator threshold for the circle centers at the detection stage; the smaller it is, the more false circles may be detected; circles, corresponding to the larger accumulator values, will be returned first
#7th argument=min. circle radius
#8th argument=max. circle radius

#draw the circles
circles=numpy.uint16(numpy.around(circles))
for i in circles[0, :]:
    cv2.circle(img2rgb, (i[0], i[1]), i[2], (0, 255, 0), 2)      #draw the outer circle; 1st argument=input image, 2nd argument=coordinates of center of the circle, 3rd argument=radius of circle, 4th & 5th arguments=line color and thickness respectively
    cv2.circle(img2rgb, (i[0], i[1]), 2, (0, 0, 255), 3)         #draw the center of the circle; 1st argument=input image, 2nd argument=coordinates of center of the circle, 3rd argument=radius of circle, 4th & 5th arguments=line color and thickness respectively
 
cv2.imshow('hough_circles', img2rgb)   #show image in a window named "hough_circles"

cv2.waitKey(0)     #waits for a specified time in milliseconds or till a key is pressed, 0=wait indefinitely or till a key is pressed

cv2.destroyAllWindows()   #delete all created windows
