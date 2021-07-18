%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Midterm Number: 1
% Problem number: 1
% Student Name: ¶ÀªÃ­Z
% Student ID: 0616098
% Email address: maomao.08190@gmail.com
% Department: Computer Science, NCTU
% Date: 4/18.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

close all; clear; clc;		% close all windows
                            % clear variables, and clear screen

disp('Midterm Problem 1.1') 	% show Midterm Problem 1.1

disp('Student Name: ¶ÀªÃ­Z Student ID: 0616098');

while 1
    a = input('Please input the number a: ');
    if a == 0
        disp('Thanks for playing');
        return;
    else
        dx = -1;
        while dx * -1 > 0
            dx = input('Please input the step size, dx, of x: ');
        end
        if dx == 0
            dx = 0.025;
        end
        x = [-5 : dx : 5];
        y = a .* cos(abs(x)) + sin(6 .* x .^ 2) - 1 ./ (x .^ 2 + 1);
        plot(x, y, 'LineWidth', 3); hold on
    end
end