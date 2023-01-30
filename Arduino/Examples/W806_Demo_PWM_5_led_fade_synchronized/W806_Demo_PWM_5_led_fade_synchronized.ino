/******************************************************************************
** 
 * \file        main.c
 * \author      IOsetting | iosetting@outlook.com
 * \date        
 * \brief       Demo code of PWM in 5-sync mode
 * \note        This will drive 5 LEDs (3 onboard and 2 external) to show 5-sync mode
 * \version     v0.1
 * \ingroup     demo
 * \remarks     test-board: HLK-W806-KIT-V1.0
 *              PWM Frequency = 40MHz / Prescaler / (Period + 1)；
 *              Duty Cycle(Edge Aligned)   = (Pulse + 1) / (Period + 1)
 *              Duty Cycle(Center Aligned) = (2 * Pulse + 1) / (2 * (Period + 1))
 *
 *              Connect PB3 and PB16 to an external LEDs for PWM3 and PWM4 output
 *              PB3   -> ext LED1(-)
 *              3V3   -> ext LED1(+)(with 1KR resistor)
 *              PB16  -> ext LED2(-)
 *              3V3   -> ext LED2(+)(with 1KR resistor)
 *              
******************************************************************************/

#include <stdio.h>
// #include "wm_hal.h"

#define DUTY_MAX 100
#define DUTY_MIN 50

PWM_HandleTypeDef hpwm;
int i, j, m, d;

static void PWM_Init(uint32_t channel);
void Error_Handler(void);

uint32_t ch = PWM_CHANNEL_0;

//

// int main(void)
void  setup()
{
    int i = 0;
    
    SystemClock_Config(CPU_CLK_160M);
    printf("enter main\r\n");
    
    PWM_Init(ch);
//    HAL_PWM_Start(&hpwm);
    HAL_PWM_Start(&hpwm, ch);
}


void  loop()
{
//    while (1)
    {
        if (m == 0) // Increasing
        {
//            HAL_PWM_Duty_Set(&hpwm, d++);
            HAL_PWM_Duty_Set(&hpwm, ch, d++);
            if (d == DUTY_MAX)
            {
                m = 1;
            }
        }
        else // Decreasing
        {
//            HAL_PWM_Duty_Set(&hpwm, d--);
            HAL_PWM_Duty_Set(&hpwm, ch, d--);
            if (d == DUTY_MIN)
            {
                m = 0;
            }
        }
        HAL_Delay(20);
    }
}

static void PWM_Init(uint32_t channel)
{
    hpwm.Instance = PWM;
    hpwm.Init.AutoReloadPreload = PWM_AUTORELOAD_PRELOAD_ENABLE;
    hpwm.Init.CounterMode = PWM_COUNTERMODE_EDGEALIGNED_DOWN;
    hpwm.Init.Prescaler = 4;
    hpwm.Init.Period = 99;    // Frequency = 40,000,000 / 4 / (99 + 1) = 100,000 = 100KHz
    hpwm.Init.Pulse = 19;     // Duty Cycle = (19 + 1) / (99 + 1) = 20%
    hpwm.Init.OutMode = PWM_OUT_MODE_5SYNC; // Make 5 channels output the same
    hpwm.Channel = channel;
    
    HAL_PWM_Init(&hpwm);
}

/*
void Error_Handler(void)
{
    while (1)
    {
    }
}

void assert_failed(uint8_t *file, uint32_t line)
{
    printf("Wrong parameters value: file %s on line %d\r\n", file, line);
}
*/
