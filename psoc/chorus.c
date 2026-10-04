#include "project.h"
#include <math.h>
#include <stdbool.h>

#define RETARDO 850
#define F_MUESTREO 44100.0
#define OFFSET 2.04

float y;

float alpha = 0.8;

float y_delayed[RETARDO] = {0};

int delay_i = 0;

volatile uint8_t flag = 0;

CY_ISR_PROTO(Adquisicion);

int main(void) {

    ADC_DelSig_IRQ_Start();
    isr_StartEx(Adquisicion);
    ADC_DelSig_Start();
    ADC_DelSig_StartConvert();
    Opamp_ADC_Start();
    VDAC8_Start();
    isr_Enable();

    CyDelay(50);

    CyGlobalIntEnable;

    float t = 0;
    float delta_t = 1.0 / F_MUESTREO;

    for (;;) {

        float valor = ADC_DelSig_CountsTo_Volts(
            ADC_DelSig_GetResult8()
        );

        y = valor
            + 1.5 * alpha * y_delayed[delay_i]
            + OFFSET;

        y_delayed[delay_i] = valor;

        delay_i = (delay_i + 1) % RETARDO;

        if (y > 4.08)
            y = 4.08;

        if (y < 0.0)
            y = 0.0;

        uint8_t val = (uint8_t)(y * 255.0 / 4.08);

        VDAC8_SetValue(val);

        flag = 0;
    }
}

CY_ISR(Adquisicion) {
    flag = 1;
    isr_ClearPending();
}
