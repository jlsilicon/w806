
#include <stdio.h>
// #include "wm_hal.h"


/// PuTTY , COM10 , Baud=115200 ///

//ADC_CHANNEL_0 : PA1
//ADC_CHANNEL_1 : PA4
//ADC_CHANNEL_2 : PA3
//ADC_CHANNEL_3 : PA2


void Error_Handler(void);
static void ADC_Init(void);
// ADC_HandleTypeDef hadc   ;
ADC_HandleTypeDef hadc_0 ;
ADC_HandleTypeDef hadc_1 ;
ADC_HandleTypeDef hadc_2 ;
ADC_HandleTypeDef hadc_3 ;

//

// int main(void)
void  setup()
{
int value;
double voltage = 0.0;
    
    SystemClock_Config(CPU_CLK_160M);

    printf("enter main\r\n");
    printf(" - Adc on Ch0:PA1 , Ch1:PA4 \r\n");
    printf(" - can also read : Adc on Ch2:PA3 , Ch3:PA2 \r\n");

    ADC_Init();
}
    
void  loop()
{   
    while (1)
    {
//        value = HAL_ADC_GET_INPUT_VOLTAGE(&hadc  );
        value = HAL_ADC_GET_INPUT_VOLTAGE(&hadc_0);
// printf("Adc0: value = %dmv\r\n", value);
printf("Adc0.PA1: value = %dmv ", value);
printf(", ");

        value = HAL_ADC_GET_INPUT_VOLTAGE(&hadc_1);
printf("Adc1.PA4: value = %dmv ", value);
printf(", ");

        value = HAL_ADC_GET_INPUT_VOLTAGE(&hadc_2);
printf("Adc2.PA3: value = %dmv ", value);
printf(", ");

        value = HAL_ADC_GET_INPUT_VOLTAGE(&hadc_3);
printf("Adc3.PA2: value = %dmv ", value);
// printf(", ");
printf("\r\n");

    //// GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin) ////
    //// if ((GPIOx->DATA & GPIO_Pin) != GPIO_PIN_RESET) ////
    //// if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == GPIO_PIN_RESET) ////
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
}

static void ADC_Init(void)
{

//    hadc.Instance     = ADC;
//    hadc.Init.channel = ADC_CHANNEL_0;
//    hadc.Init.freq    = 1000;    
//    if (HAL_ADC_Init(&hadc) != HAL_OK)
    hadc_0.Instance     = ADC;
    hadc_0.Init.channel = ADC_CHANNEL_0;
    hadc_0.Init.freq    = 1000;    
    if (HAL_ADC_Init(&hadc_0) != HAL_OK)
    {
        Error_Handler();
    }
    
    hadc_1.Instance     = ADC;
    hadc_1.Init.channel = ADC_CHANNEL_1;
    hadc_1.Init.freq    = 1000;    
    if (HAL_ADC_Init(&hadc_1) != HAL_OK)
    {
        Error_Handler();
    }

    hadc_2.Instance     = ADC;
    hadc_2.Init.channel = ADC_CHANNEL_2;
    hadc_2.Init.freq    = 1000;    
    if (HAL_ADC_Init(&hadc_2) != HAL_OK)
    {
        Error_Handler();
    }

    hadc_3.Instance     = ADC;
    hadc_3.Init.channel = ADC_CHANNEL_3;
    hadc_3.Init.freq    = 1000;    
    if (HAL_ADC_Init(&hadc_3) != HAL_OK)
    {
        Error_Handler();
    }

}

/*
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
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
*/

