%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Assignment Number: Lab Two
% Problem number: 2
% Student Name:  ¶ÀªÃ­Z
% Student ID: 0616098  
% Email address: maomao.08190@gmail.com
% Department: Computer Science, NCTU
% Date: 4/29
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% close all windows
% clear variables, and clear screen
close all; clf; clear; clc;

% show Lab Two Problem 2
disp('Lab Two Problem 2')  
fprintf('Student ID:0616098 Name:¶ÀªÃ­Z\n');

%input
while true
    a = input('Please input a: ');
    if (a == 0) 
        return;
    end
    if (a <= 10 && a >= -10) 
        break;
    end    
end
dx = input('Please the step size, dx, of x: ');
while (dx > 1 || dx < 0)
    m = input('dx must be inside (0, 1], dx: ');
end
if (dx == 0)
    dx = 0.05;
end
x = -10 : dx : 10;
y = abs(x) + a .* sin(x);
axis([-10 10 -20 20]);
for i = 1 : (10 - (-10)) / dx + 1
    clf;
    plot(x, y, 'LineWidth', 3); hold on
    x0 = x(i);
    y0 = y(i);
    plot(x0, y0, 'o', 'color', 'r');
    axis([-10 10 -20 20]);
    grid on;
    pause(dx);
end


