/*
 * bsp_eru.h
 *
 *  Created on: 2022Äê8ÔÂ16ÈÕ
 *      Author: 74067
 */

#ifndef BSP_STM_H_
#define BSP_STM_H_

void initStm0(void);
void initStm1(void);
void runStm0(void);
void runStm1(void);

extern uint16 _flag0;
extern uint16 _flag1;
extern uint16 _flag2;

#endif /* BSP_STM_H_ */
