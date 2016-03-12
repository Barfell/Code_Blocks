%Otsu_Thresholding
clear;
clf;
clc;
x=imread('E:\Work Place\Books\Image & Video Processing\lena_rgb.jpg');          %read image to workspace
y=rgb2gray(x);               %convert RGB image to grayscale
figure(1)
imshow(y)
[T, SM]=graythresh(y)           %get normalized threshold and separability measure
z=im2bw(y, T);                  %perform thresholding
figure(2)
imshow(z)