/*
 * bsp_eru.c
 *
 *  Created on: 2022Äê8ÔÂ16ÈÕ
 *      Author: 74067
 */
#include <bsp_led_button.h>
#include <bsp_stm.h>
#include "IfxStm_Timer.h"
#include <scu_sleep.h>

#define ISR_PRIORITY_STM    20                  /* STM Interrupt priority for interrupt ISR                         */

uint16 _flag0 = FALSE;
uint16 _flag1 = FALSE;
uint16 _flag2 = FALSE;

IfxStm_Timer g_stmTimer0;
IfxStm_Timer g_stmTimer1;
IFX_INTERRUPT(stmIsr0, 0, ISR_PRIORITY_STM);
IFX_INTERRUPT(stmIsr1, 2, ISR_PRIORITY_STM);

void initStm0(void)
{
    IfxStm_Timer_Config timerConfig;                                /* Timer configuration structure                */

    IfxStm_Timer_initConfig(&timerConfig, &MODULE_STM0);            /* Initialize it with default values            */

    timerConfig.base.frequency = 20;                                 /* Interrupt rate every STM_PERIOD seconds      */
    timerConfig.base.isrPriority = ISR_PRIORITY_STM;                /* Interrupt priority                           */
    timerConfig.base.isrProvider = IfxSrc_Tos_cpu0;                 /* CPU0 to trigger the interrupt                */
    timerConfig.comparator = IfxStm_Comparator_0;                   /* Comparator 0 register is used                */

    IfxStm_Timer_init(&g_stmTimer0, &timerConfig);                   /* Use timerConfig to initialize the STM        */
    IfxStm_Timer_run(&g_stmTimer0);
}

void initStm1(void)
{
    IfxStm_Timer_Config timerConfig;                                /* Timer configuration structure                */

    IfxStm_Timer_initConfig(&timerConfig, &MODULE_STM1);            /* Initialize it with default values            */

    timerConfig.base.frequency = 1;                                 /* Interrupt rate every STM_PERIOD seconds      */
    timerConfig.base.isrPriority = ISR_PRIORITY_STM;                /* Interrupt priority                           */
    timerConfig.base.isrProvider = IfxSrc_Tos_cpu2;                 /* CPU2 to trigger the interrupt                */
    timerConfig.comparator = IfxStm_Comparator_0;                   /* Comparator 0 register is used                */

    IfxStm_Timer_init(&g_stmTimer1, &timerConfig);                   /* Use timerConfig to initialize the STM        */
}

void runStm0(void)
{
    IfxStm_Timer_run(&g_stmTimer0);                                  /* Run the STM and set the compare Value        */
}

void runStm1(void)
{
    IfxStm_Timer_run(&g_stmTimer1);                                  /* Run the STM and set the compare Value        */
}

void stmIsr0(void)
{
    /* Enabling interrupts as ISR disables it */
    IfxCpu_enableInterrupts();

    /* Clear the timer event */
    IfxStm_Timer_acknowledgeTimerIrq(&g_stmTimer0);

    if (IfxPort_getPinState(BUTTON) == 0)
    {
        IfxStm_Timer_stop(&g_stmTimer0);
        IfxCpu_setCoreMode(&MODULE_CPU1, IfxCpu_CoreMode_run);
        _flag1 = TRUE;
    }
}

void stmIsr1(void)
{
    /* Enabling interrupts as ISR disables it */
    IfxCpu_enableInterrupts();

    /* Clear the timer event */
    IfxStm_Timer_acknowledgeTimerIrq(&g_stmTimer1);

    IfxStm_Timer_stop(&g_stmTimer1);

    led_toggle(LED2);
    runStm0();
    _flag2 = TRUE;
    IfxCpu_setCoreMode(&MODULE_CPU2, IfxCpu_CoreMode_idle);
}
