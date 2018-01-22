load('data_degree.mat');
load('data_probh.mat');
load('data_probv.mat');

degrees = Simulation_x(1:end);
probx = Simulation_probH(1:end);
proby = Simulation_probV(1:end);

fitresult = spline(degrees, proby);

figure(1);
plot(degrees,probx,'o');
title('Probability of a single photon be detected by the detector in Vertical axis.')
xlabel('Single Photon Polarization angle (Degrees)');
ylabel('Probability of 1')
hold on;
