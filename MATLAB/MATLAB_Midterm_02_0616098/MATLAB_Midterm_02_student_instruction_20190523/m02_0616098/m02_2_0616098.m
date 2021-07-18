%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Midterm Number: Two
% Problem number: 2
% Student Name: ¶ÀªÃ­Z
% Student ID: 0616098
% Email address: maomao.08190@gmail.com
% Department: CS
% Date: 5/23
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% close all windows
% clear variables, and clear screen
close all; clf; clear; clc;

% show Midterm Two Problem 2
disp('Midterm Two Problem 2')

I = imread('tmp.png');
I = im2double(I);
I1 = imresize(I, [640 640]);
s = size(I1);
h = s(1);
w = s(2);
imshow(I1);
disp('1) Show student name and ID. Then quit the program.');
disp('2) Shift the image to left');
disp('3) Shift the image to right');
disp('4) Shift the image to top');
disp('5) Shift the image to bottom');
disp('6) Turn on or off a spot light on the center.');

while true
    op = input('Please enter an option:');
    switch(op)
        case 1
            disp('Student ID:0616098 Student name:¶ÀªÃ­Z');
            disp('Thanks for playing');
            return;
        case 2
            for i = 1 : w / 10 
                idx = 1;
                for j = 1 : 10
                    temp_y(:, idx, 1:3) = I1(:, j, 1:3);
                    idx = idx + 1;
                end
                for j = 1 : w - 10
                    I1(:, j, 1:3) = I1(:, j + 10, 1:3);                    
                end
                idx = 1;
                for j = w - 9 : w
                    I1(:, j, 1:3) = temp_y(:, idx, 1:3);
                    idx = idx + 1;
                end
                imshow(I1);
                pause(0.00000000001);
            end
        case 3
            for i = 1 : w / 10 
                idx = 1;
                for j = w - 9 : w
                    temp_y(:, idx, 1:3) = I1(:, j, 1:3);
                    idx = idx + 1;
                end
                for j = w - 10 : -1 : 1
                    I1(:, j + 10, 1:3) = I1(:, j, 1:3);                    
                end
                idx = 1;
                for j = 1 : 10
                    I1(:, j, 1:3) = temp_y(:, idx, 1:3);
                    idx = idx + 1;
                end
                imshow(I1);
                pause(0.00000000001);
            end
        case 4
            for i = 1 : h / 10 
                idx = 1;
                for j = 1 : 10
                    temp_x(idx, :, 1:3) = I1(j ,:, 1:3);
                    idx = idx + 1;
                end
                for j = 1 : h - 10
                    I1(j, :, 1:3) = I1(j + 10, :, 1:3);                    
                end
                idx = 1;
                for j = h - 9 : h
                    I1(j, :, 1:3) = temp_x(idx, :, 1:3);
                    idx = idx + 1;
                end
                imshow(I1);
                pause(0.00000000001);
            end
        case 5
            for i = 1 : h / 10 
                idx = 1;
                for j = h - 9 : h
                    temp_x(idx, :, 1:3) = I1(j, :, 1:3);
                    idx = idx + 1;
                end
                for j = h - 10 : -1 : 1
                    I1(j + 10, :, 1:3) = I1(j, :, 1:3);                    
                end
                idx = 1;
                for j = 1 : 10
                    I1(j, :, 1:3) = temp_x(idx, :, 1:3);
                    idx = idx + 1;
                end
                imshow(I1);
                pause(0.00000000001);
            end
        case 6
            K = ones(s, 'double'); 
            for i = 1 : h
                for j = 1 : w
                    if((i - w / 2) ^ 2 + (j - w / 2) ^ 2 <= (w / 2) ^ 2)
                        K(i, j, 1:3) = 0.5; 
                    end
                end
            end
            for i = 1 : 2
                imshow(I1 ./ K);
                pause(1);
                imshow(I1 .* K);
                pause(1);
            end
    end
end


