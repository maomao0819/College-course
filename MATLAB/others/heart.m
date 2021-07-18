range = sqrt(3.3);
x=[-range : 0.005: range];
for a = 0 : 0.1 : 100
    clf;
    y=(x .^ 2) .^ (1 / 3) + 0.9 .* ((3.3 - x .^ 2) .^ 0.5) .* (sin(a .* pi .* x));
    plot(x ,y);
    clear y;
    grid;
    axis([-5 5 -5 5]);
    pause(0.05);
end