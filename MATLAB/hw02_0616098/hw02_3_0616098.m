%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Assignment Number: 2
% Problem number: 3
% Student Name: ¶ÀªÃ­Z
% Student ID: 0616098   
% Email address: maomao.08190@gmail.com
% Department: Computer Science, NCTU
% Date: 3/28
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

disp('Problem 3'); clf; clear; clc;
fprintf('Student ID:0616098 Name:¶ÀªÃ­Z\n');
while 1
    m = 11;
    while m < -1 || m >= 10
    m = input('Please input an integer m inside [-1, 10]: ');
    end
    if(m == -1)
        disp('Thanks for playing');
        break;
    else
        clf;
        x = [-5 : 0.01 : 5];
        y1 = sin(x);
        plot(x, y1, 'LineWidth',4); hold on
        ylim([-1.5, 1.5]);
        for n = 0 : m
            y2 = 0;
            time = n;
            while time >= 0
                y2 = y2 + ((-1) ^ time / factorial(2 * time + 1)) .* x .^ (2 * time + 1);
                time = time - 1;
            end
            plot(x, y2, 'LineWidth',1);
            ylim([-1.5, 1.5]);
        end
    end
end

