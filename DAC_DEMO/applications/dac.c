/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-01-23     IBM       the first version
 */
#include "dac.h"

/**
 * @brief 设置DAC输出电压
 * @param dac_value DAC值
 * @param channel 通道
 * @return
 */
int set_dac_output(uint32_t dac_value, uint8_t channel)
{
    rt_dac_device_t dac_dev;
    rt_uint32_t value, vol;
    rt_err_t ret = RT_EOK;

    /* 查找设备 */
    dac_dev = (rt_dac_device_t)rt_device_find(DAC_DEV_NAME);
    if (dac_dev == RT_NULL)
    {
        rt_kprintf("dac sample run failed! can't find %s device!\n", DAC_DEV_NAME);
        return RT_ERROR;
    }

    /* 打开通道 */
    ret = rt_dac_enable(dac_dev, channel);

    /* 设置输出值 */
    value = dac_value;
    if (value > 4095)
    {
        value = 4095;
    }
    rt_dac_write(dac_dev, channel, value);
    rt_kprintf("the value is :%d \n", value);

    /* 转换为对应电压值 */
    vol = value * REFER_VOLTAGE / CONVERT_BITS;
    rt_kprintf("the voltage is :%d.%02d \n", vol / 100, vol % 100);

    return ret;
}


/**
 * @brief 关闭DAC输出
 * @param channel 通道
 */
void close_dac_output(uint8_t channel)
{
    rt_dac_device_t dac_dev;

    /* 查找设备 */
    dac_dev = (rt_dac_device_t)rt_device_find(DAC_DEV_NAME);
    if (dac_dev == RT_NULL)
    {
        rt_kprintf("dac sample run failed! can't find %s device!\n", DAC_DEV_NAME);
        return RT_ERROR;
    }

    rt_dac_disable(dac_dev, channel);
}














