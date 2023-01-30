/// / TIM_GPIO_LEDS / : main.c : ///

#define  GPIO_LEDS_E  1 

//

#include <stdio.h>
 #include "wm_hal.h"

//

#ifdef  GPIO_LEDS_E
 static void GPIO_Init(void);
#endif

//

TIM_HandleTypeDef htim0;
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
#ifdef  NOT 
 TIM_HandleTypeDef htim3;
 TIM_HandleTypeDef htim4;
 TIM_HandleTypeDef htim5;
#endif

void Error_Handler(void);

static void TIM0_Init(void);
static void TIM1_Init(void);
static void TIM2_Init(void);
#ifdef  NOT 
 static void TIM3_Init(void);
 static void TIM4_Init(void);
 static void TIM5_Init(void);
#endif

//

// int main(void)
void  setup()
{
    SystemClock_Config(CPU_CLK_160M);
    printf("enter main\r\n");

#ifdef  GPIO_LEDS_E
    HAL_Init();
    GPIO_Init();

    HAL_GPIO_WritePin( GPIOB, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2, GPIO_PIN_RESET );
#endif


    TIM0_Init();
    HAL_TIM_Base_Start_IT(&htim0);

    TIM1_Init();
    HAL_TIM_Base_Start_IT(&htim1);

    TIM2_Init();
    HAL_TIM_Base_Start_IT(&htim2);

#ifdef  NOT 

    TIM3_Init();
    HAL_TIM_Base_Start_IT(&htim3);

    TIM4_Init();
    HAL_TIM_Base_Start_IT(&htim4);

    TIM5_Init();
    HAL_TIM_Base_Start_IT(&htim5);

#endif
}


void  loop()
{    
//    while(1)
    {
        HAL_Delay(1000);
    }
}

//

static void TIM0_Init(void)
{
    htim0.Instance = TIM0;
    htim0.Init.Unit = TIM_UNIT_US;
//    htim0.Init.Period = 1000000;
    htim0.Init.Period = 1000000;  // - 1 sec 
    htim0.Init.AutoReload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    if (HAL_TIM_Base_Init(&htim0) != HAL_OK)
    {
        Error_Handler();
    }
// HAL_GPIO_WritePin( GPIOB, GPIO_PIN_0 , GPIO_PIN_SET );
}

static void TIM1_Init(void)
{
    htim1.Instance = TIM1;
    htim1.Init.Unit = TIM_UNIT_US;
//    htim1.Init.Period = 1001000; 
//    htim1.Init.Period =  333000;  // - 1/3 sec 
    htim1.Init.Period =  667000;  // - 2/3 sec 
    htim1.Init.AutoReload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
    {
        Error_Handler();
    }
}

static void TIM2_Init(void)
{
    htim2.Instance = TIM2;
    htim2.Init.Unit = TIM_UNIT_US;
//    htim2.Init.Period = 1002000;
    htim2.Init.Period =  250000;  // - 1/4 sec 
    htim2.Init.AutoReload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
    {
        Error_Handler();
    }
}

#ifdef  NOT 

static void TIM3_Init(void)
{
    htim3.Instance = TIM3;
    htim3.Init.Unit = TIM_UNIT_US;
    htim3.Init.Period = 1003000;
    htim3.Init.AutoReload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
    {
        Error_Handler();
    }
}

static void TIM4_Init(void)
{
    htim4.Instance = TIM4;
    htim4.Init.Unit = TIM_UNIT_US;
    htim4.Init.Period = 1004000;
    htim4.Init.AutoReload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
    {
        Error_Handler();
    }
}

static void TIM5_Init(void)
{
    htim5.Instance = TIM5;
    htim5.Init.Unit = TIM_UNIT_US;
    htim5.Init.Period = 1005000;
    htim5.Init.AutoReload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    if (HAL_TIM_Base_Init(&htim5) != HAL_OK)
    {
        Error_Handler();
    }
}

#endif

//

void HAL_TIM_Callback(TIM_HandleTypeDef *htim)
{
    printf("t=%d ", htim->Instance );
//HAL_GPIO_WritePin( GPIOB, GPIO_PIN_1 , GPIO_PIN_SET );

    if (htim->Instance == TIM0)
    {

#ifdef  GPIO_LEDS_E

//        if (key_flag == 1)
//        {
//            HAL_Delay(20);
//            if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == GPIO_PIN_RESET)
//            {
                HAL_GPIO_TogglePin( GPIOB, GPIO_PIN_0 );
//            }
//            key_flag = 0;
//        }

#endif

    }

    if (htim->Instance == TIM1)
    {

#ifdef  GPIO_LEDS_E
                HAL_GPIO_TogglePin( GPIOB, GPIO_PIN_1 );
#endif
        
    }

    if (htim->Instance == TIM2)
    {

#ifdef  GPIO_LEDS_E
                HAL_GPIO_TogglePin( GPIOB, GPIO_PIN_2 );
#endif

    }

#ifdef  NOT 
    if (htim->Instance == TIM3)
    {
        ;
    }

    if (htim->Instance == TIM4)
    {
        ;
    }

    if (htim->Instance == TIM5)
    {
        ;
    }
#endif

}

//

/*
void Error_Handler(void)
{
    while (1)
    {
    }
}
*/

/*
void assert_failed(uint8_t *file, uint32_t line)
{
    printf("Wrong parameters value: file %s on line %d\r\n", file, line);
}
*/

//


#ifdef  GPIO_LEDS_E

static void GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    __HAL_RCC_GPIO_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2, GPIO_PIN_SET);
    
//    GPIO_InitStruct.Pin = GPIO_PIN_5;
//    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
//    GPIO_InitStruct.Pull = GPIO_PULLUP;
//    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    HAL_NVIC_SetPriority(GPIOB_IRQn, 0);
    HAL_NVIC_EnableIRQ(GPIOB_IRQn);

}

void HAL_GPIO_EXTI_Callback(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin)
{

//    if ((GPIOx == GPIOB) && (GPIO_Pin == GPIO_PIN_5))
//    {
//        key_flag = 1;
//    }

}

#endif

