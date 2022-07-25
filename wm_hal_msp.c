#include "wm_hal.h"
#include "SpiRam6404.h"

 
void HAL_MspInit(void)
{
 
}

void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi)
{
    __HAL_RCC_SPI_CLK_ENABLE();

////    __HAL_AFIO_REMAP_SPI_CS(GPIOB, GPIO_PIN_4);
////    __HAL_AFIO_REMAP_SPI_CLK(GPIOB, GPIO_PIN_2);
////    __HAL_AFIO_REMAP_SPI_MISO(GPIOB, GPIO_PIN_3);
////    __HAL_AFIO_REMAP_SPI_MOSI(GPIOB, GPIO_PIN_5);
    
//    __HAL_AFIO_REMAP_SPI_CS(   NRF24L01_CS_PORT  , NRF24L01_CS_PIN   );
//    __HAL_AFIO_REMAP_SPI_CLK(  NRF24L01_SCK_PORT , NRF24L01_SCK_PIN  );
//    __HAL_AFIO_REMAP_SPI_MOSI( NRF24L01_MOSI_PORT, NRF24L01_MOSI_PIN );
//    __HAL_AFIO_REMAP_SPI_MISO( NRF24L01_MISO_PORT, NRF24L01_MISO_PIN );

    __HAL_AFIO_REMAP_SPI_CS(   SPIRAM6404_CS_PORT  , SPIRAM6404_CS_PIN   );
    __HAL_AFIO_REMAP_SPI_CLK(  SPIRAM6404_SCK_PORT , SPIRAM6404_SCK_PIN  );
    __HAL_AFIO_REMAP_SPI_MOSI( SPIRAM6404_MOSI_PORT, SPIRAM6404_MOSI_PIN );
    __HAL_AFIO_REMAP_SPI_MISO( SPIRAM6404_MISO_PORT, SPIRAM6404_MISO_PIN );
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* hspi)
{
    __HAL_RCC_SPI_CLK_DISABLE();

////    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5);

//    HAL_GPIO_DeInit( NRF24L01_CS_PORT,   NRF24L01_CS_PIN   );
//    HAL_GPIO_DeInit( NRF24L01_SCK_PORT,  NRF24L01_SCK_PIN  );
//    HAL_GPIO_DeInit( NRF24L01_MOSI_PORT, NRF24L01_MOSI_PIN );
//    HAL_GPIO_DeInit( NRF24L01_MISO_PORT, NRF24L01_MISO_PIN );

    HAL_GPIO_DeInit( SPIRAM6404_CS_PORT,   SPIRAM6404_CS_PIN   );
    HAL_GPIO_DeInit( SPIRAM6404_SCK_PORT,  SPIRAM6404_SCK_PIN  );
    HAL_GPIO_DeInit( SPIRAM6404_MOSI_PORT, SPIRAM6404_MOSI_PIN );
    HAL_GPIO_DeInit( SPIRAM6404_MISO_PORT, SPIRAM6404_MISO_PIN );
}