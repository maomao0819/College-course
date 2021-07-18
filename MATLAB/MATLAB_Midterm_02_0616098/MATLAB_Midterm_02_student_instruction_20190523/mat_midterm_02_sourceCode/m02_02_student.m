%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Midterm Number: Two
% Problem number: 2
% Student Name: Ping-MAo Huang
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
I1 = imresize(I,[640 640]);

while true
    disp('1) Show student name and ID. Then quit the program.');
    disp('2) Shift the image to left');
    disp('3) Shift the image to right');
    disp('4) Shift the image to top');
    disp('5) Shift the image to bottom');
    disp('6) Turn on or off a spot light on the center.');
    op = input('Please enter an option:');
    switch(op)
        case 1
            disp('Student ID:0616098 Student name:Ping-MAo Huang');
            disp('Thanks for playing');
            return;
        case 2
            
        case 3
        case 4
        case 5
        case 6
    end
    
end


