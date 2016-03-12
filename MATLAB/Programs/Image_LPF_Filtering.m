%Image_LPF_Filtering
clear;
clf;
clc;
x=imread('E:\Work Place\Books\Image & Video Processing\lena_rgb.jpg');          %read image to workspace
y=rgb2gray(x);               %convert RGB image to grayscale
figure(1)
imshow(y)
title('Original Image');
z=imnoise(y, 'gaussian');               %add gaussian noise
figure(2)
imshow(z)
title('Corrupted Image');
a=1/9*ones(3);               %averaging filter
b=imfilter(z, a);            %perform 2D convolution
b=uint8(b);
figure(3)
imshow(b)
title('Filtered Image');