%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Final Exam Number: 2
% Problem number: 2
% Student Name:  ¶ÀªÃ­Z
% Student ID: 0616098
% Email address: maomao.08190@gmail.com
% Department: Computer Science, NCTU
% Date: 2019/06/20
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

close all; clear; clc;		% close all windows
% clear variables, and clear screen

disp('Final Exam Problem 2.2') 	% show Problem Number

disp('Student Name:¶ÀªÃ­Z');
disp('Student ID:0616098');

disp('Option 1) Function Graph');
disp('Option 2) Fractal');
option = input('Input:');

if option==1
    syms a;
    syms b;
    g11 = sym(a+b);
    g12 = sym(a-b);
    %
    g21 = sym(sin(a)./(cos(b).*cos(b)+1));
    g22 = sym(a.*b);
    g23 = sym(a+b);
    g24 = sym(b-a);
    
    g31 = sym(exp(-(a + b) .* (a + b)));
    g32 = sym(a-b);
    g33 = sym(sin(a) + cos(b));
    g34 = sym(cos(b) ./(abs(a) + 1));
    
    g41 = sym(cos(a) + sin(b));
    g42 = sym(cos(b) + sin(a));
    
    g51 = sym(b.*sin(a));
    
    dx = 0.05;
    dy = 0.05;
    x = -1.5:dx:1.5;
    y = -1.5:dy:1.5;
    
    [X Y] = meshgrid(x,y);
    
    k11 = subs(g11, {a, b},{X, Y});	% result of g11(X,Y)
    k12 = subs(g12, {a, b},{X, Y});
    k21 = subs(g21, {a, b},{k11, k12});
    k22 = subs(g22, {a, b},{k11, k12});
    k23 = subs(g23, {a, b},{k11, k12});
    k24 = subs(g24, {a, b},{k11, k12});
    k31 = subs(g31, {a, b},{k21, k22});
    k32 = subs(g32, {a, b},{k21, k22});
    k33 = subs(g33, {a, b},{k23, k24});
    k34 = subs(g34, {a, b},{k23, k24});
    k41 = subs(g41, {a, b},{k32, k31});
    k42 = subs(g42, {a, b},{k33, k34});
    Z = subs(g51, {a, b},{k41, k42});
    meshz(X, Y, Z);
    
    return;
end

if option==2
    arg1 = 120;  arg2 = 350;
    julia(arg1, arg2)
    %K1 = 1-0.5.*K;
    I = imread('tmp.png');
    I = im2double(I);
    s = size(I);
    h = s(1);
    w = s(2);
    imshow(I);
    return;
end