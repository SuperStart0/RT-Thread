/*
 * 程序清单：这是一个 hwtimer 设备使用例程
 * 例程导出了 hwtimer_sample 命令到控制终端
 * 命令调用格式：hwtimer_sample
 * 程序功能：硬件定时器超时回调函数周期性的打印当前tick值，2次tick值之差换算为时间等同于定时时间值。
*/
#include "timer.h"

rt_device_t hw_dev = RT_NULL;   /* 定时器设备句柄 */
rt_uint32_t timer_count = 0;    /* 定时器计数值 */
rt_uint16_t timer_flag = 0;

/**
 * @brief 定时器超时回调函数
 * @param dev
 * @param size
 * @return
 */
static rt_err_t timeout_cb(rt_device_t dev, rt_size_t size)
{
    rt_tick_t tick = rt_tick_get();
    rt_kprintf("tick is :%d !\n", tick);

    timer_count++;
    if (timer_count >= 60)
    {
        timer_count = 0;
        timer_flag = 1;
    }

    return 0;
}


/**
 * @brief 启动定时器，设置定时时间
 * @param timeout_s 定时时间
 * @return
 */
int start_Hwtimer(rt_hwtimerval_t timeout_s)
{
    rt_err_t ret = RT_EOK;
    rt_hwtimer_mode_t mode;         /* 定时器模式 */
    rt_uint32_t freq = 10000;       /* 计数频率 */

    /* 查找定时器设备 */
    hw_dev = rt_device_find(HWTIMER_DEV_NAME);
    if (hw_dev == RT_NULL)
    {
        rt_kprintf("hwtimer sample run failed! can't find %s device!\n", HWTIMER_DEV_NAME);
        return RT_ERROR;
    }

    /* 以读写方式打开设备 */
    ret = rt_device_open(hw_dev, RT_DEVICE_OFLAG_RDWR);
    if (ret != RT_EOK)
    {
        rt_kprintf("open %s device failed!\n", HWTIMER_DEV_NAME);
        return ret;
    }

    /* 设置超时回调函数 */
    rt_device_set_rx_indicate(hw_dev, timeout_cb);

    /* 设置计数频率(若未设置该项，默认为1Mhz 或 支持的最小计数频率) */
    rt_device_control(hw_dev, HWTIMER_CTRL_FREQ_SET, &freq);

    /* 设置模式为周期性定时器（若未设置，默认是HWTIMER_MODE_ONESHOT）*/
    mode = HWTIMER_MODE_PERIOD;
    ret = rt_device_control(hw_dev, HWTIMER_CTRL_MODE_SET, &mode);
    if (ret != RT_EOK)
    {
        rt_kprintf("set mode failed! ret is :%d\n", ret);
        return ret;
    }

    /* 设置定时器超时值,并启动定时器 */
    if (rt_device_write(hw_dev, 0, &timeout_s, sizeof(timeout_s)) != sizeof(timeout_s))
    {
        rt_kprintf("set timeout value failed\n");
        return RT_ERROR;
    }

    return ret;
}


/**
 * @brief 关闭定时器
 */
void close_Hwtimer(void)
{
    rt_device_close(hw_dev);
}





