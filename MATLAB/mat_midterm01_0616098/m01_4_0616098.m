%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Midterm Number: 1
% Problem number: 4
% Student Name: ¶ÀªÃ­Z
% Student ID: 0616098
% Email address: maomao.08190@gmail.com
% Department: Computer Science, NCTU
% Date: 4/18.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

close all; clear; clc;		% close all windows
                            % clear variables, and clear screen

disp('Midterm Problem 1.4') 	% show Midterm Problem 1.1

disp('Student Name: ¶ÀªÃ­Z Student ID: 0616098');

b = input('Please input the number b: ');
dx = 0.001;
x = -5 : dx : -2;
y = (2 .* exp(-2 .* x) - b .* x .* cos(abs(5 .* x)) + abs(x) .^ (1 / 2)) ./ ((x - 1) .* (x - 2) .* (x + 1) .* (x + 2));
plot(x, y, 'LineWidth', 3); hold on
ylim([-50, 50]);
x = -2 : dx : -1;
y = (2 .* exp(-2 .* x) - b .* x .* cos(abs(5 .* x)) + abs(x) .^ (1 / 2)) ./ ((x - 1) .* (x - 2) .* (x + 1) .* (x + 2));
plot(x, y, 'LineWidth', 3); 
x = -1 : dx : 1;
y = (2 .* exp(-2 .* x) - b .* x .* cos(abs(5 .* x)) + abs(x) .^ (1 / 2)) ./ ((x - 1) .* (x - 2) .* (x + 1) .* (x + 2));
plot(x, y, 'LineWidth', 3); 
x = 1 : dx : 2;
y = (2 .* exp(-2 .* x) - b .* x .* cos(abs(5 .* x)) + abs(x) .^ (1 / 2)) ./ ((x - 1) .* (x - 2) .* (x + 1) .* (x + 2));
plot(x, y, 'LineWidth', 3);
x = 2 : dx : 5;
y = (2 .* exp(-2 .* x) - b .* x .* cos(abs(5 .* x)) + abs(x) .^ (1 / 2)) ./ ((x - 1) .* (x - 2) .* (x + 1) .* (x + 2));
plot(x, y, 'LineWidth', 3); 
