%Image_Acquisition
clear;
clf;
clc;
%initialize camera
vid = videoinput('winvideo', 1, 'RGB24_320x240');
src = getselectedsource(vid);
x=1;
while x>0
    imshow(getsnapshot(vid))          %capture a frame
end