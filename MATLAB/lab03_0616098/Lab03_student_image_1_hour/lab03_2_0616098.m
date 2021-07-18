%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Assignment Number: Lab3
% Problem number: 2
% Student Name: ¶ÀªÃ­Z
% Student ID: 0616098   
% Email address: maomao.08190@gmail.com
% Department: Computer Science, NCTU
% Date: 5/6
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% close all windows
% clear variables, and clear screen
close all; clf; clear; clc;

% show Lab Problem 3.2
disp('Lab Problem 3.2')  
I = imread('tmp.png');

Id = im2double(I);

s = size(Id);
h = s(1);
w = s(2);

while(1)
    K = ones(size(I), 'double');
    s = size(K); 
    i = 1;
    op = input('Please input the option code : ');
    switch op
        case 0
            break;
        case 1
            dir = w;
            while i < dir
                K(:,i,1:3) = abs(cos(i / dir * 2 * pi)); i = i + 1;
            end
        case 2
            dir = h;
            while i < dir
                K(i,:,1:3) = abs(cos(i / dir * 2 * pi)); i = i + 1;
            end
    end
    imshow(Id.*K);
end
