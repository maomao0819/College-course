%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Final Exam Number: 1
% Problem number: 2
% Student Name: ¶ÀªÃ­Z
% Student ID: 0616098
% Email address: maomao.08190@gmail.com
% Department: CS
% Date: 2019/06/13
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

close all; clear; clc;		% close all windows
                            % clear variables, and clear screen

disp('Final Exam Problem 1.2') 	% show Problem Number

disp('Student Name:¶ÀªÃ­Z');
disp('Student ID:0616098');
disp('Menu');
disp('Option 1)');
disp('Option 2)');
disp('Option 3)');
op = input("Please enter the option: ");
if(op == 1)
    while(1)
        for w = [20 : -1 : 0 0 : 1 : 50 50 : -1 : 20]
            clf;
            am = w / 10;
            x = -10 : 0.1 : 10;
            y = sin(x);
            lw = [1 : 6  6 : -1 : 1]
            for c = 0 : 11
                plot(x, (-1) ^ c .* y .* am + c, 'linewidth', lw(c + 1));
                hold on
                axis([-10 10 -5 15]);
            end
        pause(0.000001);
        end
    end
elseif(op == 2)
    while(1)
        for w = [5 : -0.1 : 0  0 : 0.1 : 5]
            clf;
            am = w / 10;
            x = -10 : 0.1 : 10;
            y = sin (x.* (1 + w));
            lw = [1 : 6  6 : -1 : 1]
            for c = 0 : 11
                plot(x, (-1) ^ c .* y .* am + c, 'linewidth', lw(c + 1));
                hold on
                axis([-10 10 -5 15]);
            end
        pause(0.000001);
        end
    end
elseif(op == 3)
    I = imread('tmp.png');
    I = im2double(I);
    I1 = imresize(I,[640 640]);
end