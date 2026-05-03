
#include "sys.h"
#include "led.h"
#include "usart.h"
#include <stdint.h>
#include <stdio.h>
#include "mpu.h"
#include "timer.h"






int main(void)
{


    sys_cache_enable();                     /* 使能CPU cache */
    delay_init(600);                        /* 延时初始化 */
    usart_init(115200);                     /* 初始化USART */
    led_init();							                /* 初始化LED */   
    mpu_memory_protection();                /* 保护相关存储区域 */

	
	timerx_int_init(10000 - 1, 30000 - 1);   /* 300 000 000 / 30000 = 10KHz 10KHz的计数频率，计数10000次为1s */
	printf("SystemCoreClock: %lu Hz\r\n", SystemCoreClock);

    while (1)
    {        
		LED0_TOGGLE();
		delay_ms(1000);

    }
}









#if SYS_SUPPORT_OS


 


/**
 * @brief       systick中断服务函数,使用OS时用到
 * @param       ticks: 延时的节拍数
 * @retval      无
 */



void SysTick_Handler(void)
{

}

#endif




