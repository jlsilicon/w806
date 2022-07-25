
#include "wm_hal.h"
#include "SpiRam6404.h"


extern SPI_HandleTypeDef hspi;


#define readl(addr) ({unsigned int __v = (*(volatile unsigned int *) (addr)); __v;})
__attribute__((isr)) void CORET_IRQHandler(void)
{
    readl(0xE000E010);
    HAL_IncTick();
}

/*
__attribute__((isr)) void GPIOB_IRQHandler(void)
{
//	HAL_GPIO_EXTI_IRQHandler(NRF24L01_IRQ_PORT, NRF24L01_IRQ_PIN);

	HAL_GPIO_EXTI_IRQHandler(SPIRAM6404_IRQ_PORT, SPIRAM6404_IRQ_PIN);
}
*/

__attribute__((isr)) void SPI_LS_IRQHandler(void)
{
    HAL_SPI_IRQHandler(&hspi);
}

/*
__attribute__((isr)) void DMA_Channel0_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&hdma_spi_tx);
}

__attribute__((isr)) void DMA_Channel1_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&hdma_spi_rx);
}
*/
