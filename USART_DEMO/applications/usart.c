/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-01-31     IBM       the first version
 */
#include "usart.h"

static rt_device_t serial;                                  /* 串口设备句柄 */
static struct rt_semaphore rx_sem;                          /* 用于接收消息的信号量 */
struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;  /* 初始化配置参数 */

char str[] = "hello RT-Thread!\r\n";
char ch;


/**
 * @brief 接收数据回调函数
 * @param dev
 * @param size
 */
static rt_err_t uart_input(rt_device_t dev, rt_size_t size)
{
    /* 串口接收到数据后产生中断，调用此回调函数，然后发送接收信号量 */
    rt_sem_release(&rx_sem);

    return RT_EOK;
}


/**
 * @brief 串口初始化
 */
void usart_Init(void)
{
    /* 初始化信号量 */
    rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);

    /* step1：查找串口设备 */
    serial = rt_device_find(RT_CONSOLE_DEVICE_NAME);

    /* step2：修改串口配置参数 */
    config.baud_rate = BAUD_RATE_115200;    // 修改波特率为 115200
    config.data_bits = DATA_BITS_8;         // 数据位 8
    config.stop_bits = STOP_BITS_1;         // 停止位 1
    config.bufsz = 128;                     // 修改缓冲区 buff size 为 128
    config.parity = PARITY_NONE;            // 无奇偶校验位

    /* step3：控制串口设备。通过控制接口传入命令控制字，与控制参数 */
    rt_device_control(serial, RT_DEVICE_CTRL_CONFIG, &config);

    /* step4：打开串口设备。以中断接收及轮询发送模式打开串口设备 */
    rt_device_open(serial, RT_DEVICE_FLAG_INT_RX);

    /* 设置接收回调函数 */
    rt_device_set_rx_indicate(serial, uart_input);

    /* 发送字符串 */
    rt_device_write(serial, 0, str, (sizeof(str) - 1));
}


/**
 * @brief 接收串口数据
 */
void recv_Usart_Data(void)
{
    /* 从串口读取一个字节的数据，没有读取到则等待接收信号量 */
    if (rt_device_read(serial, 0, &ch, 1) != 0)
    {
        /* 阻塞等待接收信号量，等到信号量后再次读取数据 */
        rt_sem_take(&rx_sem, RT_WAITING_FOREVER);
        rt_kprintf("%c\n",ch);

        if(ch=='l')
            rt_pin_write(LED0_PIN, PIN_LOW);
        else if(ch=='e')
            rt_pin_write(LED0_PIN, PIN_HIGH);
    }
}
















