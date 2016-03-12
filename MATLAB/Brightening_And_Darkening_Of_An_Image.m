%Brightening_And_Darkening_Of_An_Image
clear;
clf;
clc;
x=imread('E:\Work Place\Books\Image & Video Processing\lena_rgb.jpg');          %read image to workspace
y=rgb2gray(x);               %convert RGB image to grayscale
figure(1)
subplot(2, 1, 1)
imshow(y)
title('Original Image');
subplot(2, 1, 2)
imhist(y)
title('Histogram');
z1=y-100;                    %darkening of image
figure(2)
subplot(2, 1, 1)
imshow(z1)
title('Darkened Image');
subplot(2, 1, 2)
imhist(z1)
title('Histogram');
z2=y+100;                    %brightening of image
figure(3)
subplot(2, 1, 1)
imshow(z2)
title('Brightened Image');
subplot(2, 1, 2)
imhist(z2)
title('Histogram');