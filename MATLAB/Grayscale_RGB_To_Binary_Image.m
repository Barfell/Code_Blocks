%Grayscale_RGB_To_Binary_Image
clear;
clc;
clf;
x=imread('E:\Work Place\Books\Image & Video Processing\lena_rgb.jpg');              %read image to workspace
figure(1)
imshow(x)
title('Original Image');
%convert image to binary
%0.5 is the threshold here
%threshold must be between 0 and 1
y=im2bw(x, 0.5);  
figure(2)
imshow(y)
title('Binary Image');