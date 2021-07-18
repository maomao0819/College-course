%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Assignment Number: 2
% Problem number: 4
% Student Name: ¶ÀªÃ­Z
% Student ID: 0616098   
% Email address: maomao.08190@gmail.com
% Department: Computer Science, NCTU
% Date: 3/28
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

disp('Problem 4'); clf; clear; clc;
fprintf('Student ID:0616098 Name:¶ÀªÃ­Z\n');
x = [-5 : 0.005 : 10];
y = (5 .* x .^ 2 + 2 .* x + 7) ./ (x .^ 2 - 5 .* x - 14);
i1 = find(y >= 0);
y11 = y(i1);
x11 = x(i1);
hold on
plot(x11, y11, 'color', 'red', 'LineWidth',2); 
i1 = find(y < 0);
y11 = y(i1);
x11 = x(i1);
plot(x11, y11, 'color', 'blue', 'LineWidth',2);