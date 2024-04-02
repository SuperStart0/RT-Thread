/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-01-23     RT-Thread    first version
 */

#include <rtthread.h>

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#include "dac.h"

int main(void)
{
    int count = 1;

    while (count)
    {
        set_dac_output(2048, 1);
        set_dac_output(4095, 2);
        rt_thread_mdelay(3000);

        close_dac_output(1);
        close_dac_output(2);
        rt_thread_mdelay(3000);
    }

    return RT_EOK;
}
