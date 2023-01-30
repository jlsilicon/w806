
 #include "wm_hal.h"


void HAL_MspInit(void)
{

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{
    __HAL_RCC_TIM_CLK_ENABLE();
    HAL_NVIC_SetPriority(TIM_IRQn, 0);
    HAL_NVIC_EnableIRQ(TIM_IRQn);
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* htim_base)
{
//    __HAL_RCC_TIM_CLK_DISABLE();
//    HAL_NVIC_DisableIRQ(TIM_IRQn);
}
