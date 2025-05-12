% Exponential fit

xData = [1, 2, 5, 10, 15, 20, 25, 50]; % Input sizes
yData = [0.00002, 0.000003, 0.000028, 0.001911, 0.112411, 5.938734, 287.409284, 10000]; % Runtimes

% Log-transform of yData for linear fitting
logYData = log(yData);
n = length(xData);

% Linear regression on log(y) = log(C) + A*x
sumX = sum(xData);
sumY = sum(logYData);
sumX2 = sum(xData.^2);
sumXY = sum(xData .* logYData);

% Calculate coefficients
A = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX^2);
lnC = (sumY - A * sumX) / n;
C = exp(lnC);

% Generate smooth x values for plotting the curve
xFit = linspace(min(xData), max(xData), 200);
yFit = C * exp(A * xFit);  % Exponential model

% Plot results
figure;
semilogy(xData, yData, 'bo', 'MarkerFaceColor', 'b'); % Data points
hold on;
semilogy(xFit, yFit, 'r-', 'LineWidth', 2); % Fitted exponential curve

% Horizontal line at y = 3600
semilogy([min(xFit), max(xFit)], [3600, 3600], 'k--');
text(max(xFit)*0.9, 3600*1.2, '1 hour', 'FontSize', 10);

% Fitting formula annotation
text(min(xFit)*1.05, max(yData)/10, ...
    sprintf('Fit: t = %.2e × e^{%.2f×n}', C, A), ...
    'FontSize', 10, 'Color', 'k');

% Labels and grid
grid on;
xlabel('Problem Size (n)');
ylabel('Runtime (seconds)');
title('Exponential Fit of TSP Held-Karp Algorithm Runtime');
legend('Measured Data', 'Exponential Fit', 'y = 3600');

