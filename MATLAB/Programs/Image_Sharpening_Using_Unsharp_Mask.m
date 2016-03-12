%Image_Sharpening_Using_Unsharp_Mask
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
b=y-a;                   %unsharp mask
figure(2)
imshow(b)
title('Unsharp Mask');
c=y+b;       %sharpening
figure(3)
imshow(c)
title('Sharpened Image');