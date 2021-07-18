%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Assignment Number: Lab Two
% Problem number: 1
% Student Name:  ¶ÀªÃ­Z
% Student ID: 0616098  
% Email address: maomao.08190@gmail.com
% Department: Computer Science, NCTU
% Date: 4/29
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% close all windows
% clear variables, and clear screen
close all; clf; clear; clc;

% show Lab Two Example
disp('Lab Two Example')  

t = 0;
tmax = 100;

grid
a = [-0.5 -1.5];
p = [0 0];
v = [15 10];
dt = 0.05;
while true
    d = input('Please input d:');
    if (d<0) 
        return;
    end
    if (d<=1) 
        break;
    end    
end
figure
while (t<=tmax) 
    clf
    v = v + a*t - d*v;
    p = p + v*t;
    t = t + dt;
    viscircles([p(1) p(2)], 1, 'color', 'b');
    axis([-100 100 -100 100]);
    pause(0.05);
end