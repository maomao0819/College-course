%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Lab Number: 1
% Problem number: Lab 1.4
% Student Name: ¶ÀªÃ­Z
% Student ID: 0616098   
% Email address: maomao.08190@gmail.com
% Department: Computer Science, NCTU
% Date: 3/28
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
disp('Lab Problem 1.4'); clf; clear; clc;
fprintf('Student ID:0616098 Name:¶ÀªÃ­Z\n');
a = input('Please input the number a:');
dx = -1;
while dx < 0;
    dx = input('Please input the step size dx of x (dx must be a non-negative value): ');
end
x = [-10 : dx : 10];
y = (2 .* x .^ 2 + 3 .* exp(-1 .* x) - (100 * a) .* sin(5 .* x)) ./ (6 .* x .^ 2 - 9 .* x - 42) - 10; 
s = size(x);
i = 1;
sig = s(i)>=0;		% sign
x1 = [];
y1 = [];			
while i <= s(2)	% number of samples
    sig0 = y(i) >= 0;
    if (sig0 == sig)	% same sign
        x1 = [x1, x(i)];	% collect x-coordinate
        y1 = [y1, y(i)];   % collect y-coordinate
    else		%not same sign
        if (sig == 1)
            color = 'blue';
        else
            color = 'red';
        end
        plot(x1, y1, 'color', color); hold on
        ylim([-100, 100]);
        x1 = [];
        y1 = [];
        x1 = [x1, x(i)];	
        y1 = [y1, y(i)];
        sig = sig0;
    end 
    i = i + 1;
end
if (sig == 1)
    color = 'blue';
else
	color = 'red';
end
plot(x1, y1, 'color', color);
ylim([-100, 100]);
