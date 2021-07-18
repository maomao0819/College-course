%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Assignment Number: Lab6
% Problem number: 3
% Student Name:  ¶ÀªÃ­Z
% Student ID: 0616098
% Email address: maomao.08190@gmail.com
% Department: Computer Science, NCTU
% Date: 6/7
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% close all windows
% clear variables, and clear screen
close all; clf; clear; clc;

% show Lab Problem 6.3
disp('Lab Problem 6.3')  


%x0 is in [0, 10]
x0 = input('Please input the number x0: ');
if x0 == 0
    disp('Thanks for playing');
end
if x0 ~= 0
    syms x;
    y1 = sym(sin(x));
    area1 = int(abs(y1), x, 0, x0);
    area1 = double(area1);
    y2 = sym(cos(2 .* x));
    area2 = int(abs(y2), x, 0, x0);
    area2 = double(area2);
    y3 = sym(x .^ 2 .* sin(x) .* exp(-(x-1)));
    area3 = int(abs(y3), x, 0, x0);
    area3 = double(area3);
    y4 = sym(4 - x ./ 2);
    area4 = int(abs(y4), x, 0, x0);
    area4 = double(area4);
    area = [area1 area2 area3 area4];
    [sort_area , order] = sort(area);
    x = 0 : 0.01 : 10;
    y1 = sin(x);
    y2 = cos(2 .* x);
    y3 = x .^ 2 .* sin(x) .* exp(-(x-1));
    y4 = 4 - x ./ 2;
    xlim([0 10]);	
    subplot(2, 2, 1)
    plot(x, y1);
    %set(gca, 'xtick', [0 : 2 : 10]);
    grid on;
    hold on;
    title(['(', num2str(find(order == 1)), '): y1(x) = sin(x): Area = ', num2str(area1)]);
    subplot(2, 2, 2)
    plot(x, y2);
    %set(gca, 'xtick', [0 : 2 : 10]);
    grid on;
    hold on;
    title(['(', num2str(find(order == 2)), '): y2(x) = cos(2*x): Area = ', num2str(area2)]);
    subplot(2, 2, 3)
    plot(x, y3);
    %set(gca, 'xtick', [0 : 2 : 10]);
    grid on;
    hold on;
    title(['(', num2str(find(order == 3)), '): y3(x) = x^2*sin(x)*exp(-(x-1)): Area = ', num2str(area3)]);
    subplot(2, 2, 4)
    plot(x, y4);
    %set(gca, 'xtick', [0 : 2 : 10]);
    grid on;
    hold on;
    title(['(', num2str(find(order == 4)), '): y4(x) = 4-x/2: Area = ', num2str(area4)]);
    idx = 1;
    subplot(2, 2, 1)
    line1 = plot([0 x(1)], [0 y1(1)], 'r');
    subplot(2, 2, 2)
    line2 = plot([0 x(1)], [0 y2(1)], 'r');
    subplot(2, 2, 3)
    line3 = plot([0 x(1)], [0 y3(1)], 'r');
    subplot(2, 2, 4)
    line4 = plot([0 x(1)], [0 y4(1)], 'r');
    size = size(x);
    for i = 2 : size(2)
        subplot(2, 2, 1)
        delete(line1)
        line1 = plot([x(i) x(i)], [0 y1(i)], 'r');
        subplot(2, 2, 2)
        delete(line2)
        line2 = plot([x(i) x(i)], [0 y2(i)], 'r');
        subplot(2, 2, 3)
        delete(line3)
        line3 = plot([x(i) x(i)], [0 y3(i)], 'r');
        subplot(2, 2, 4)
        delete(line4)
        line4 = plot([x(i) x(i)], [0 y4(i)], 'r');
        pause(0.025);
    end
end
