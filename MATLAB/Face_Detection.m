%Face_Detection
clear;
clf;
clc;
%initialize camera
vid = videoinput('winvideo', 1, 'MJPG_320x240');
src = getselectedsource(vid);
x=1;
%detect face using Viola-Jones algorithm
while x==1
    frame=getsnapshot(vid);            %capture a frame
    faceDetector=vision.CascadeObjectDetector();           %detect face
    box=step(faceDetector, frame);       %
    % Draw the returned bounding box around the detected face.
    videoOut=insertObjectAnnotation(frame,'rectangle',box,'Face');
    imshow(videoOut)
end
