/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-01-23     IBM       the first version
 */
#ifndef APPLICATIONS_DAC_H_
#define APPLICATIONS_DAC_H_

#include <rtthread.h>
#include <rtdevice.h>
#include <drv_common.h>
#include <stdlib.h>

#define DAC_PORT    GPIOA
#define DAC_PIN     GPIO_PIN_5          // dac引脚号 -- DAC1_OUT2


#define DAC_DEV_NAME        "dac1"      // DAC 设备名称
#define DAC_DEV_CHANNEL_1   1           // DAC 通道1
#define DAC_DEV_CHANNEL_2   2           // DAC 通道2
#define REFER_VOLTAGE       250         // 参考电压 2.5V,数据精度乘以100保留2位小数
#define CONVERT_BITS        (1 << 12)   // 转换位数为12位


extern int set_dac_output(uint32_t dac_value, uint8_t channel);
extern void close_dac_output(uint8_t channel);

#endif /* APPLICATIONS_DAC_H_ */
