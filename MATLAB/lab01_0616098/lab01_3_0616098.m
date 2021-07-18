%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Lab Number: 1
% Problem number: Lab 1.3
% Student Name: ¶ÀªÃ­Z
% Student ID: 0616098   
% Email address: maomao.08190@gmail.com
% Department: Computer Science, NCTU
% Date: 3/28
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
disp('Lab Problem 1.3'); clf; clear; clc;
fprintf('Student ID:0616098 Name:¶ÀªÃ­Z\n');
while 1
    m = 20;
    while m > 10 || m < 0
        m = input('Please input a number m, which is a non-negative integer and inside [0, 10] : ');
    end
    if(m == 0)
        disp('Thanks for playing');
    else
        clf;
        x = [-10 : 0.01 : 10];
     y1 = cos(x);
        y = y1;
        plot(x, y, 'LineWidth', 4); hold on
        for n = 0 : m
            y2 = 0;
            time = n;
            while time >= 0
                y2 = y2 + ((-1) ^ time / factorial(2 * time)) .* x .^ (2 * time);
               time = time - 1;
            end
            y = y2;
            plot(x, y, 'LineWidth', 2);
        end
    end
end