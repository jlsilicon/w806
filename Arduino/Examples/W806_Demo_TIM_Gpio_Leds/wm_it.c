
#include "wm_hal.h"


extern TIM_HandleTypeDef htim0;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
#ifdef  NOT 
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
#endif


#define readl(addr) ({unsigned int __v = (*(volatile unsigned int *) (addr)); __v;})
/* ??? REDEFINES ??? :
__attribute__((isr)) void CORET_IRQHandler(void)
{
    readl(0xE000E010);
    HAL_IncTick();
}
*/

__attribute__((isr)) void TIM0_5_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&htim0);
    HAL_TIM_IRQHandler(&htim1);
    HAL_TIM_IRQHandler(&htim2);

#ifdef  NOT 
    HAL_TIM_IRQHandler(&htim3);
    HAL_TIM_IRQHandler(&htim4);
    HAL_TIM_IRQHandler(&htim5);
#endif

}


#ifdef  GPIO_LEDS_E

__attribute__((isr)) void GPIOA_IRQHandler(void)
{
 	HAL_GPIO_EXTI_IRQHandler(GPIOA, GPIO_PIN_0);
}

__attribute__((isr)) void GPIOB_IRQHandler(void)
{
 	HAL_GPIO_EXTI_IRQHandler(GPIOB, GPIO_PIN_0);
 	HAL_GPIO_EXTI_IRQHandler(GPIOB, GPIO_PIN_1);
 	HAL_GPIO_EXTI_IRQHandler(GPIOB, GPIO_PIN_2);

	HAL_GPIO_EXTI_IRQHandler(GPIOB, GPIO_PIN_5);
}

#endif
