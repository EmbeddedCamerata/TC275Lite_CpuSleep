/*
 * bsp_uart.h
 *
 *  Created on: 2022Äê8ÔÂ16ÈÕ
 *      Author: 74067
 */

#ifndef BSP_UART_H_
#define BSP_UART_H_

#include "Ifx_Types.h"

void init_UART(void);
void send_UART_message(uint8* txData, Ifx_SizeT count);

#endif /* BSP_UART_H_ */
