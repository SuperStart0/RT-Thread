/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-01-31     IBM       the first version
 */
#ifndef APPLICATIONS_INC_USART_H_
#define APPLICATIONS_INC_USART_H_

#include <rtthread.h>
#include <rtdevice.h>
#include <drv_common.h>
#include <rtconfig.h>
#include <rtdbg.h>

#define LED0_PIN    GET_PIN(D, 12)

extern void usart_Init(void);
extern void recv_Usart_Data(void);

#endif /* APPLICATIONS_INC_USART_H_ */
