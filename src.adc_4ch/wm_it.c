
#include "wm_hal.h"

//extern ADC_HandleTypeDef hadc;
extern ADC_HandleTypeDef hadc_0;
extern ADC_HandleTypeDef hadc_1;
extern ADC_HandleTypeDef hadc_2;
extern ADC_HandleTypeDef hadc_3;


#define readl(addr) ({unsigned int __v = (*(volatile unsigned int *) (addr)); __v;})
__attribute__((isr)) void CORET_IRQHandler(void)
{
    readl(0xE000E010);
    HAL_IncTick();
}

__attribute__((isr)) void ADC_IRQHandler(void)
{
//    HAL_ADC_IRQHandler(&hadc);
    HAL_ADC_IRQHandler(&hadc_0);
    HAL_ADC_IRQHandler(&hadc_1);
    HAL_ADC_IRQHandler(&hadc_2);
    HAL_ADC_IRQHandler(&hadc_3);
}
