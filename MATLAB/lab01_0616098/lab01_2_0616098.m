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
while 1
    b = input('Please input the number b:');
    if(b == 0)
        disp('Thanks for playing');
        break;
    else
        clf;
        y = [-10 : 0.001 : 10];
        A = abs(sin(y)) + 1;
        B = (-2 .* y);
        C = -1 .* b .* y .^ 2;
        x1 = (-B + sqrt(B .^ 2 - 4 .* A .* C)) ./ (2 .* A);
        x2 = (-B - sqrt(B .^ 2 - 4 .* A .* C)) ./ (2 .* A);
        plot(x1, y, 'LineWidth',3); hold on
        plot(x2, y, 'LineWidth',3);
    end
end