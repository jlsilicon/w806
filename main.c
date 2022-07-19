
#include <stdio.h>
#include "wm_hal.h"

//

void Error_Handler(void);
static void GPIO_Init(void);

//

int main(void)
{
    SystemClock_Config(CPU_CLK_160M);
    printf("enter main\r\n");

    HAL_Init();
    GPIO_Init();
    
    while (1)
    {


int value;

            value = GPIOA->DATA ;
// printf("PA: data = %08X ", value );
printf("PA: data = %032b ", value );
printf(", ");

            value = GPIOB->DATA ;
// printf("PB: data = %08X ", value );
printf("PB: data = %032b ", value );
printf("\r\n");
            HAL_Delay(1000);

    }
    
    return 0;
}

//

static void GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    __HAL_RCC_GPIO_CLK_ENABLE();

}

void HAL_GPIO_EXTI_Callback(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin)
{
    if ((GPIOx == GPIOB) && (GPIO_Pin == GPIO_PIN_5))
    {
        key_flag = 1;
    }
}

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
