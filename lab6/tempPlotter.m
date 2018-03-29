%% ECE477 Lab 5
% Mason Roach
% Patrick Roy
% March 29, 2018
clear variables;
clc;

filename = "temp.csv";
fid = fopen(filename);
data = cell2table(textscan(fid, '%d%d%s', 'Delimiter' , ','));

% Column 1: ATMega88 temp 
atmegaTemp = table2array(data(1,1));
atmegaTemp = atmegaTemp{1,1};

% Column 2: I2C temp
i2cTemp = table2array(data(1,2));
i2cTemp = i2cTemp{1,1};

% Column 3: Timestamp
timeStamp = table2array(data(:,3));
timeStamp = datenum(timeStamp{1,1}, 'HH:MM:SS');

hold on;
grid on;
plot(timeStamp, atmegaTemp, timeStamp, i2cTemp);
datetick('x', 'keepticks', 'keeplimits');
title('ATMega Temperature Logger');
xlabel('Time past start, HH:MM:SS');
ylabel('Temperature, degrees Celsius');
legend('ATMega88', 'TC74a0');