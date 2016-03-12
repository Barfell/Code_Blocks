%Hit_And_Miss_Transformation
clear;
clc;
clf;
x=imread('E:\Work Place\Books\Image & Video Processing\lena_rgb.jpg');              %read image to workspace
%convert image to binary
%0.5 is the threshold here
%threshold must be between 0 and 1
y=im2bw(x, 0.5);  
figure(1)
imshow(y)
title('Original Image');
z1=[0 1 0; 1 1 1; 0 1 0];            %foreground structuring element
z2=~z1;                              %background structuring element
a=bwhitmiss(y, z1, z2);                %hit and miss transformation
figure(2)
imshow(a)
title('Hit & Miss Transform');