%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Assignment Number: Lab6
% Problem number: 2
% Student Name:  ¶ÀªÃ­Z
% Student ID: 0616098
% Email address: maomao.08190@gmail.com
% Department: Computer Science, NCTU
% Date: 6/7
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% close all windows
% clear variables, and clear screen
close all; clf; clear; clc;

% show Lab Problem 6.2
disp('Lab Problem 6.2')  

while 1
    n = input('Please input the number of samples of X, n: ');
    %n is inside [0, 1000000].
    if n == 0
        disp('Thanks for playing');
        return;
    else
        a = input('Please input the number a: ');
        b = input('Please input the number b: ');
        c = input('Please input the number c: ');
        if a * b <= 0 || a * c <= 0
            disp("the values are invalid");
            return;
        else
            clf;
            Y = rand(n, 1);
            a = double(a);
            b = double(b);
            c = double(c);
            X = a .* Y .^ 2 + b .* Y + c;
            H = histogram(X, 'Normalization','pdf');
            hold on
            %axis manual
            syms x; syms y;
            answer = solve(a * y ^ 2 + b * y + c == x, y);
            %z = min(X) : (max(X) - min(X)) / n : max(X);
            if a > 0
                %F = (-b + sqrt(b .^ 2 - 4 .* a .* c + 4 .* a .* z)) ./ (2 * a);
                %f_value = 2 .* a .^ (1 / 2 - 1) .* (b .^ 2 - 4 .* a .* c + 4 .* a .* z) .^ (1 / 2 - 1);
                f = diff(answer(2));
            else
                %F = (-b + sqrt(b .^ 2 - 4 .* a .* c + 4 .* a .* z)) ./ (2 * a);
                %f_value = -1 .* 2 .* a .^ (1 / 2 - 1) .* (-(b .^ 2 - 4 .* a .* c + 4 .* a .* z)) .^ (1 / 2 - 1);
                f = diff(answer(1));
            end 
            %idx = 1;
            %for i = z
            %    f_value(idx) = subs(f, i);
            %    idx = idx + 1;
            %end
            %ezplot
            fplot(f, [min(X), max(X)], 'LineWidth', 3);
            %plot(z, f_value, 'LineWidth', 2);
            title(['M=', num2str(mean(X)), '; SD=', num2str(std(X)),...
                '; a=', num2str(a), '; b=', num2str(b), '; c=', num2str(c)]);
            z = max(X) : -(max(X) - min(X)) / 1000 : min(X);
            fig = plot(max(X), subs(f, max(X)), "o");
            for i = z
                delete(fig);
                fig = plot(i, subs(f, i), 'ko', 'LineWidth', 3);
                pause(0.033);
            end
        end
    end
end