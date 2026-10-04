clear all
close all
clc

%% Lectura del audio
[x, fs] = audioread("Recorte.wav");
t = length(x) / fs;

%% Parametros del flanger
D = 960;
f_flanger = 0.25;
alpha = 0.7;

N = length(x);
y = zeros(size(x));

%% Aplicar el efecto flanger
for n = D+1:N
    d = round(D / 2 * (1 + sin(2 * pi * f_flanger * n / fs)));
    y(n, :) = x(n, :) + alpha * x(n - d, :);
end

%% Concatenar el audio original y el audio con flanger
audio_final = [x; y];
sound(audio_final, fs);

%% Grafica del audio original y el audio con flanger
figure

subplot(2, 1, 1)
plot(x(:, 1))
title('Original')

subplot(2, 1, 2)
plot(y(:, 1))
title('Flanger Effect')
