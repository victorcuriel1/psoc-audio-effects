clear all
close all
clc

%% Lectura del audio
[x, fs] = audioread("Recorte.wav");
t = length(x) / fs;

%% Parametros del chorus
D = 850;
alpha_chorus = 0.8;

N = length(x);
y = zeros(size(x));

%% Aplicar el efecto chorus
for n = D+1:N
    d = round(D / 2 * (1 + sin(2 * pi * 0.3 * n / fs)));
    y(n, :) = x(n, :) + alpha_chorus * x(n - d, :);
end

%% Concatenar el audio original y el audio con chorus
audio_final = [x; y];
sound(audio_final, fs);

%% Grafica del audio original y el audio con chorus
figure

subplot(2, 1, 1)
plot(x(:, 1))
title('Original')

subplot(2, 1, 2)
plot(y(:, 1))
title('Chorus Effect')
