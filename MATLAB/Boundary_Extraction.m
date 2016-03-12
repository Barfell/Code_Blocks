%Boundary_Extraction
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
z=strel('square', 3);           %creates a square structuring element with width of 3 pixels; a simple matrix can be made and used too
a=imerode(y, z);                %erosion operation
figure(2)
imshow(a)
title('Eroded Image');
b=y-a;                          %extract boundaries
figure(3)
imshow(b)
title('Image Boundaries');
b=uint8(b);