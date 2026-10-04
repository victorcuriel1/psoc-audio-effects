# Efectos de Audio con PSoC 5LP

Proyecto de Procesamiento Digital de Señales orientado al desarrollo e implementación de efectos de audio utilizando un microcontrolador PSoC 5LP.

El sistema procesa una señal de audio en tiempo real mediante conversión analógico-digital, procesamiento digital y posterior reconstrucción analógica.

Los efectos implementados fueron:

- Echo
- Flanger
- Chorus
- Vibrato

## Tecnologías utilizadas

- PSoC 5LP
- PSoC Creator
- MATLAB
- C
- Procesamiento Digital de Señales
- ADC y DAC
- Filtros FIR e IIR
- Filtros analógicos

## Funcionamiento

La señal de audio de entrada pasa inicialmente por un filtro antialiasing antes de ser digitalizada mediante el ADC del PSoC.

Luego se aplica el algoritmo correspondiente al efecto seleccionado y la señal procesada es convertida nuevamente a formato analógico mediante el DAC.

Finalmente, un filtro de reconstrucción acondiciona la señal de salida.

Flujo general:

`Audio → Filtro Antialiasing → ADC → Procesamiento DSP → DAC → Filtro de Reconstrucción`

## Efectos implementados

### Echo

Genera copias retardadas de la señal original utilizando dos retardos con diferentes niveles de atenuación.

### Flanger

Combina la señal original con una versión retardada y modulada para generar variaciones periódicas en el sonido.

### Chorus

Combina la señal original con una copia retardada para simular la presencia de múltiples fuentes de audio.

### Vibrato

Utiliza un retardo variable controlado mediante modulación sinusoidal para producir variaciones periódicas en el tono.

## MATLAB

Los algoritmos fueron inicialmente desarrollados y evaluados en MATLAB.

Los archivos se encuentran en:

`matlab/`

## PSoC

Posteriormente, los efectos fueron implementados en el PSoC 5LP utilizando el ADC, el DAC y procesamiento en tiempo real.

Los archivos se encuentran en:

`psoc/`

## Filtrado analógico

El sistema incorpora filtros pasa bajos de segundo orden utilizados tanto como filtro antialiasing como filtro de reconstrucción.

Se utilizó una frecuencia de corte aproximada de 20 kHz.

## Documentación

El informe completo del proyecto está disponible aquí:

[Ver informe del proyecto](docs/Project_Report.pdf)

## Autores

- Victor Gabriel Curiel Gonzalez
- Ximena Lujan Quenhan Riveros

Universidad Nacional de Asunción  
Facultad de Ingeniería  
Ingeniería Mecatrónica

## Licencia

Este proyecto está distribuido bajo la licencia MIT.
