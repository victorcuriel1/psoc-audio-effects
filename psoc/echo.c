#include "project.h"

#define RETARDO_1 3600
#define RETARDO_2 6000

float y;
float entrada = 0.0;

float x_delayed_1[RETARDO_1] = {0};
float x_delayed_2[RETARDO_2] = {0};

int retardo_index_1 = 0;
int retardo_index_2 = 0;

float OFFSET = 2.04;

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

            y = entrada
                + 0.7 * x_delayed_1[retardo_index_1]
                + 0.4 * x_delayed_2[retardo_index_2]
                + OFFSET;

            x_delayed_1[retardo_index_1] = entrada;
            x_delayed_2[retardo_index_2] = entrada;

            retardo_index_1++;
            retardo_index_2++;

            if (retardo_index_1 >= RETARDO_1) {
                retardo_index_1 = 0;
            }

            if (retardo_index_2 >= RETARDO_2) {
                retardo_index_2 = 0;
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
