%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Lab Number: 1
% Problem number: Lab 1.5
% Student Name: ¶ÀªÃ­Z
% Student ID: 0616098   
% Email address: maomao.08190@gmail.com
% Department: Computer Science, NCTU
% Date: 3/28
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
disp('Lab Problem 1.5'); clf; clear; clc;
fprintf('Student ID:0616098 Name:¶ÀªÃ­Z\n');
while 1
    t = 0;
    v = [0 8];
    p = [50 0]; %p is a function of time. 
    Dt = 0.05;
    M = 10000;
    m = 1;
    d = 2;
    while d > 1
        d = input('Please input d, which is in [0, 1]: ');
    end
    if(d < 0)
       break;
    else
       clf;
       for t = [0 : Dt : 100]
            F = -1 .* p ./ norm(p) .* m .* M ./ (p * p);
            a = F ./ m - d .* v;
            v = v + a .* Dt;
            p = p + v .* Dt;
            plot(p(1), p(2), '.'); hold on
       end
    end
end