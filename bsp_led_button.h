/*
 * bsp_leds.h
 *
 *  Created on: 2022Äê7ÔÂ29ÈÕ
 *      Author: 74067
 */

#ifndef BSP_LED_BUTTON_H_
#define BSP_LED_BUTTON_H_

#include "IfxPort.h"
#include "Ifx_Types.h"

#define LED1         &MODULE_P00,5
#define LED2         &MODULE_P00,6
#define BUTTON       &MODULE_P00,7

void init_GPIOs(void);
void led_toggle(Ifx_P *port, uint8 pinIndex);

#endif /* BSP_LED_BUTTON_H_ */
