%Up_Sampling_Down_Sampling
clear;
clf;
clc;
a=imread('E:\Work Place\Books\Image & Video Processing\lena_rgb.jpg');          %read image to workspace
x=rgb2gray(a);               %convert RGB image to grayscale
figure(1)
imshow(x)
title('Original Image');
x=double(x);
%down-sampling
[r c]=size(x);
d=x(1:2:r, 1:2:c);
y=(1/9)*ones(3);           %averaging filter
h=imfilter(d, y);
h=uint8(h);
figure(2)
imshow(h)
title('Down-Sampled Image');
%up-sampling
z=zeros(256);
z(1:2:r, 1:2:c)=d;
g=[0.25 0.5 0.25; 0.5 1 0.5; 0.25 0.5 0.25];                  %LPF
t=imfilter(z, g);
t=uint8(t);
figure(3)
imshow(t)
title('Up-Sampled Image');