%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Lab Number: 1
% Problem number: Lab 1.4
% Student Name: ¶ÀªÃ­Z
% Student ID: 0616098   
% Email address: maomao.08190@gmail.com
% Department: Computer Science, NCTU
% Date: 3/28
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
disp('Lab Problem 1.4'); clf; clear; clc;
fprintf('Student ID:0616098 Name:¶ÀªÃ­Z\n');
a = input('Please input the number a:');
dx = -1;
while dx < 0;
    dx = input('Please input the step size dx of x (dx must be a non-negative value): ');
end
x = [-10 : dx : 10];
y = (2 .* x .^ 2 + 3 .* exp(-1 .* x) - (100 * a) .* sin(5 .* x)) ./ (6 .* x .^ 2 - 9 .* x - 42) - 10; 
i1 = find(y >= 0);
y11 = y(i1);
x11 = x(i1);
hold on
plot(x11, y11, '.','color', 'blue');
ylim([-100, 100]);
i = find(y < 0);
y1 = y(i);
x1 = x(i);
plot(x1, y1,'.', 'color', 'red');
ylim([-100, 100]);