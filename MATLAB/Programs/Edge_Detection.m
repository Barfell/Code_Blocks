%Edge_Detection
clear;
clf;
clc;
x=imread('E:\Work Place\Books\Image & Video Processing\lena_rgb.jpg');          %read image to workspace
y=rgb2gray(x);               %convert RGB image to grayscale
figure(1)
imshow(y)
title('Original Image');
figure(2)
edge(y, 'canny')             %perform canny edge detection
title('Canny Edge Detection');
figure(3)
edge(y, 'sobel')             %perform sobel edge detection
title('Sobel Edge Detection');