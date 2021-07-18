%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Final Exam Number: 1
% Problem number: 1
% Student Name: ¶ÀªÃ­Z
% Student ID: 0616098
% Email address: maomao.08190@gmail.com
% Department: CS
% Date: 2019/06/13
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

close all; clear; clc;		% close all windows
                            % clear variables, and clear screen

disp('Final Exam Problem 1.1') 	% show Problem Number

disp('Student Name:¶ÀªÃ­Z');
disp('Student ID:0616098');
gray_op = input("Do you want to show the tail of the free particle (yes/no)? yes ... 1 / no ... 0  ");
form_op = input("Which format to be used for showing the systems? 1) 1x2 2) 2x1 ");
G = 47.3;
m = 1;
r1 = 50;
r2 = 200;
%Setting One
s1w1 = 0.5; 
s1w2 = 0.5; 
s1M1 = 13900; 
s1M2 = 19900;
%Setting Two
s2w1 = 0.8; 
s2w2 = 0.8;
s2M1 = 15500;  
s2M2 = 16000;
if(form_op == 1)
    t = 1;
    while(t)
        s1x1 = r1 .* cos(s1w1 .* t);
        s1y1 = r1 .* sin(s1w1 .* t);
        s1x2 = r2 .* cos(s1w2 .* t);
        s1y2 = r2 .* sin(s1w2 .* t);
        s2x1 = r1 .* cos(s2w1 .* t);
        s2y1 = r1 .* sin(s2w1 .* t);
        s2x2 = r2 .* cos(s2w2 .* t);
        s2y2 = r2 .* sin(s2w2 .* t);
        clf;
        subplot(1, 2, 1)
        hold on
        plot(s1x1, s1y1, 'ro')
        plot(s1x2, s1y2, 'bo')
        w = 400;
        axis([-w w -w w]);
        pbaspect([1 1 1]);
        subplot(1, 2, 2)
        hold on
        plot(s2x1, s2y1, 'ro')
        plot(s2x2, s2y2, 'bo')
        axis([-w w -w w]);
        pbaspect([1 1 1]);
        pause(0.001)
        t = t + 1;
    end
end
if(form_op == 2)
    t = 1;
    while(t)
        s1x1 = r1 .* cos(s1w1 .* t);
        s1y1 = r1 .* sin(s1w1 .* t);
        s1x2 = r2 .* cos(s1w2 .* t);
        s1y2 = r2 .* sin(s1w2 .* t);
        s2x1 = r1 .* cos(s2w1 .* t);
        s2y1 = r1 .* sin(s2w1 .* t);
        s2x2 = r2 .* cos(s2w2 .* t);
        s2y2 = r2 .* sin(s2w2 .* t);
        clf;
        subplot(2, 1, 1)
        hold on
        plot(s1x1, s1y1, 'ro')
        plot(s1x2, s1y2, 'bo')
        w = 400;
        axis([-w w -w w]);
        pbaspect([1 1 1]);
        subplot(2, 1, 2)
        hold on
        plot(s2x1, s2y1, 'ro')
        plot(s2x2, s2y2, 'bo')
        axis([-w w -w w]);
        pbaspect([1 1 1]);
        pause(0.001)
        t = t + 1;
    end
end
%F = -()
md = 10;
pq = p-q0;
if (norm(pq) < md)
          p = q0 + pq ./ norm(pq) .* md;
end
maxv = 500;
if (norm(v) > maxv)
          v = v ./ norm(v) .* maxv;
end

