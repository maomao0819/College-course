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

% show Lab Two Problem 1
disp('Lab Two Problem 1')  

%initial
t = 0;
v1 = [15 20];
p1 = [0 0];
v2 = [15 20];
p2 = [0 0];
dt = 0.02;
m = 1;
g = 2;
n = [0 -1];
tmax = 100;

% input
while true
    d = input('Please input d: ');
    if (d(1) < 0 || d(2) < 0) 
        return;
    end
    if (d(1) <= 1 && d(2) <= 1) 
        break;
    end    
end

figure;
grid
px1 = [];
py1 = [];
px2 = [];
py2 = [];
% drawing
while (t <= tmax) 
    clf;
    F = m .* g .* n;
    a1 = F ./ m - d(1) .* v1;
    v1 = v1 + a1 .* dt;
    p1 = p1 + v1 .* dt;
    px1 = [px1 p1(1)];
    py1 = [py1 p1(2)];
    subplot(1,2,1), plot(px1, py1); hold on 
    viscircles([p1(1) p1(2)], 1, 'color', 'b');
    axis([0 400 -100 100]);
    a2 = F ./ m - d(2) .* v2;
    v2 = v2 + a2 .* dt;
    p2 = p2 + v2 .* dt;
    px2 = [px2 p2(1)];
    py2 = [py2 p2(2)];
    subplot(1,2,2), plot(px2, py2); 
    viscircles([p2(1) p2(2)], 1, 'color', 'b'); 
    axis([0 400 -100 100]);
    t = t + dt;
    pause(dt);
end

