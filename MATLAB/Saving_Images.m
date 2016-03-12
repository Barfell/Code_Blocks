%Saving_Images
clear;
clf;
clc;
x=imread('E:\Work Place\Books\Image & Video Processing\lena_rgb.jpg');          %read image to workspace
figure(1)
imshow(x)
title('Original Image');
y=rgb2gray(x);               %convert RGB image to grayscale
figure(2)
imshow(y)
title('Saved Image');
%save image
%2 is the figure window number
saveas(2,'filename.jpg')