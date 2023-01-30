//
// need to compile / make i : 
//    ~/wm-sdk-w806/ 
//

#include <stdio.h>
// #include "wm_hal.h"

//

/// LED_0_PORT = GPB0 = Out : ///
#define  LED_0_PORT    GPIOB
#define  LED_0_PIN      GPIO_PIN_0 

/// LED_1_PORT = GPB1 = Out : ///
#define  LED_1_PORT   GPIOB
#define  LED_1_PIN      GPIO_PIN_1 

/// LED_2_PORT = GPB2 = Out : ///
#define  LED_2_PORT   GPIOB
#define  LED_2_PIN      GPIO_PIN_2 

//

void Error_Handler(void);
static void GPIO_Init(void);

//

long  Cnt_ = 0 ;

//

// int main(void)
void  setup()
{
    SystemClock_Config(CPU_CLK_160M);
    printf("enter main\r\n");

    HAL_Init();
    GPIO_Init();
    HAL_GPIO_WritePin( GPIOB, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2, GPIO_PIN_RESET );
//    HAL_GPIO_WritePin( GPIOB, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2, GPIO_PIN_SET );
}

void  loop()
{
//    while (1)
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


        Cnt_ ++ ; 

        /// if b0 == 1 : ///
        if( Cnt_ & 0x00000001 )
            /// LED_0 = 1 : ///
            HAL_GPIO_WritePin( LED_0_PORT , LED_0_PIN , GPIO_PIN_RESET );
        else 
            /// LED_0 = 0 : ///
            HAL_GPIO_WritePin( LED_0_PORT , LED_0_PIN , GPIO_PIN_SET   );

        /// if b0 == 1 : ///
        if( Cnt_ & 0x00000002 )
            /// LED_1 = 1 : ///
            HAL_GPIO_WritePin( LED_1_PORT , LED_1_PIN , GPIO_PIN_RESET );
        else 
            /// LED_1 = 0 : ///
            HAL_GPIO_WritePin( LED_1_PORT , LED_1_PIN , GPIO_PIN_SET   );

        /// if b0 == 1 : ///
        if( Cnt_ & 0x00000004 )
            /// LED_2 = 1 : ///
            HAL_GPIO_WritePin( LED_2_PORT , LED_2_PIN , GPIO_PIN_RESET );
        else 
            /// LED_2 = 0 : ///
            HAL_GPIO_WritePin( LED_2_PORT , LED_2_PIN , GPIO_PIN_SET   );


    }
    
//    return 0;
}

//

static void GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    __HAL_RCC_GPIO_CLK_ENABLE();

    /// LED_0_PIN = GPB0 = Out : ///
    /// LED_1_PIN = GPB1 = Out : ///
    /// LED_2_PIN = GPB2 = Out : ///
    GPIO_InitStruct.Pin = LED_0_PIN | LED_1_PIN | LED_2_PIN ;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(     GPIOB, &GPIO_InitStruct);
    HAL_GPIO_WritePin( GPIOB, LED_0_PIN | LED_1_PIN | LED_2_PIN , GPIO_PIN_SET );

}

void HAL_GPIO_EXTI_Callback(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin)
{
/*
    if ((GPIOx == GPIOB) && (GPIO_Pin == GPIO_PIN_5))
    {
//        key_flag = 1;
    }
*/
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

