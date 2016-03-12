#import CV libraries
import numpy
import cv2

img1=cv2.imread("/home/udayan/Downloads/rectangle.jpg", -1)    #read image, 0=read as grayscale, -1=read as color
img2=numpy.ndarray(img1.shape)
numpy.copyto(img2, img1)
img3=numpy.ndarray(img1.shape)
numpy.copyto(img3, img1)
img4=numpy.ndarray(img1.shape)
numpy.copyto(img4, img1)

img2gray=cv2.cvtColor(img1, cv2.COLOR_BGR2GRAY)    #convert to grayscale

ret, thresh=cv2.threshold(img2gray, 127, 255, cv2.THRESH_BINARY)       #threshold image; contour algorithms work best with binary images

contours, hierarchy=cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)      #find contour point coodrinates using cv2.CHAIN_APPROX_SIMPLE method; this function modifies source image

M=cv2.moments(contours[0])     #calc moment of contour

#calc centroid of contour
cx=int(M['m10']/M['m00'])
cy=int(M['m01']/M['m00'])
print "Centroid Coordinates: ("+str(cx)+", "+str(cy)+")"

#calc area of contour
area=cv2.contourArea(contours[0])
print "Area: "+str(area)

#calc diameter of the circle whose area is same as the contour area (aka equivalent diameter)
equi_diameter=numpy.sqrt(4*area/numpy.pi)
print "Equivalent Diameter: "+str(equi_diameter)

#calc perimeter of contour
perimeter=cv2.arcLength(contours[0], True)
print "Perimeter: "+str(perimeter)

#calc convex hull
hull=cv2.convexHull(contours[0]) 

#calc ratio of contour area to its convex hull area (aka solidity)    
hull_area=cv2.contourArea(hull)
solidity=float(area)/hull_area
print "Solidity: "+str(solidity)

#contour approximation
epsilon=0.1*cv2.arcLength(contours[0], True)      #10% of arc length; it's the max. distance of contour to approximated contour, 2nd argument=specifies if curved is closed or not
approx=cv2.approxPolyDP(contours[0], epsilon, True)         #3rd argument=specifies if curved is closed or not

#draw a bounding rectangle around the contour
x, y, w, h=cv2.boundingRect(contours[0])
cv2.rectangle(img1, (x, y),(x+w, y+h),(0, 0, 255), 3)

#calc aspect ratio of bounding rectangle
aspect_ratio=float(w)/h      
print "Aspect ratio: "+str(aspect_ratio)

#calc ratio of contour area to bounding rectangle area (aka extent)
rect_area=w*h
extent=float(area)/rect_area
print "Extent: "+str(extent)

#calculate distance of a point ((50, 50) here) from the contour (aka Point Polygon Test)
dist=cv2.pointPolygonTest(contours[0], (50, 50), True)      #3rd argument=if it is True, it finds the signed distance; if False, it finds whether the point is inside or outside or on the contour (it returns +1, -1, 0 respectively); using False will speed up execution of the function by 2-3 times
print "Point Polygon Test Result: "+str(dist)

cv2.drawContours(img2, contours, -1, (0, 255, 0), 3)       #draw the contours on the image; 1st argument=image variable, 2nd argument=contour coordinates, 3rd argument=index of which contour to draw (-1=all contours), 4th argument=color of drawn contour line, 5th argument=pixel width of drawn contour line

cv2.drawContours(img3, approx, -1, (0, 255, 0), 3)       #draw the approximated contours on the image; 1st argument=image variable, 2nd argument=contour coordinates, 3rd argument=index of which contour to draw (-1=all contours), 4th argument=color of drawn contour line, 5th argument=pixel width of drawn contour line

cv2.drawContours(img4, hull, -1, (255, 0, 0), 3)       #draw the convex hull on the image; 1st argument=image variable, 2nd argument=contour coordinates, 3rd argument=index of which contour to draw (-1=all contours), 4th argument=color of drawn contour line, 5th argument=pixel width of drawn contour line

cv2.imshow('bounded_rect', img1)   #show image in a window named "bounded_rect"
cv2.imshow('contours', img2)   #show image in a window named "contours"
cv2.imshow('contours_approx', img3)   #show image in a window named "contours_approx"
cv2.imshow('convex_hull', img4)   #show image in a window named "convex_hull"

cv2.waitKey(0)     #waits for a specified time in milliseconds or till a key is pressed, 0=wait indefinitely or till a key is pressed

cv2.destroyAllWindows()   #delete all created windows

