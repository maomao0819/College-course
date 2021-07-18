%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Assignment Number: Lab5
% Problem number: 2
% Student Name:  ¶ÀªÃ­Z
% Student ID: 0616098
% Email address: maomao.08190@gmail.com
% Department: Computer Science, NCTU
% Date: 5/21
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% close all windows
% clear variables, and clear screen
close all; clf; clear; clc;

% show Lab Problem 5.2
disp('Lab Problem 5.2')  

x = 0 : 0.25 : 2 * pi;
y1 = sin(x);
y2 = cos(2 * x);
plot(x, y1, 'linewidth', 3, 'color', 'red'); hold on
plot(x, y2, 'linewidth', 3, 'color', 'blue');
x_arr = [];
y1_arr = [];
y2_arr = [];
hold off;
step_size = 0.05;
for i = 0 : step_size : max(x)
    if (i == 0)
        input('Press a key to continue...');
    end
    clf;
    x_arr = [x_arr i];
    y1_temp = sin(i);
    y1_arr = [y1_arr y1_temp];
    y2_temp = cos(2 * i);
    y2_arr = [y2_arr y2_temp];
    hold on
    plot(x_arr, y1_arr, 'linewidth', 3, 'color', 'red'); 
    plot(x_arr, y2_arr, 'linewidth', 3, 'color', 'blue');
    axis([ min(x) max(x) min(y2) max(y2)]);
    text(i, y1_temp, 'y1(x)');
    text(i, y2_temp, 'y2(x)');
    xlabel('x');
    ylabel('y');
    title('y1(x) = sin(x). y2(x) = cos(2x)');
    patch([x_arr fliplr(x_arr)], [y1_arr fliplr(y2_arr)], 'y')
    legend('y1(x)', 'y2(x)', 'region');
    pause(1/1000000000);
end