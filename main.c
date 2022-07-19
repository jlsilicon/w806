/*
     ->	SH/LD#	1   \/	14	+Vcc 
     ->	SCLK			CLKINH# = -Gnd 
    I >	PdiE			PdiA < I 
    I >	PdiF			PdiB < I 
    I >	Pdig			PdiC < I 
    I >	PdiH			PdiD < I 
    . =	SerQh'			SerI  = .
	-Gnd	8	9	SerQh -> 
*/


#include <stdio.h>
#include "wm_hal.h"

//

/// LED_0_PORT = GPB0 = Out : ///
#define  LED_0_PORT		GPIOB
#define  LED_0_PIN   		GPIO_PIN_0 

/// LED_1_PORT = GPB1 = Out : ///
#define  LED_1_PORT		GPIOB
#define  LED_1_PIN   		GPIO_PIN_1 

/// LED_2_PORT = GPB2 = Out : ///
#define  LED_2_PORT		GPIOB
#define  LED_2_PIN   		GPIO_PIN_2 


/// HC165_LDSH_PIN = GPB3 = Out (0=LD , 1=SH) : ///
#define  HC165_LDSH_PORT	GPIOB
#define  HC165_LDSH_PIN 	GPIO_PIN_3 

/// HC165_SCLK_PIN = GPB4 = Out (0->1=CLK) : ///
#define  HC165_SCLK_PORT	GPIOB
#define  HC165_SCLK_PIN 	GPIO_PIN_4 

/// HC165_SERQH_PIN = GPB5 = In : ///
#define  HC165_SERQH_PORT	GPIOB
#define  HC165_SERQH_PIN	GPIO_PIN_5 

//

void Error_Handler(void);
static void GPIO_Init(void);

//

// static volatile uint8_t key_flag = 0;

//

int main(void)
{
    SystemClock_Config(CPU_CLK_160M);
    printf("enter main\r\n");

    HAL_Init();
    GPIO_Init();
    HAL_GPIO_WritePin( GPIOB, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2, GPIO_PIN_RESET );

    while (1)
    {

            HAL_Delay(20);

//            if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == GPIO_PIN_RESET)
//            {
//                HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2);
//            }

        int  i , b , d=0 ;
        for( i=0; i<=8; i++ )
        {
            /// b = HC165_SERQH_PIN : ///
            if (HAL_GPIO_ReadPin( HC165_SERQH_PORT , HC165_SERQH_PIN ) == GPIO_PIN_RESET)
                b = 0 ;
            else
                b = 1 ;
            /// ( d << 1 ) +  b : ///
            d = ( (d << 1) | b );
            ;
            /// SCLK = 0 -> 1 : ///
            /// SCLK = 0 : ///
            HAL_GPIO_WritePin( HC165_SCLK_PORT , HC165_SCLK_PIN , GPIO_PIN_RESET );
             HAL_Delay(1);
            /// SCLK = 1 : ///
            HAL_GPIO_WritePin( HC165_SCLK_PORT , HC165_SCLK_PIN , GPIO_PIN_SET   );
             HAL_Delay(1);
        }

        /// if b0 == 1 : ///
        if( d & 0x01 )
            /// LED_0 = 1 : ///
            HAL_GPIO_WritePin( LED_0_PORT , LED_0_PIN , GPIO_PIN_RESET );
        else 
            /// LED_0 = 0 : ///
            HAL_GPIO_WritePin( LED_0_PORT , LED_0_PIN , GPIO_PIN_SET   );

        /// if b0 == 1 : ///
        if( d & 0x02 )
            /// LED_1 = 1 : ///
            HAL_GPIO_WritePin( LED_1_PORT , LED_1_PIN , GPIO_PIN_RESET );
        else 
            /// LED_1 = 0 : ///
            HAL_GPIO_WritePin( LED_1_PORT , LED_1_PIN , GPIO_PIN_SET   );

        /// if b0 == 1 : ///
        if( d & 0x04 )
            /// LED_2 = 1 : ///
            HAL_GPIO_WritePin( LED_2_PORT , LED_2_PIN , GPIO_PIN_RESET );
        else 
            /// LED_2 = 0 : ///
            HAL_GPIO_WritePin( LED_2_PORT , LED_2_PIN , GPIO_PIN_SET   );
printf("74hc165: data = %08b ", d );
printf(", ");


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

    /// HC165_LDSH_PIN   = GPB3 = Out : ///
    /// HC165_SCLK_PIN   = GPB4 = Out : ///
    GPIO_InitStruct.Pin  = HC165_LDSH_PIN | HC165_SCLK_PIN ;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(     GPIOB, &GPIO_InitStruct);
    HAL_GPIO_WritePin( GPIOB, HC165_LDSH_PIN , GPIO_PIN_SET   );
    HAL_GPIO_WritePin( GPIOB, HC165_SCLK_PIN , GPIO_PIN_RESET );

    /// HC165_SERQH_PIN  = GPB5 = In : ///
    GPIO_InitStruct.Pin  = HC165_SERQH_PIN ;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(     GPIOB, &GPIO_InitStruct);
//    HAL_GPIO_WritePin( GPIOB, HC165_SERQH_PIN , GPIO_PIN_RESET );


}

void HAL_GPIO_EXTI_Callback(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin)
{
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