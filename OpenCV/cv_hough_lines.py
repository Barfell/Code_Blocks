#import CV libraries
import numpy
import cv2

img1=cv2.imread("/home/udayan/Downloads/sudoku.png", -1)    #read image, 0=read as grayscale, -1=read as color
img2=numpy.ndarray(img1.shape)
numpy.copyto(img2, img1)

img2gray=cv2.cvtColor(img1, cv2.COLOR_BGR2GRAY)    #convert to grayscale

edges=cv2.Canny(img1, 50, 200)             #Canny edge detection; Hough line transform APIs only take binary images

########################general Hough Transform########################
lines1=cv2.HoughLines(edges, 1, numpy.pi/180, 200)         #calc Hough transform for lines; 1st argument=input image, 2nd & 3rd arguments: rho & theta accuracies respectively, 4th argument=threshold i.e. which means minimum vote it should get for it to be considered as a line

for rho, theta in lines1[0]:
	a=numpy.cos(theta)
	b=numpy.sin(theta)
	x=a*rho
	y=b*rho
	x1=int(x+1000*(-b))
	y1=int(y+1000*(a))
	x2=int(x-1000*(-b))
	y2=int(y-1000*(a))

	cv2.line(img1, (x1, y1), (x2, y2), (0, 0, 255), 2)          #draw detected lines; 1st argument=input image, 2nd & 3rd arguments=the end points of the line segment, 4th & 5th arguments=line color and thickness respectively
#######################################################################

#####################probabilistic Hough Transform#####################
minLineLength=100
maxLineGap=5

lines2=cv2.HoughLinesP(edges, 1, numpy.pi/180, 100, minLineLength, maxLineGap)           #calc Hough transform; 1st argument=input image, 2nd & 3rd arguments: rho & theta accuracies respectively, 4th argument=threshold i.e. which means minimum vote it should get for it to be considered as a line (it's usually less here compared to the general Hough line transform), 5th argument=line segments shorter than this are rejected, 6th argument=max. allowed gap between line segments to treat them as single line

for x1, y1, x2, y2 in lines2[0]:
    cv2.line(img2, (x1, y1), (x2, y2), (0, 255, 0), 2)              #draw detected lines; 1st argument=input image, 2nd & 3rd arguments=the end points of the line segment, 4th & 5th arguments=line color and thickness respectively
#######################################################################

cv2.imshow('hough_lines', img1)   #show image in a window named "hough_lines"

cv2.imshow('hough_lines_probabilistic', img2)   #show image in a window named "hough_lines"

cv2.waitKey(0)     #waits for a specified time in milliseconds or till a key is pressed, 0=wait indefinitely or till a key is pressed

cv2.destroyAllWindows()   #delete all created windows
