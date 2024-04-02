/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-01-22     RT-Thread    first version
 */

#include <rtthread.h>
#include <drv_common.h>
#include "pwm.h"

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#define ID  GET_PIN(E, 12)

int main(void)
{
    int count = 1;

    rt_pin_mode(ID, PIN_MODE_OUTPUT);

    set_pwm_param(500, 50);

    while (count)
    {
        rt_pin_write(ID, RESET);
        rt_thread_mdelay(1000);
        rt_pin_write(ID, SET);
        rt_thread_mdelay(1000);
    }

    return RT_EOK;
}
