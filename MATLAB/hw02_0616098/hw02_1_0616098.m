%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Assignment Number: 2
% Problem number: 1
% Student Name: ¶ÀªÃ­Z
% Student ID: 0616098   
% Email address: maomao.08190@gmail.com
% Department: Computer Science, NCTU
% Date: 3/28
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

disp('Problem 1'); clf; clear; clc;
fprintf('Student ID:0616098 Name:¶ÀªÃ­Z\n');
while 1
    a0 = input('Please input a0 in a vector form: ');
    b0 = input('Please input b0 in a vector form: ');
    if(a0 == 0 && b0 == 0)
        disp('Thanks for playing');
        break;
    else
        clf;
        x = [-10 : 0.05 : 10];
        for a = [a0 - 10 : a0 + 10]
            for b = [b0 - 10 : b0 + 10]
                y = a .* sin(x) + b .* cos(x);
                plot(x, y); hold on
            end
        end
    end
end