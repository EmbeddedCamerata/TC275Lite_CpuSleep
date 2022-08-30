/*
 * bsp_uart.c
 *
 *  Created on: 2022Äê8ÔÂ16ÈÕ
 *      Author: 74067
 */

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "IfxAsclin_Asc.h"
#include "IfxCpu_Irq.h"

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
#define SERIAL_BAUDRATE         115200                                      /* Baud rate in bit/s                   */

#define SERIAL_PIN_RX           IfxAsclin0_RXA_P14_1_IN                     /* RX pin of the board                  */
#define SERIAL_PIN_TX           IfxAsclin0_TX_P14_0_OUT                     /* TX pin of the board                  */

#define INTPRIO_ASCLIN0_TX      19                                          /* Priority of the ISR                  */

#define ASC_TX_BUFFER_SIZE      64                                          /* Definition of the buffer size        */

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/
IfxAsclin_Asc g_asc;                                                        /* Declaration of the ASC handle        */
uint8 g_ascTxBuffer[ASC_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];             /* Declaration of the FIFOs parameters  */

/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/
IFX_INTERRUPT(asclin0_Tx_ISR, 0, INTPRIO_ASCLIN0_TX);                       /* Adding the Interrupt Service Routine */

void asclin0_Tx_ISR(void)
{
    IfxAsclin_Asc_isrTransmit(&g_asc);
}

void init_UART(void)
{
    /* Initialize an instance of IfxAsclin_Asc_Config with default values */
    IfxAsclin_Asc_Config ascConfig;
    IfxAsclin_Asc_initModuleConfig(&ascConfig, SERIAL_PIN_TX.module);

    /* Set the desired baud rate */
    ascConfig.baudrate.baudrate = SERIAL_BAUDRATE;

    /* ISR priorities and interrupt target */
    ascConfig.interrupt.txPriority = INTPRIO_ASCLIN0_TX;
    ascConfig.interrupt.typeOfService = IfxCpu_Irq_getTos(IfxCpu_getCoreIndex());

    /* FIFO configuration */
    ascConfig.txBuffer = &g_ascTxBuffer;
    ascConfig.txBufferSize = ASC_TX_BUFFER_SIZE;

    /* Port pins configuration */
    const IfxAsclin_Asc_Pins pins =
    {
        NULL_PTR,         IfxPort_InputMode_pullUp,     /* CTS pin not used     */
        &SERIAL_PIN_RX,   IfxPort_InputMode_pullUp,     /* RX pin not used      */
        NULL_PTR,         IfxPort_OutputMode_pushPull,  /* RTS pin not used     */
        &SERIAL_PIN_TX,   IfxPort_OutputMode_pushPull,  /* TX pin               */
        IfxPort_PadDriver_cmosAutomotiveSpeed1
    };
    ascConfig.pins = &pins;

    IfxAsclin_Asc_initModule(&g_asc, &ascConfig);                       /* Initialize module with above parameters  */
}

void send_UART_message(uint8* txData, Ifx_SizeT count)
{
    IfxAsclin_Asc_write(&g_asc, txData, &count, TIME_INFINITE);         /* Transfer of data                         */
}
