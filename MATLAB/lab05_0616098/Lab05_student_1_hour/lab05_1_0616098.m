%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Assignment Number: Lab5
% Problem number: 1
% Student Name:  ¶ÀªÃ­Z
% Student ID: 0616098
% Email address: maomao.08190@gmail.com
% Department: Computer Science, NCTU
% Date: 5/21
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% close all windows
% clear variables, and clear screen
close all; clf; clear; clc;

% show Lab Problem 5.1
disp('Lab Problem 5.1')  

c = -1; sigma = 3; r1 = 2.5; r2 = 3.5;
syms x;
y = sym(exp(-(x - c) ^ 2 / (2 * sigma ^ 2)));
A = int(y, x, r1, r2);
n = [1000 100000 1000000]; 
mean_n = [];
std_n = [];
for n_idx = n
    i = 1;
    while (i <= n_idx)
        x = r1 + (r2 - r1) * rand(1);
        p  = gaussmf(x, [sigma, c]);
        r = x * p * (r2 - r1);
        a(i) = r;
        i = i + 1;
    end
    mean_n = [mean_n double(mean(a) / A)];
    std_n = [std_n double(std(a) / A)];
end
x = -9 : 0.2 : 7;
y = gaussmf(x, [sigma c]);
plot(x,y);
axis([ -10 8 0 1]);
title({['n = ', num2str(n(1)) , '; Mean=', num2str(mean_n(1)), '; SD:', num2str(std_n(1))];...
    ['n = ', num2str(n(2)) , '; Mean=', num2str(mean_n(2)), '; SD:', num2str(std_n(2))];...
    ['n = ', num2str(n(3)) , '; Mean=', num2str(mean_n(3)), '; SD:', num2str(std_n(3))]});
hold on
x = r1 : 0.2 : r2;
y = gaussmf(x, [sigma c]);
x = [x,r2];	%extra point
y = [y,0];
x = [x,r1];	%extra point
y = [y,0];
fill(x, y, 'b');
legend('y(x)', 'Data');

