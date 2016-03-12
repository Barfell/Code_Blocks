%Thickening
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
z=bwmorph(y, 'thicken', Inf);         %perform thickening; Inf is used to make the algorithm run until the image stops changing
figure(2)
imshow(z)
title('Thickened Image');