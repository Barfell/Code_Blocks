#import CV libraries
import numpy
import cv2

img=cv2.imread("/home/udayan/Downloads/Lena.png", -1)    #read image, 0=read as grayscale, -1=read as color

img_b, img_g, img_r=cv2.split(img)        #split up the RGB channels

img_rgb=cv2.merge((img_b,img_g,img_r))  #merge RGB channels

cv2.imshow('img_b',img_b)   #show image in a window named "img_b"

cv2.imshow('img_g',img_g)   #show image in a window named "img_g"

cv2.imshow('img_r',img_r)   #show image in a window named "img_r"

cv2.imshow('img_rgb',img_rgb)   #show image in a window named "img_rgb"

cv2.waitKey(0)     #waits for a specified time in milliseconds or till a key is pressed, 0=wait indefinitely or till a key is pressed

cv2.destroyAllWindows()   #delete all created window
