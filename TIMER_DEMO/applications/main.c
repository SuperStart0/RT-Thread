/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-01-29     RT-Thread    first version
 */

#include <rtthread.h>

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#include "timer.h"

int main(void)
{
    int count = 1;

    rt_hwtimerval_t timeout_s;
    timeout_s.sec = 1;
    start_Hwtimer(timeout_s);

    while (count++)
    {
//        LOG_D("Hello RT-Thread!");
        if (timer_flag == 1)
        {
            close_Hwtimer();
            timer_flag = 0;

            rt_kprintf("hwtimer close\n");
        }

        rt_thread_mdelay(1000);
    }

    return RT_EOK;
}

