%Addition_Of_2_Images
clear;
clf;
clc;
%1st image
figure(1)
x=imread('E:\Work Place\Books\Image & Video Processing\lena_rgb.jpg');          %read image to workspace
imshow(x)
title('Original Image-1');
%2nd image
figure(2)
y=imread('E:\Work Place\Books\Image & Video Processing\brain.jpg');          %read image to workspace
imshow(y)
title('Original Image-2');
%Addition
a=x+y;                                %add the 2 images
figure(3)
imshow(a)
title('Sum');
%Subtraction
b=x-y;                                %subtract the 2 images
figure(4)
imshow(b)
title('Difference');