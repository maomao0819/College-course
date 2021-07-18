%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Assignment Number: Lab4
% Problem number: 2
% Student Name:  ¶ÀªÃ­Z
% Student ID: 0616098
% Email address: maomao.08100@gmail.com
% Department: Computer Science, NCTU
% Date: 5/13
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% close all windows
% clear variables, and clear screen
close all; clf; clear; clc;

% show Lab Problem 4.2
disp('Lab Problem 4.2')  

x = 0 : 0.01 : pi * 2;
x0 = [];    %theta
r0 = [];    %rho
for it_x = x
    x0 = [x0 it_x];
    r_temp = cos(2 * it_x) .* sin(2 * it_x);
    r0 = [r0 r_temp];
    h = polar(x0, r0, 'k');
    patch(get(h, 'XData'), get(h, 'YData'), 'y')
	pause(0.033);
end
