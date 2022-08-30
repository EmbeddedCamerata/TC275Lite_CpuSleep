/*
 * bsp_leds.c
 *
 *  Created on: 2022Äê7ÔÂ29ÈÕ
 *      Author: 74067
 */

#include <bsp_led_button.h>
#include "Bsp.h"
#include <scu_sleep.h>

/* This function initializes the port pin which drives the LED */
void init_GPIOs(void)
{
    IfxPort_setPinMode(LED1, IfxPort_Mode_outputPushPullGeneral);
    IfxPort_setPinMode(LED2, IfxPort_Mode_outputPushPullGeneral);
    IfxPort_setPinMode(BUTTON, IfxPort_Mode_inputPullUp);

    /* Switch OFF the LED (low-level active) */
    IfxPort_setPinState(LED1, IfxPort_State_high);
    IfxPort_setPinState(LED2, IfxPort_State_high);
}

/* This function toggles the port pin and wait 1000 milliseconds */
void led_toggle(Ifx_P *port, uint8 pinIndex)
{
    IfxPort_togglePin(port, pinIndex);
    // waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, 1000U));
}
