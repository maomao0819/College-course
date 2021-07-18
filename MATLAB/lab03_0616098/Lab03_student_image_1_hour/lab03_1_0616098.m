%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Assignment Number: Lab3
% Problem number: 1
% Student Name: 黃秉茂
% Student ID: 0616098   
% Email address: maomao.08190@gmail.com
% Department: Computer Science, NCTU
% Date: 5/6
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% close all windows
% clear variables, and clear screen
close all; clf; clear; clc;

% show Lab Problem 3.1
disp('Lab Problem 3.1')  
while(1)
    op = input('Please input the option code : ');
    switch op
        case 0
            disp('Thanks for playing.');
            break;
        case 1
            num = 2;
        case 2
            num = 4;
        case 3
            num = 8;  
    end

    I = imread('tmp.png');

    Id = im2double(I);

    s = size(Id);
    w = s(2);
    h = s(1);
    thickness = 5;

    %上
    Id(1:thickness, :, 1) = 0;
    Id(1:thickness, :, 2) = 0;
    Id(1:thickness, :, 3) = 1;
    %下
    Id((h - thickness):h, :, 1) = 0;
    Id((h - thickness):h, :, 2) = 0;
    Id((h - thickness):h, :, 3) = 1;
    %左
    Id(:, 1:thickness, 1) = 0;
    Id(:, 1:thickness, 2) = 0;
    Id(:, 1:thickness, 3) = 1;
    %右
    Id(:, (w - thickness):w, 1) = 0;
    Id(:, (w - thickness):w, 2) = 0;
    Id(:, (w - thickness):w, 3) = 1;
    %直線
    for i = w / 8 : w / 8 : w - w / 8
        Id(:, 1 + i:thickness + i, 1) = 0;
        Id(:, 1 + i:thickness + i, 2) = 0;
        Id(:, 1 + i:thickness + i, 3) = 1;
    end
    %橫線
    for i = h / num : h / num : h - h / num
        Id(1 + i:thickness + i, :, 1) = 0;
        Id(1 + i:thickness + i, :, 2) = 0;
        Id(1 + i:thickness + i, :, 3) = 1;
    end
    imshow(Id);
end
