%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Midterm Number: 1
% Problem number: 2
% Student Name: ¶ÀªÃ­Z
% Student ID: 0616098
% Email address: maomao.08190@gmail.com
% Department: Computer Science, NCTU
% Date: 4/18.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

close all; clear; clc;		% close all windows
                            % clear variables, and clear screen

disp('Midterm Problem 1.2') 	% show Midterm Problem 1.1

disp('Student Name: ¶ÀªÃ­Z Student ID: 0616098');

while 1
    b = input('Please input the number b: ');
    if(b == 0)
        disp('Thanks for playing');
        break;
    else
        clf;
        dy = 0.001;
        y = [-10 : dy : 10];
        for a = 1 : 10
            A = -a .* (abs(cos(y .^ 2)) + 1);
            B = y;
            C = b .* y .^ 2;
            x1 = (-B + sqrt(B .^ 2 - 4 .* A .* C)) ./ (2 .* A);
            x2 = (-B - sqrt(B .^ 2 - 4 .* A .* C)) ./ (2 .* A);
            hold on;
            plot(x1, y, 'LineWidth',3); 
            plot(x2, y, 'LineWidth',3);
            xlim([-10, 10]);
            ylim([-5, 5]);
        end
    end
end