%Closing
clear;
clc;
clf;
x=imread('E:\Work Place\Books\Image & Video Processing\lena_rgb.jpg');              %read image to workspace
%convert image to binary
%0.5 is the threshold here
%threshold must be between 0 and 1
y=im2bw(x, 0.5);  
figure(1)
imshow(y)
title('Original Image');
z=strel('diamond', 2);           %creates a diamond structuring element with a distance of 2 pixels from it's origin to it's extreme points; a simple matrix can be made and used too
a=imclose(y, z);                %closing operation
figure(2)
imshow(a)
title('Closed Image');