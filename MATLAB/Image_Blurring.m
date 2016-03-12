%Image_Blurring
clear;
clf;
clc;
x=imread('E:\Work Place\Books\Image & Video Processing\lena_rgb.jpg');          %read image to workspace
y=rgb2gray(x);               %convert RGB image to grayscale
figure(1)
imshow(y)
title('Original Image');
z=1/9*ones(3);               %averaging filter
a=imfilter(y, z);            %perform 2D convolution
a=uint8(a);
figure(2)
imshow(a)
title('Blurred Image');