%Serial_Communication
clear;                      %delete previous serial objects
clc;
clf;
s=serial('COM4','BaudRate',9600,'DataBits',8);             %create serial object
set(s, 'Timeout', 1);                            %change settings if required; here timeout is in seconds
get(s)                                  %display settings of the serial object
fopen(s);                         %start communication
for i=1:10
    x=fread(s);                  %read from serial
    disp(x)             %show received data
end
fwrite(s, 'C');           %write to serial; here we are sending the character 'C'
fclose(s);                     %stop communication & free up the COM port; necessary as MATLAB assumes complete command of COM port after fopen()
clear;                         %delete serial object, this prevents any errors when using serial communication on MATLAB again