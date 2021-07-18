%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Midterm Number: Two
% Problem number: 1
% Student Name: ¶ÀªÃ­Z
% Student ID: 0616098
% Email address: maomao.08190@gmail.com
% Department: CS
% Date: 5/23
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% close all windows
% clear variables, and clear screen
close all; clf; clear; clc;

% show Midterm Two Problem 1
disp('Midterm Two Problem 1')

%Galaxy
clear;
nmax = 300;
n = input('Enter the number of particles [0,300]:');
while true
    if ( n == 0)
        disp('Student ID:0616098');
        disp('Thanks for playing');
        return;
    end
    if (1 <= n && n <= nmax)
        fprintf('This system generates %d particles. Enjoy the simulation.', n);
        break;
    end
end
if (1 <= n && n <= nmax)
    P = zeros(n ,2);        % position of free particles
    V = zeros(n, 2);        % velocities of free particles

    % generate the free particles
    rmin = 10;
    rmax = 50;
    nc = 0;
    xmax = 80;
    xmin = -80;
    ymax = 80;
    ymin = -80;
    while nc < n
        x0 = rand(1); x0 = xmin + (xmax - xmin) * x0;
        y0 = rand(1); y0 = xmin + (ymax - ymin) * y0;
        r0 = sqrt(x0 ^ 2 + y0 ^ 2);
        if (rmin <= r0 && r0 <= rmax)
            nc = nc + 1;
            P(nc,1:2) = [x0 y0];
        end
    end

    %set the velocities of particles orthogonal to p - [0 0]
    %the speed is 20.
    s = 20;
    for k = 1:n
        p = P(k, 1:2);
        V(k, 1:2) = s .* [p(2) -p(1)] ./ sqrt(p * p');
        if(rand(1) <= 0.5)
            V(k, 1:2) = V(k, 1:2) .* -1; 
        end    
    end

    m = 1;
    M = 10000;
    t0 = 0;
    dt = 0.025;     % time step size
    t = t0;         % time
    plot(0, 0, '.');
    while(true)
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        %insert your own stuff
        %color interpolation
        cp0 = [0 0 1];  %blue
        cp1 = [1 0 0]; % red
        %update galaxy system
        for idx = 1 : n
            p = P(idx, 1:2);
            v = V(idx, 1:2);
            F = -p .* m .* M ./ (sqrt(p * p') * (1 + p * p'));
            a = F ./ m;
            v = v + a .* dt;
            p = p + v .* dt;
            P(idx, 1:2) = p;
            V(idx, 1:2) = v;
            %show particles
            d = sqrt(p * p');
            vD = min(1, d / 50);
            particle_color = cp0 + vD * (cp1 - cp0);
            pbaspect([ 1 1 1])
            plot(p(1), p(2), 'o', 'color', particle_color);
            axis([-80 80 -80 80]);
            pbaspect([ 1 1 1])
            hold on
        end
        t = t + dt;
        %plot(P(1), P(2), '.');
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        axis([-80 80 -80 80]);
        pbaspect([ 1 1 1])
        pause(0.000001);
        clf;
    end
end
