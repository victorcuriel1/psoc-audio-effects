clear all
close all
clc

%% Lectura del audio
[x, fs] = audioread("Recorte.wav");
t = length(x) / fs;

%% Parametros del eco
delay1_ms = 75;
delay2_ms = 125;
alpha1 = 0.7;
alpha2 = 0.4;
offset = 2.04;

delay1 = round((delay1_ms / 1000) * fs);
delay2 = round((delay2_ms / 1000) * fs);

N = length(x);
y = zeros(size(x));

%% Aplicar el efecto eco
y(1:delay2, :) = x(1:delay2, :);

for n = delay2+1:N
    y(n, :) = x(n, :) + ...
        alpha1 * x(n - delay1, :) + ...
        alpha2 * x(n - delay2, :) + ...
        offset;
end

y = y / max(abs(y(:)));

%% Concatenar el audio original y el audio con efecto eco
audio_final = [x; y];
sound(audio_final, fs);

%% Grafica del audio original y el audio con eco
figure

subplot(2, 1, 1)
plot(x(:, 1))
title('Original')

subplot(2, 1, 2)
plot(y(:, 1))
title('Eco Effect')
