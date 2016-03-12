function [ y ] = circshift1( x, M )
%circshift1 Summary of this function goes here
%   Detailed explanation goes here
if(abs(M)) > length(x)
    M=rem(M, length(x));
end
if M < 0
    M=M+length(x);
end
y=[x(M+1:length(x)) x(1:M)]
end

