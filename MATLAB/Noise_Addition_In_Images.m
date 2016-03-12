%Noise_Addition_In_Images
clear;
clf;
clc;
x=imread('E:\Work Place\Books\Image & Video Processing\lena_rgb.jpg');          %read image to workspace
y=rgb2gray(x);               %convert RGB image to grayscale
figure(1)
imshow(y)
title('Original Image');
%salt and pepper
z=imnoise(y, 'salt & pepper');               %add salt and pepper noise
figure(2)
imshow(z)
title('Corrupted Image-Salt & Pepper Noise');
%gaussian
z=imnoise(y, 'gaussian');               %add gaussian noise
figure(3)
imshow(z)
title('Corrupted Image-Gaussian Noise');