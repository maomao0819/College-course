%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Assignment Number: 2
% Problem number: 2
% Student Name: ¶ÀªÃ­Z
% Student ID: 0616098   
% Email address: maomao.08190@gmail.com
% Department: Computer Science, NCTU
% Date: 3/28
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

disp('Problem 2'); clf; clear; clc;
fprintf('Student ID:0616098 Name:¶ÀªÃ­Z\n');
while 1
    a = [10, 2];
    while a(1) > a(2)
        a = input('Please input the range of a, [aMin, aMax]:');
    end
    da = -2;
    while da < 0
        da = input('Please input the step size, da:');
    end
    if(da == 0 )
        disp('Thanks for playing');
        break;
    else
        clf;
        x = [-10 : 0.05 : 10];
        for a = [a(1) : da : a(2)]
                y = abs(sin(a .* x) .* cos(x));
                plot(x, y, 'LineWidth',2); hold on
        end
    end
end