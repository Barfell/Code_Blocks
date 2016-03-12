%Power_Law_Transform_Of_Image
clear;
clf;
clc;
%read image
a=imread('E:\Work Place\Books\Image & Video Processing\lena_rgb.jpg');          %read image to workspace       
b=rgb2gray(a);                 %convert RGB image to grayscale
figure(1)
imshow(b)
title('Original Image');
b=double(b);
%get nth power transform
c=1;
gamma=0.67;
h=c.*(b.^gamma);
h=uint8(h);
figure(2)
imshow(h)
title('nth power transform');
%get nth root transform
gamma=1.5;
h=c.*(b.^gamma);
h=uint8(h);
figure(3)
imshow(h)
title('nth root transform');