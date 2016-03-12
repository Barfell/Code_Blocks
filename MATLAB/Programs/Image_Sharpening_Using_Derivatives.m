%Image_Sharpening_Using_Derivatives
clear;
clf;
clc;
x=imread('E:\Work Place\Books\Image & Video Processing\lena_rgb.jpg');          %read image to workspace
y=rgb2gray(x);               %convert RGB image to grayscale
figure(1)
imshow(y)
title('Original Image');
%1st filter
z1=[0 -1 0;-1 4 -1; 0 -1 0];               %2nd derivative filter
a=imfilter(y, z1);            %perform 2D convolution
a=uint8(a);
figure(2)
subplot(2, 1, 1)
imshow(a)
title('1st Filter');
c=y+a;                     %sharpening
subplot(2, 1, 2)
imshow(c)
title('Sharpened Image-1st Filter');
%2nd filter
z2=[-1 -1 -1;-1 8 -1; -1 -1 -1];               %2nd derivative filter
b=imfilter(y, z2);            %perform 2D convolution
b=uint8(b);
figure(3)
subplot(2, 1, 1)
imshow(b)
title('2nd Filter');
d=y+b;                     %sharpening
subplot(2, 1, 2)
imshow(d)
title('Sharpened Image-2nd Filter');