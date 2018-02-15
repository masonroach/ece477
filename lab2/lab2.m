%% ECE 477 Lab 2
% Mason Roach
% Patrick Roy
% This matlab file will read the contents of
% 'database.csv' produced by lab2 and produce various plots
clear variables;
clc;

%% Read data from csv file
data = readtable('database.csv');

% Convert table values to array values
index = table2array(data(:,1));
freeMemkB = table2array(data(:,2));
loadAvg1min = table2array(data(:,3));
loadAvg5min = table2array(data(:,4));
loadAvg15min = table2array(data(:,5));
runningProcesses = table2array(data(:,6));
totalProcesses = table2array(data(:,7));
times = datetime(table2array(data(:,8)), 'InputFormat', 'MM-dd-yyyy HH:mm:ss');
machine = table2array(data(1,9));

%% Plot Data
figure(1);

% Memory and Processes
subplot(2,1,1);
yyaxis left;
plot(index, freeMemkB);
ylabel('Free Memory (kB)');

yyaxis right;
plot(index, totalProcesses);
ylabel('Total Processes');
grid on;
xlim([1 length(index)]);
xlabel('Sample Index');
title(machine);


% Memory and load times
subplot(2,1,2);
yyaxis left;
plot(index, freeMemkB);
ylabel('Free Memory (kB)');

yyaxis right;
% Load averages
hold on;
plot(index, loadAvg1min, '--r');
plot(index, loadAvg5min, '--b');
plot(index, loadAvg15min, '--g');

ylabel('Load Averages');
xlabel('Sample Index');
legend('Free Memory (kB)', '1 min avg', '5 min avg', '15 min avg');
grid on;
xlim([1 length(index)]);
title(machine);