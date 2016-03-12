%Negative_Of_Image
clear;
clf;
clc;
%read image
x=imread('E:\Work Place\Books\Image & Video Processing\lena_rgb.jpg');          %read image to workspace
y=rgb2gray(x);                        %convert RGB image to grayscale
figure(1)
imshow(y)
title('Original Image');
h=255-y;                    %get negative
h=uint8(h);
figure(2)
imshow(h)
title('Negative Image');