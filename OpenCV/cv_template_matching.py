#import CV libraries
import numpy
import cv2

img=cv2.imread("/home/udayan/Downloads/messi.jpg", 0)    #read image, 0=read as grayscale, -1=read as color
template=cv2.imread("/home/udayan/Downloads/messi_face.jpg", 0)    #read image, 0=read as grayscale, -1=read as color

h, w=template.shape

result=cv2.matchTemplate(img, template, cv2.TM_CCOEFF_NORMED)     #template matching, can also use cv2.TM_CCOEFF, cv2.TM_CCORR, 'cv2.TM_CCORR_NORMED', cv2.TM_SQDIFF, cv2.TM_SQDIFF_NORMED

min_val, max_val, min_loc, max_loc = cv2.minMaxLoc(result)        #get coordinates and intensity values of pixels with max. & min. intensities in the result, max. value indicates best match here; min. value indicates best match for cv2.TM_SQDIFF & cv2.TM_SQDIFF_NORMED

#mark recognized area
top_left=max_loc
bottom_right=(top_left[0]+w, top_left[1]+h)
cv2.rectangle(img, top_left, bottom_right, 255, 3)   #draw a rectangle on the image, 1st argument=image variable, 2nd & 3rd arguments=coordinates of top-left & bottom right corners of rectangle, 4th argument=color (intensity here) of rectangle edge, 5th argument=pixel width of rectangle edge

cv2.imshow('image',img)   #show image in a window named "image"

cv2.imshow('result',result)   #show image in a window named "result"

cv2.waitKey(0)     #waits for a specified time in milliseconds or till a key is pressed, 0=wait indefinitely or till a key is pressed

cv2.destroyAllWindows()   #delete all created windows
