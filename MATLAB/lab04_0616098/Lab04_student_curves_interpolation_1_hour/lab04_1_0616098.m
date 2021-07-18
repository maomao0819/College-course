%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Assignment Number: Lab4
% Problem number: 1
% Student Name:  ¶ÀªÃ­Z
% Student ID: 0616098
% Email address: maomao.08100@gmail.com
% Department: Computer Science, NCTU
% Date: 5/13
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% close all windows
% clear variables, and clear screen
close all; clf; clear; clc;

% show Lab Problem 4.1
disp('Lab Problem 4.1')  

%y1(x) = sin(5x) + 5, y2(x) = 2cos(x^2) ¡V 5
%z1(x) = x*sin(x/2) + 5, z2(x) = 2cos(x^2)/(sin(x)+1.5) - 1

x = -10:0.025:10;
y1 = sin(5 * x) + 5;
y2 = 2 * cos(x .^ 2) - 5;

z1 = x .* sin(x / 2) + 5;
z2 = 2 * cos(x .^ 2) ./ (sin(x) + 1.5) - 1;

clf
hold on
subplot(1, 2, 1);
plot(x, y1, 'linewidth', 2);
plot(x, y2, 'linewidth', 2);
subplot(1, 2, 2);    
plot(x, z1, 'linewidth', 2);
plot(x, z2, 'linewidth', 2);
    
for k = 1:-0.01:0
    pause(1 / 30);
    clf
    subplot(1, 2, 1);
    hold on
    plot(x, y1, 'linewidth', 2);
    plot(x, y2, 'linewidth', 2);
    y = k .* y1 + (1 - k) .* y2;
    plot(x, y, 'linewidth', 2);  
    set(gca,'FontSize',15);         %set font size
    
    subplot(1, 2, 2);
    hold on
    plot(x, z1, 'linewidth', 2);
    plot(x, z2, 'linewidth', 2);
    z = k .* z1 + (1 - k) .* z2;
    plot(x, z, 'linewidth', 2); 
    set(gca, 'FontSize', 15);         %set font size

    if (k == 1)
        input('Press a key to continue...');
    end
end

