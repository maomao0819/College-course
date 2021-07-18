%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Midterm Number: Two
% Problem number: 3
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
disp('Midterm Two Problem 3')

axis([-10 10 -20 20]);
grid

dx = 0.02;
x = -10:dx:10;
y11 = cos(2 * 1 .* x);
y12 = 2 .* x .* sin(1 .^ 2 .* x) ./ (x .^ 2 + 1) - 2;
y21 = cos(2 * 2 .* x);
y22 = 2 .* x .* sin(2 .^ 2 .* x) ./ (x .^ 2 + 1) - 2;
y31 = cos(2 * 3 .* x);
y32 = 2 .* x .* sin(3 .^ 2 .* x) ./ (x .^ 2 + 1) - 2;
y41 = cos(2 * 4 .* x);
y42 = 2 .* x .* sin(4 .^ 2 .* x) ./ (x .^ 2 + 1) - 2;

clf
hold on
subplot(2, 2, 1);
plot(x, y11, 'color', 'red', 'linewidth', 3);
plot(x, y12, 'color', 'red', 'linewidth', 3);
subplot(2, 2, 2);    
plot(x, y21, 'color', 'red', 'linewidth', 3);
plot(x, y22, 'color', 'blue', 'linewidth', 3);
subplot(2, 2, 3);    
plot(x, y31, 'color', 'red', 'linewidth', 3);
plot(x, y32, 'color', 'blue', 'linewidth', 3);
subplot(2, 2, 4);    
plot(x, y41, 'color', 'red', 'linewidth', 3);
plot(x, y42, 'color', 'blue', 'linewidth', 3);
    
for k = 1 : -0.01 : 0
    pause(1 / 30);
    clf
    subplot(2, 2, 1);
    hold on
    plot(x, y11, 'color', 'red', 'linewidth', 3);
    plot(x, y12, 'color', 'blue', 'linewidth', 3);
    y13 = k .* y11 + (1 - k) .* y12;
    plot(x, y13, 'linewidth', 2);  
    title({'cos(2*1*x)'; '2*x*sin(1^2*x)/(x^2+1)-2'});
        
    subplot(2, 2, 2);
    hold on
    plot(x, y21, 'color', 'red', 'linewidth', 3);
    plot(x, y22, 'color', 'blue', 'linewidth', 3);
    y23 = k .* y21 + (1 - k) .* y22;
    plot(x, y23, 'linewidth', 2);
    title({'cos(2*2*x)'; '2*x*sin(2^2*x)/(x^2+1)-2'});
    
    subplot(2, 2, 3);
    hold on
    plot(x, y31, 'color', 'red', 'linewidth', 3);
    plot(x, y32, 'color', 'blue', 'linewidth', 3);
    y33 = k .* y31 + (1 - k) .* y32;
    plot(x, y33, 'linewidth', 2);
    title({'cos(2*3*x)'; '2*x*sin(3^2*x)/(x^2+1)-2'});
    
    subplot(2, 2, 4);
    hold on
    plot(x, y41, 'color', 'red', 'linewidth', 3);
    plot(x, y42, 'color', 'blue', 'linewidth', 3);
    y43 = k .* y41 + (1 - k) .* y42;
    plot(x, y43, 'linewidth', 2);
    title({'cos(2*4*x)'; '2*x*sin(4^2*x)/(x^2+1)-2'});

    if (k == 1)
        input('Press a key to continue...');
    end
end

