%DFT_Of_Image
clear;
clf;
clc;
x=imread('E:\Work Place\Books\Image & Video Processing\lena_rgb.jpg');          %read image to workspace
y=rgb2gray(x);               %convert RGB image to grayscale
figure(1)
imshow(y)
title('Image');
z=fft2(y);            %get 2D-DFT
z=fftshift(z);        %shift 2D-DFT by pi radians
z=abs(z);             %get the magnitude
z=log(z+1);           %use log() for perceptual scaling and +1 since log(0) is undefined
z=mat2gray(z);        %convert matrix into grayscale image
figure(2)
imshow(z,[]);       %display the result
title('2D-DFT');