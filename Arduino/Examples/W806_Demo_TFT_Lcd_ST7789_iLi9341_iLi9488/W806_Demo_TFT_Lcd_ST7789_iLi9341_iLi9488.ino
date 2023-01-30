/// / tft_lcd_ST7789_iLi9341_iLi9488 / main.c : ///

///

/// redefine in LCD.h : ///
 #define  ST7789_SPI   1 
 // #define  ST7789_8080  1 
 // #define  ST7789_E     1 
// #define  ILI9341_E    1 
 #define  ILI9488_E1   1 
 // #define  ILI9488_E2   1 

//

#include <stdio.h>
// #include "wm_hal.h"
#include "lcd.h"
#include "lufei.h"
#include "pikaqiu.h"

void LCD_Init(void) ;

//

void write_pixel(unsigned short x, unsigned short y, unsigned char r, unsigned char g, unsigned char b) ;

static void GPIO_Init(void) ;

//

#if ST7789_SPI
 SPI_HandleTypeDef hspi;
 static void SPI_Init(void);
#endif
void Error_Handler(void);

//

// int main(void)
void  setup()
{
// uint16_t  x,y;

    SystemClock_Config(CPU_CLK_240M);
    printf("enter main\r\n");
    
    GPIO_Init();
#if ST7789_SPI    
    SPI_Init();
#endif
    LCD_Init();
}


void  loop()
{    
uint16_t  x,y;

    while (1)
    {

/// Clr Screen : ///
for(x=0; x<480; x++)
{
  for(y=0; y<320; y++)
  {
    write_pixel(       x ,       y, 0x00, 0x00, 0x00 );
  }
}
        LCD_DrawLine( 10, 10, 200, 200, 0xFFFF );
        LCD_DrawCircle( 100, 100, 100, 0xFF00 );
for(x=0; x<300; x++)
{
  y = x ;
  write_pixel(       x ,       y, 0xFF, 0x00, 0x00 );
  write_pixel( 300 - x ,       y, 0x00, 0xFF, 0x00 );
  write_pixel(       x ,     150, 0x00, 0x00, 0xFF );
}
        HAL_Delay(1000);

        LCD_ShowPicture(0, 40, 240, 240, gImage_pikaqiu);
        HAL_Delay(1000);

        LCD_ShowPicture(0, 40, 240, 240, gImage_lufei);
        HAL_Delay(1000);

    }
}

//

static void GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    __HAL_RCC_GPIO_CLK_ENABLE();

#if ST7789_SPI    
    GPIO_InitStruct.Pin = S_LEDA1_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(S_LEDA1_PORT, &GPIO_InitStruct);
    HAL_GPIO_WritePin(S_LEDA1_PORT, S_LEDA1_PIN, GPIO_PIN_RESET);
    
    GPIO_InitStruct.Pin = S_LEDA2_PIN;
    HAL_GPIO_Init(S_LEDA2_PORT, &GPIO_InitStruct);
    HAL_GPIO_WritePin(S_LEDA2_PORT, S_LEDA2_PIN, GPIO_PIN_RESET);
    
    GPIO_InitStruct.Pin = S_CD_PIN;
    HAL_GPIO_Init(S_CD_PORT, &GPIO_InitStruct);
    HAL_GPIO_WritePin(S_CD_PORT, S_CD_PIN, GPIO_PIN_SET);
    
    GPIO_InitStruct.Pin = S_RESET_PIN;
    HAL_GPIO_Init(S_RESET_PORT, &GPIO_InitStruct);
    HAL_GPIO_WritePin(S_RESET_PORT, S_RESET_PIN, GPIO_PIN_RESET);
    
    GPIO_InitStruct.Pin = S_FMARK_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(S_FMARK_PORT, &GPIO_InitStruct);
#endif

#if ST7789_8080
    GPIO_InitStruct.Pin = P_LEDA_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(P_LEDA_PORT, &GPIO_InitStruct);
    HAL_GPIO_WritePin(P_LEDA_PORT, P_LEDA_PIN, GPIO_PIN_SET);
    
    GPIO_InitStruct.Pin = P_RD_PIN;
    HAL_GPIO_Init(P_RD_PORT, &GPIO_InitStruct);
    HAL_GPIO_WritePin(P_RD_PORT, P_RD_PIN, GPIO_PIN_SET);
    
    GPIO_InitStruct.Pin = P_WR_PIN;
    HAL_GPIO_Init(P_WR_PORT, &GPIO_InitStruct);
    HAL_GPIO_WritePin(P_WR_PORT, P_WR_PIN, GPIO_PIN_RESET);
    
    GPIO_InitStruct.Pin = P_CD_PIN;
    HAL_GPIO_Init(P_CD_PORT, &GPIO_InitStruct);
    HAL_GPIO_WritePin(P_CD_PORT, P_CD_PIN, GPIO_PIN_SET);
    
    GPIO_InitStruct.Pin = P_CS_PIN;
    HAL_GPIO_Init(P_CS_PORT, &GPIO_InitStruct);
    HAL_GPIO_WritePin(P_CS_PORT, P_CS_PIN, GPIO_PIN_SET);
    
    GPIO_InitStruct.Pin = P_RESET_PIN;
    HAL_GPIO_Init(P_RESET_PORT, &GPIO_InitStruct);
    HAL_GPIO_WritePin(P_RESET_PORT, P_RESET_PIN, GPIO_PIN_SET);
    
    GPIO_InitStruct.Pin = P_DATA_PIN;
    HAL_GPIO_Init(P_DATA_PORT, &GPIO_InitStruct);
    HAL_GPIO_WritePin(P_DATA_PORT, P_DATA_PIN, GPIO_PIN_RESET);
    
    GPIO_InitStruct.Pin = P_FMARK_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(P_FMARK_PORT, &GPIO_InitStruct);
    
#endif

}

#if ST7789_SPI
static void SPI_Init(void)
{
    hspi.Instance = SPI;
    hspi.Init.Mode = SPI_MODE_MASTER;
    hspi.Init.CLKPolarity = SPI_POLARITY_LOW;
    hspi.Init.CLKPhase = SPI_PHASE_1EDGE;
    hspi.Init.NSS = SPI_NSS_SOFT;
    hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
    hspi.Init.FirstByte = SPI_LITTLEENDIAN;
    
    if (HAL_SPI_Init(&hspi) != HAL_OK)
    {
        Error_Handler();
    }
}
#endif

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

//
