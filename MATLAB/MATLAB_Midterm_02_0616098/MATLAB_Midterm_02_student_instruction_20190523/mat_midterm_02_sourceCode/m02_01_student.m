%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Midterm Number: Two
% Problem number: 1
% Student Name: Ping-MAo Huang
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
    if ( n ==0)
        disp('Student ID??????');
        disp('Thanks for playing');
        return;
    end
    if (1 <= n && n<=nmax)
        break;
    end
end

P = zeros(n,2);         % position of free particles
V = zeros(n, 2);        % velocities of free particles

% generate the free particles
rmin = 10;
rmax = 50;
nc = 0;
while nc < n
    
    %if (rmin<=r0 && r0<=rmax)
        nc = nc + 1;
    %    P(nc,1:2) = [x0 y0];
    %end
end

%set the velocities of particles orthogonal to p - [0 0]
%the speed is 20.
for k = 1:n
    
end

m = 1;
M = 10000;
t0 = 0;
dt = 0.025;     % time step size
t = t0;         % time

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%insert your own stuff
%update galaxy system
%show particles
%color interpolation
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
axis([-80 80 -80 80]);
pbaspect([ 1 1 1])
pause(0.033);
end
