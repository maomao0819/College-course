%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Assignment Number: Lab3
% Problem number: Example
% Student Name: ¶ÀªÃ­Z
% Student ID: 0616098   
% Email address: maomao.08190@gmail.com
% Department: Computer Science, NCTU
% Date: 5/6
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% close all windows
% clear variables, and clear screen
close all; clf; clear; clc;

% show Lab Example
disp('Lab Example')  


I = imread('tmp.png');

Id = im2double(I);

s = size(Id);
w = s(2);
h = s(1);
%¤W
Id(1:10,:, 1) = 0;
Id(1:10,:, 2) = 1.0;
Id(1:10,:, 3) = 0;
%¤U
Id((h-10):h,:, 1) = 0;
Id((h-10):h,:, 2) = 1.0;
Id((h-10):h,:, 3) = 0;
%¥ª
Id(:,1:10, 1) = 0;
Id(:,1:10, 2) = 1.0;
Id(:,1:10, 3) = 0;
%¥k
Id(:,(w-10):w, 1) = 0;
Id(:,(w-10):w, 2) = 1.0;
Id(:,(w-10):w, 3) = 0;

imshow(Id);

