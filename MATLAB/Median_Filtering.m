%Median_Filtering
clear;
clf;
clc;
x=imread('E:\Work Place\Books\Image & Video Processing\lena_rgb.jpg');          %read image to workspace
y=rgb2gray(x);               %convert RGB image to grayscale
figure(1)
imshow(y)
title('Original Image');
z=imnoise(y, 'salt & pepper');               %add salt and pepper noise
figure(2)
imshow(z)
title('Corrupted Image');
a=medfilt2(z);           %performing median filtering using a 3x3 neighbourhood         
a=uint8(a);
figure(3)
imshow(a)
title('Filtered Image');