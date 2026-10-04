#include "project.h"
#include <math.h>

#define RETRASO (480)

float y;
float entrada = 0.0;

float x_delayed[RETRASO] = {0};

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

    for (;;) {

        if (flag == 1) {

            entrada = ADC_DelSig_CountsTo_Volts(
                ADC_DelSig_GetResult8()
            );

            float cos_term =
                0.7 * cos(2 * M_PI * 0.45 * delay_i / 480.0);

            y = entrada
                + 0.9 * entrada * cos_term
                + x_delayed[delay_i]
                + OFFSET;

            x_delayed[delay_i] = entrada;

            delay_i++;

            if (delay_i >= RETRASO) {
                delay_i = 0;
            }

            if (y >= 4.08) {
                y = 4.08;
            }

            if (y <= 0.0) {
                y = 0.0;
            }

            uint8_t val = (uint8_t)(y * 255.0 / 4.08);

            VDAC8_SetValue(val);

            flag = 0;
        }
    }
}

CY_ISR_PROTO(Adquisicion) {
    flag = 1;
    isr_ClearPending();
}
