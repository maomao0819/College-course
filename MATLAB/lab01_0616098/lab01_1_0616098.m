%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Lab Number: 1
% Problem number: Lab 1.1
% Student Name: ¶ÀªÃ­Z
% Student ID: 0616098   
% Email address: maomao.08190@gmail.com
% Department: Computer Science, NCTU
% Date: 3/28
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
disp('Lab Problem 1.1'); clf; clear; clc;
fprintf('Student ID:0616098 Name:¶ÀªÃ­Z\n');
while 1
    a = input('Please input the number a:');
    if(a == 0)
        disp('Thanks for playing');
        break;
    else
        dx = input('Please input the step size, dx: ');
        if(dx == 0 )
            dx = 0.05;
        end
        while dx < 0
            dx = input('dx must be a non-negative number, dx: ');
        end
        x = [-10 : dx : 10];
        y = a .* abs(x) + sin(x);
        plot(x, y, 'LineWidth', 3); hold on
    end
end