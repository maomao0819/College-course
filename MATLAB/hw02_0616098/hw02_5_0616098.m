%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Assignment Number: 2
% Problem number: 5
% Student Name: ¶ÀªÃ­Z
% Student ID: 0616098   
% Email address: maomao.08190@gmail.com
% Department: Computer Science, NCTU
% Date: 3/28
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

disp('Problem 5'); clf; clear; clc;
fprintf('Student ID:0616098 Name:¶ÀªÃ­Z\n');
v = 0;
p = 0; %p is a function of time. 
Dt = 0.02;
clf;
d = input('Please input d(, which is in [0, 1]): ');
A = [];
t_A = [0 : Dt : 10];
for k = 0 : 0.1 : 1
    for t = 0 : Dt : 10;
        v = v + k * sin(t) * Dt - d * v;
        p = p + v * Dt;
        A = [A, p];
    end
    plot(t_A, A); hold on
    v = 0;
    p = 0; 
    A = [];
end