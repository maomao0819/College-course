%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Midterm Number: 1
% Problem number: 3
% Student Name: ¶ÀªÃ­Z
% Student ID: 0616098
% Email address: maomao.08190@gmail.com
% Department: Computer Science, NCTU
% Date: 4/18.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

close all; clear; clc;		% close all windows
                            % clear variables, and clear screen

disp('Midterm Problem 1.3') 	% show Midterm Problem 1.1

disp('Student Name: ¶ÀªÃ­Z Student ID: 0616098');

while 1
    m = input('Please input the number m: ');
    while m < 0 || m >5
        m = input('Please input the number m, which is a non-negative integer and inside [0, 5]: ');
    end
    if(m == 0)
        disp('Thanks for playing');
        break;
    else
        clf;
        x = -5 : 0.02 : 5;
        y1 = sinh(x);
        plot(x, y1, 'LineWidth', 5, 'color', 'blue'); hold on
        for n = 0 : m
            y2 = 0;
            time = n;
            while time >= 0
                y2 = y2 +  x .^ (2 * time + 1) ./ factorial(2 * time + 1);
                time = time - 1;
            end
            plot(x, y2, 'LineWidth', 2);
        end
    end
end