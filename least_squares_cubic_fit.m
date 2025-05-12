% Cubic Fit Using Least Squares Method

xData = [20, 25, 26, 35, 50, 100, 200];
yData = [0.001, 0.001, 0.002, 0.005, 0.015, 0.110, 1.029];
xPlot = linspace(0, 4000, 100);
n = length(xData);


% Build design matrix for cubic: [x^3, x^2, x, 1]
X = [xData'.^3, xData'.^2, xData', ones(n, 1)];

% Least squares solution
coefficients = (X' * X) \ (X' * yData');

% Extract coefficients
a = coefficients(1);
b = coefficients(2);
c = coefficients(3);
d = coefficients(4);

% Define cubic function
f = @(x) a*x.^3 + b*x.^2 + c*x + d;

% Evaluate fit
yPlot = f(xPlot);

% Plot results
figure;
plot(xData, yData, 'ko', 'MarkerFaceColor', 'b'); % Data points
hold on;
plot(xPlot, yPlot, 'r-', 'LineWidth', 2);         % Cubic Fit
y_3600 = ones(1, length(xPlot)) * 3600;
plot(xPlot, y_3600, 'g--', 'LineWidth', 1.5);  % Horizontal line at y = 3600
xlabel('x');
ylabel('y');
title('Cubic Fit using Least Squares');
legend('Data Points', 'Cubic Fit');
grid on;
