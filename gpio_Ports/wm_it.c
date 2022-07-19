
#include "wm_hal.h"

#define readl(addr) ({unsigned int __v = (*(volatile unsigned int *) (addr)); __v;})
__attribute__((isr)) void CORET_IRQHandler(void)
{
    readl(0xE000E010);
    HAL_IncTick();
}

__attribute__((isr)) void GPIOA_IRQHandler(void)
{

}

__attribute__((isr)) void GPIOB_IRQHandler(void)
{

}
