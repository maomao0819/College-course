%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Assignment Number: 1
% Student Name: ¶ÀªÃ­Z
% Student ID: 0616098   
% Email address: maomao.08190@gmail.com
% Department: Computer Science, NCTU
% Date: 3/9
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
disp('Problem 1.1'); clf; clear; clc;
n = 8;
P = [-n : 2 : n]
clear; clc; disp('Problem 1.2'); clf;  
n = [-3 : 3];
z = meshgrid(n .^ n)
disp('Problem 1.3'); clf; clear; clc;
n = 10;
a = [0:n - 1];
b = zeros(1, 10) - 1;
X = b .^ a
disp('Problem 1.4'); clf; clear; clc;
n = 10;
bitand(1, 0:n-1) + 1
%[1:n] - reshape( repmat( [0:n / 2 - 1], 2, 1 ), 1, [] ) .*2
disp('Problem 1.5'); clf; clear; clc;
n = 10;
X = mod(0 : n-1, 3) + 1
disp('Problem 2.1'); clf; clear; clc;
[x y] = meshgrid(-8:8);
z = y*sin(x);
surf (z), shading faceted
% Try other shading methods: flat, interp
disp('Problem 2.2'); clf; clear; clc;
x = [0 : 0.01 : 4];
y = x;
plot(x, y); hold on
y = x .^ 2;
plot(x, y);
y = x .^3;
plot(x, y);
y = exp(x);
plot(x, y);
y = exp(-1 .* x);
plot(x, y);
y = log(x);
plot(x, y);
% You can use clf to clear all figures.
% plot(x,y); (label)
disp('Problem 2.3'); clf; clear; clc;
x = [-10 : 0.001 : 10];
y = sin(x) - x;
z = sin((y .^ 2)) - exp(x) ./ x;
plot(x,z); hold on
x = [-10 : 0.5 : 10];
y = sin(x) - x;
z = sin((y .^ 2)) - exp(x) ./ x;
plot(x,z,'o')
disp('Problem 2.4'); clf; clear; clc;
[x y]=meshgrid(-10 : 0.5 : 10);
z = (x + y) ./ (x .^ 2 + y .^ 2 + 1);
meshc(x, y, z); %shading faceted
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% [x y]=meshgrid(-10 : 0.01 : 10);
% z = (x + y) ./ (x .^ 2 + y .^ 2 + 1);
% meshc(x, y, z);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
disp('Problem 2.5'); clf; clear; clc;
x = [-10 : 0.05 : 10];
y = 0.5 + (x .* sin(x)) ./ ( x .^ 2 .* exp(sin(x)) + 1);
plot(x, y); hold on
y = cos(x) .^ 2 + sin(x) .^ 2;
plot(x, y)
% You can use size(x, 2) to get the number of columns of x.