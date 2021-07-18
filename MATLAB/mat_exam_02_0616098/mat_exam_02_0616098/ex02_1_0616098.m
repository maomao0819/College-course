%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Final Exam Number: 2
% Problem number: 1
% Student Name:  ¶ÀªÃ­Z
% Student ID: 0616098
% Email address: maomao.08190@gmail.com
% Department: Computer Science, NCTU
% Date: 2019/06/20
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

close all; clear; clc;		% close all windows
                            % clear variables, and clear screen

disp('Final Exam Problem 2.1') 	% show Problem Number

disp('Student Name:¶ÀªÃ­Z');
disp('Student ID:0616098');


while 1
    n = input('Please input the number of samples of X, n: ');
    %n is inside [0, 2000000].
    if n == 0
        disp('Thanks for playing');
        return;
    else
        a = input('Please input the number a: ');
        b = input('Please input the number b: ');
        while a < 0.1 || a > 1 || abs(b) > 1 || abs(b) < 0.1
            disp("the values are invalid");
            a = input('Please input the number a: ');
            b = input('Please input the number b: ');
        end
            clf;
            Y = rand(n, 1);
            a = double(a);
            b = double(b);
            subplot(1, 2, 1)
                H1 = histogram(Y, 'Normalization','pdf');
                hold on 
                x1 = 0 : 0.01 : 1;
                size_x1 = size(x1);
                y1 = ones(size_x1(2));
                plot(x1, y1, 'r', 'LineWidth', 3);
                title(['Mean=', num2str(mean(Y)), '; SD=', num2str(std(Y)),...
                    '; a=', num2str(a), '; b=', num2str(b)]);
            subplot(1, 2, 2)
                X = b .* sin(pi ./ 2 .* a .* Y .^ 2);
                H2 = histogram(X, 'Normalization','pdf');
                hold on 
                %axis manual
                syms x; syms y;
                answer = solve(b * sin(pi / 2 * a * y ^ 2) == x, y);
                %z = min(X) : (max(X) - min(X)) / n : max(X);
                if b > 0
                    f = diff(answer(2));
                else
                    f = diff(answer(4));
                end 
                fplot(f, [min(X), max(X)], 'LineWidth', 3);
                ylim([0, 50]);
                title(['Mean=', num2str(mean(X)), '; SD=', num2str(std(X)),...
                    '; a=', num2str(a), '; b=', num2str(b)]);
                if(b < 0)
                    while(1)
                        z = max(X) : -(max(X) - min(X)) / 1000 : min(X);
                        fig = plot(max(X), subs(f, max(X)), "o");
                    subplot(1, 2, 1)
                        fig2 = plot(min(Y), 1, "o");
                        idx = 0;
                        for i = z
                            delete(fig);
                            delete(fig2);
                            subplot(1, 2, 2)
                                fig = plot(i, subs(f, i), 'yo', 'LineWidth', 3);
                            subplot(1, 2, 1)
                                idx = idx + 0.001;
                                fig2 = plot(idx, 1, 'yo', 'LineWidth', 3);
                            pause(0.033);
                        end
                        delete(fig);
                        delete(fig2);
                    end
                else
                    while(1)
                        z = min(X) : (max(X) - min(X)) / 1000 : max(X);
                        fig = plot(min(X), subs(f, min(X)), "o");
                    subplot(1, 2, 1)
                        fig2 = plot(min(Y), 1, "o");
                        idx = 0;
                        for i = z
                            delete(fig);
                            delete(fig2);
                            subplot(1, 2, 2)
                                fig = plot(i, subs(f, i), 'yo', 'LineWidth', 3);
                            subplot(1, 2, 1)
                                idx = idx + 0.001;
                                fig2 = plot(idx, 1, 'yo', 'LineWidth', 3);
                            pause(0.033);
                        end
                        delete(fig);
                        delete(fig2);
                    end
                end
    end
end