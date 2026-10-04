#include "project.h"
#include <math.h>

#define DELAY (960)
#define FREC_V 5.0
#define FS 48000.0

float buffer[DELAY] = {0};

int delay_i = 0;

float OFFSET = 2.0;

volatile uint8_t flag = 0;

CY_ISR_PROTO(Adquisicion);

int main(void) {

    ADC_DelSig_IRQ_Start();
    isr_StartEx(Adquisicion);
    ADC_DelSig_Start();
    ADC_DelSig_StartConvert();
    Opamp_Start();
    VDAC8_Start();
    isr_Enable();

    CyDelay(50);

    CyGlobalIntEnable;

    float lectura;
    float muestra_r;
    float vibrato_delay;

    int actual_delay;

    for (;;) {

        if (flag == 1) {

            lectura = ADC_DelSig_CountsTo_Volts(
                ADC_DelSig_GetResult8()
            );

            vibrato_delay =
                (DELAY / 2.0)
                * (1.0 + sinf(
                    2 * M_PI * FREC_V * delay_i / FS
                ));

            actual_delay = (int)vibrato_delay;

            int delayed_index =
                (delay_i - actual_delay + DELAY) % DELAY;

            muestra_r = buffer[delayed_index];

            float salida = muestra_r + OFFSET;

            buffer[delay_i] = lectura;

            delay_i = (delay_i + 1) % DELAY;

            if (salida >= 4.08) {
                salida = 4.08;
            }

            if (salida <= 0.0) {
                salida = 0.0;
            }

            uint8_t val =
                (uint8_t)(salida * 255.0 / 4.08);

            VDAC8_SetValue(val);

            flag = 0;
        }
    }
}

CY_ISR(Adquisicion) {
    flag = 1;
    isr_ClearPending();
}
