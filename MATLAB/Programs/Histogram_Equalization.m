%Histogram_Equalization
clear;
clf;
clc;
x=imread('E:\Work Place\Books\Image & Video Processing\lena_rgb.jpg');          %read image to workspace
y=rgb2gray(x);               %convert RGB image to grayscale
figure(1)
imshow(y)
title('Original Image');
figure(2)
histeq(y)             %perform histogram equalization
title('Histogram Equalized Image');