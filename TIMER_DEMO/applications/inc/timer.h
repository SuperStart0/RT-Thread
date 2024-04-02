/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-01-29     IBM       the first version
 */
#ifndef APPLICATIONS_INC_TIMER_H_
#define APPLICATIONS_INC_TIMER_H_

#include <rtthread.h>
#include <rtdevice.h>

#define HWTIMER_DEV_NAME   "timer3"     /* 定时器名称 */
extern rt_device_t hw_dev;              /* 定时器设备句柄 */
extern rt_uint16_t timer_flag;

extern int start_Hwtimer(rt_hwtimerval_t timeout_s);
extern void close_Hwtimer(void);

#endif /* APPLICATIONS_INC_TIMER_H_ */
