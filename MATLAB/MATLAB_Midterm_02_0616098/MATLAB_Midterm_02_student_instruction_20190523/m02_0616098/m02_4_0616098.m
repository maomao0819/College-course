%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Midterm Number: Two
% Problem number: 4
% Student Name: ¶ÀªÃ­Z
% Student ID: 0616098
% Email address: maomao.08190@gmail.com
% Department: CS
% Date: 5/23
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% close all windows
% clear variables, and clear screen
close all; clf; clear; clc;

% show Midterm Two Problem 4
disp('Midterm Two Problem 4')
while true
    while true
        n = input('Please input n:');
        if n >= 0 && n <= 10000
            break;
        end
    end
    if (n==0)
        disp('Student ID 0616098.');
        disp('Thanks for playing.');
        return;
    end

    disp('1) Plot the curves of y(1,1) and y(1,2) in one figure.');
    disp('2) Plot two pairs of curves, (y(1,1) and y(1,2)) and (y(2,1) and y(2,2)).');
    disp('3) Plot the four pairs of curves.');
    op = input('Please input an option:');

    dx = 0.01;
    x = -5:dx:5;

    h = figure;
    dx = 0.01;
    ymin = -15; ymax = 15;
    xmin = -5; xmax = 5;

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    y11 = sin(x) .* sqrt(abs(x));
    y12 = 2 .* cos(x) .* exp(cos(x .^ 2));

    switch(op)
        case 1
            hold on
            plot(x, y11, 'color', 'red', 'linewidth', 2);
            plot(x, y12, 'color', 'blue', 'linewidth', 2);
            min_y = min(y11);
            if(min(y11) > min(y12))
                min_y = min(y12);
            end
            max_y = max(y11);
            if(max(y11) < max(y12))
                max_y = max(y12);
            end
            set(gca, 'xtick', [xmin : 1 : xmax]);
            axis([-5 5 min_y max_y]);
            grid on
            x_fig = [];
            y_fig = [];
            count = 0;
            while count < n
                while true
                    x0 = rand(1); x0 = xmin + ( xmax - xmin )*x0;
                    if (xmin <= x0 && x0 <= xmax)
                         break;
                    end
                end
                while true
                    y0 = rand(1); y0 = ymin + ( ymax - ymin )*y0;
                    if (ymin <= y0 && y0 <= ymax)
                         break;
                    end
                end
                count = count + 1;
                if((y0 - (sin(x0) * sqrt(abs(x0)))) * (y0 - (2 * cos(x0) * exp(cos(x0 .^ 2)))) < 0)
                    x_fig = [x_fig x0];
                    y_fig = [y_fig y0];
                end
            end 
            plot(x_fig, y_fig, '.' , 'Color', 'g');

        case 2
            subplot(2, 1, 1);
            hold on
            plot(x, y11, 'color', 'red', 'linewidth', 2);
            plot(x, y12, 'color', 'blue', 'linewidth', 2);
            min_y = min(y11);
            if(min(y11) > min(y12))
                min_y = min(y12);
            end
            max_y = max(y11);
            if(max(y11) < max(y12))
                max_y = max(y12);
            end
            set(gca, 'xtick', [xmin : 1 : xmax]);
            axis([-5 5 min_y max_y]);
            grid on
            x_fig = [];
            y_fig = [];
            count = 0;
            while count < n
                while true
                    x0 = rand(1); x0 = xmin + ( xmax - xmin )*x0;
                    if (xmin <= x0 && x0 <= xmax)
                         break;
                    end
                end
                while true
                    y0 = rand(1); y0 = ymin + ( ymax - ymin )*y0;
                    if (ymin <= y0 && y0 <= ymax)
                         break;
                    end
                end
                count = count + 1;
                if((y0 - (sin(x0) * sqrt(abs(x0)))) * (y0 - (2 * cos(x0) * exp(cos(x0 .^ 2)))) < 0)
                    x_fig = [x_fig x0];
                    y_fig = [y_fig y0];
                end
            end 
            plot(x_fig, y_fig, '.' , 'Color', 'g');
            y21 = sin(x) + x .^ 2 .* cos(x); 
            y22 = 2 .* sin(x) .* exp(sin(x .^ 2));
            subplot(2, 1, 2);
            hold on
            plot(x, y21, 'color', 'red', 'linewidth', 2);
            plot(x, y22, 'color', 'blue', 'linewidth', 2);
            min_y = min(y21);
            if(min(y21) > min(y22))
                min_y = min(y22);
            end
            max_y = max(y21);
            if(max(y21) < max(y22))
                max_y = max(y22);
            end
            set(gca, 'xtick', [xmin : 1 : xmax]);
            axis([-5 5 min_y max_y]);
            grid on
            x_fig = [];
            y_fig = [];
            count = 0;
            while count < n
                while true
                    x0 = rand(1); x0 = xmin + ( xmax - xmin )*x0;
                    if (xmin <= x0 && x0 <= xmax)
                         break;
                    end
                end
                while true
                    y0 = rand(1); y0 = ymin + ( ymax - ymin )*y0;
                    if (ymin <= y0 && y0 <= ymax)
                         break;
                    end
                end
                count = count + 1;
                if((y0 - (sin(x0) + x0 ^ 2 * cos(x0))) * (y0 - (2 * sin(x0) * exp(sin(x0 ^ 2)))) < 0)
                    x_fig = [x_fig x0];
                    y_fig = [y_fig y0];
                end
            end 
            plot(x_fig, y_fig, '.' , 'Color', 'g');
        case 3
            subplot(2, 2, 1);
            hold on
            plot(x, y11, 'color', 'red', 'linewidth', 2);
            plot(x, y12, 'color', 'blue', 'linewidth', 2);
            min_y = min(y11);
            if(min(y11) > min(y12))
                min_y = min(y12);
            end
            max_y = max(y11);
            if(max(y11) < max(y12))
                max_y = max(y12);
            end
            set(gca, 'xtick', [xmin : 1 : xmax]);
            axis([-5 5 min_y max_y]);
            grid on
            x_fig = [];
            y_fig = [];
            count = 0;
            while count < n
                while true
                    x0 = rand(1); x0 = xmin + ( xmax - xmin )*x0;
                    if (xmin <= x0 && x0 <= xmax)
                         break;
                    end
                end
                while true
                    y0 = rand(1); y0 = ymin + ( ymax - ymin )*y0;
                    if (ymin <= y0 && y0 <= ymax)
                         break;
                    end
                end
                count = count + 1;
                if((y0 - (sin(x0) * sqrt(abs(x0)))) * (y0 - (2 * cos(x0) * exp(cos(x0 .^ 2)))) < 0)
                    x_fig = [x_fig x0];
                    y_fig = [y_fig y0];
                end
            end 
            plot(x_fig, y_fig, '.' , 'Color', 'g');
            y21 = sin(x) + x .^ 2 .* cos(x); 
            y22 = 2 .* sin(x) .* exp(sin(x .^ 2));
            subplot(2, 2, 2);
            hold on
            plot(x, y21, 'color', 'red', 'linewidth', 2);
            plot(x, y22, 'color', 'blue', 'linewidth', 2);
            min_y = min(y21);
            if(min(y21) > min(y22))
                min_y = min(y22);
            end
            max_y = max(y21);
            if(max(y21) < max(y22))
                max_y = max(y22);
            end
            set(gca, 'xtick', [xmin : 1 : xmax]);
            axis([-5 5 min_y max_y]);
            grid on
            x_fig = [];
            y_fig = [];
            count = 0;
            while count < n
                while true
                    x0 = rand(1); x0 = xmin + ( xmax - xmin )*x0;
                    if (xmin <= x0 && x0 <= xmax)
                         break;
                    end
                end
                while true
                    y0 = rand(1); y0 = ymin + ( ymax - ymin )*y0;
                    if (ymin <= y0 && y0 <= ymax)
                         break;
                    end
                end
                count = count + 1;
                if((y0 - (sin(x0) + x0 ^ 2 * cos(x0))) * (y0 - (2 * sin(x0) * exp(sin(x0 ^ 2)))) < 0)
                    x_fig = [x_fig x0];
                    y_fig = [y_fig y0];
                end
            end 
            plot(x_fig, y_fig, '.' , 'Color', 'g');
            y31 = sin(x) + sin(x) .^ 2; 
            y32 = cos(x) + cos(x) .^ 2;
            subplot(2, 2, 3);
            hold on
            plot(x, y31, 'color', 'red', 'linewidth', 2);
            plot(x, y32, 'color', 'blue', 'linewidth', 2);
            min_y = min(y31);
            if(min(y31) > min(y32))
                min_y = min(y32);
            end
            max_y = max(y31);
            if(max(y31) < max(y32))
                max_y = max(y32);
            end
            set(gca, 'xtick', [xmin : 1 : xmax]);
            axis([-5 5 min_y max_y]);
            grid on
            x_fig = [];
            y_fig = [];
            count = 0;
            while count < n
                while true
                    x0 = rand(1); x0 = xmin + ( xmax - xmin )*x0;
                    if (xmin <= x0 && x0 <= xmax)
                         break;
                    end
                end
                while true
                    y0 = rand(1); y0 = ymin + ( ymax - ymin )*y0;
                    if (ymin <= y0 && y0 <= ymax)
                         break;
                    end
                end
                count = count + 1;
                if((y0 - (sin(x0) + sin(x0) ^ 2)) * (y0 - (cos(x0) + cos(x0) ^ 2)) < 0)
                    x_fig = [x_fig x0];
                    y_fig = [y_fig y0];
                end
            end 
            plot(x_fig, y_fig, '.' , 'Color', 'g');
            y41 = x .^ 5 .* cos(x) .* exp(-abs(x));
            y42 = x .^ 5 .* sin(x) .* exp(-abs(x));
            subplot(2, 2, 4);
            hold on
            plot(x, y41, 'color', 'red', 'linewidth', 2);
            plot(x, y42, 'color', 'blue', 'linewidth', 2);
            min_y = min(y41);
            if(min(y41) > min(y42))
                min_y = min(y42);
            end
            max_y = max(y41);
            if(max(y41) < max(y42))
                max_y = max(y42);
            end
            set(gca, 'xtick', [xmin : 1 : xmax]);
            axis([-5 5 min_y max_y]);
            grid on
            x_fig = [];
            y_fig = [];
            count = 0;
            while count < n
                while true
                    x0 = rand(1); x0 = xmin + ( xmax - xmin )*x0;
                    if (xmin <= x0 && x0 <= xmax)
                         break;
                    end
                end
                while true
                    y0 = rand(1); y0 = ymin + ( ymax - ymin )*y0;
                    if (ymin <= y0 && y0 <= ymax)
                         break;
                    end
                end
                count = count + 1;
                if((y0 - (x0 ^ 5 * cos(x0) * exp(-abs(x0)))) * (y0 - (x0 ^ 5 * sin(x0) * exp(-abs(x0)))) < 0)
                    x_fig = [x_fig x0];
                    y_fig = [y_fig y0];
                end
            end 
            plot(x_fig, y_fig, '.' , 'Color', 'g');
    end
end