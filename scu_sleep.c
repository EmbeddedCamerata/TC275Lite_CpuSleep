/*
 * scu_sleep.c
 *
 *  Created on: 2022Äê8ÔÂ2ÈÕ
 *      Author: 74067
 */
#include <scu_sleep.h>
#include <bsp_uart.h>
#include "IfxCpu.h"
#include "IfxScuWdt.h"

#define BLOCK_SLEEP_MODE    0x1                 /* Block sleep mode for STM                                         */
#define PMSWCR1_CPUSEL      0x1                 /* Set the CPU0 as CPU master                                       */
#define PMSWCR2_CPUSEL      0x2                 /* Set the CPU1 as CPU master                                       */
#define PMSWCR3_CPUSEL      0x4                 /* Set the CPU2 as CPU master                                       */
#define PMCSR0_REQSLP       0x2                 /* Request sleep mode                                               */

void Cpu0_req_sleep(void)
{
    /* Clear safety EndInit protection */
    IfxScuWdt_clearSafetyEndinitInline(IfxScuWdt_getSafetyWatchdogPasswordInline());
    /* Clear EndInit protection */
    IfxScuWdt_clearCpuEndinit(IfxScuWdt_getCpuWatchdogPassword());

    STM0_CLC.B.EDIS = BLOCK_SLEEP_MODE;

    SCU_PMSWCR1.B.CPUSEL = PMSWCR1_CPUSEL;      /* Set the CPU0 as CPU master to trigger a power down mode      */
    SCU_PMCSR0.B.REQSLP = PMCSR0_REQSLP;        /* Request System Sleep Mode CPU0                               */

    /* Set safety EndInit protection */
    IfxScuWdt_setSafetyEndinitInline(IfxScuWdt_getSafetyWatchdogPasswordInline());
    /* Set EndInit protection */
    IfxScuWdt_setCpuEndinit(IfxScuWdt_getCpuWatchdogPassword());
}
