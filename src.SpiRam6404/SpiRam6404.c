/******************************************************************************
** 
 * \file        SpiRam6404.c
 * \ingroup     demo
 * 
 *              Defined in SpiRam6404.h 
 *              SPIRAM6404_MODE:
 *                  RX mode or TX mode
 *              Pin Wiring:
 *                  // B11   -> CE
 *                  B14   -> CS, Chip Select
 *                  B15   -> SCK, SCL, CLK, Clock
 *                  B16   -> MISO
 *                  B17   -> MOSI
 *                   GND   -> GND
 *                   3.3V  -> VCC
 * 
 *              Baud rate should be under 84M (80M = prescaler = 1, 2, 4, 8 or larger)
 * 
******************************************************************************/


#include "SpiRam6404.h"
#include <stdio.h>

extern  SPI_HandleTypeDef  hspi ;

//

// uint8_t nrf24_state;
uint8_t SpiRam_state ;

SPIRAM6404_bufStruct                          SPIRAM6404_txbuff ;
SPIRAM6404_bufStruct                          SPIRAM6404_rxbuff ;
uint8_t *  SPIRAM6404_txbuffpt = (uint8_t *)(&SPIRAM6404_txbuff) ;
uint8_t *  SPIRAM6404_rxbuffpt = (uint8_t *)(&SPIRAM6404_rxbuff) ;


//

//void  SPIRAM6404_Test(void)

void  SPIRAM6404_Test(SPI_HandleTypeDef *hspi , char*bufout , char* bufin )
{
        SPIRAM6404_txbuff.opt = (uint8_t)0x02  ; // = SPIRAM6404_CMD_R_WRITE ;  // 
        memset(SPIRAM6404_txbuff.buf, 0, SPIRAM6404_PLOAD_WIDTH);
        memcpy( (SPIRAM6404_txbuff.buf + 3) , bufout , strlen(bufout) );
        printf("< SpiRam:IN: %s \r\n", (SPIRAM6404_txbuff.buf + 3));
         SPIRAM6404_CS_LOW;
         if (HAL_SPI_TransmitReceive(hspi, SPIRAM6404_txbuffpt, SPIRAM6404_rxbuffpt, (strlen(bufout) + 4), SPIRAM6404_SPI_TIMEOUT) != HAL_OK)
         {
//            return HAL_ERROR;
         }
         SPIRAM6404_CS_HIGH;

         SPIRAM6404_CS_LOW;
         SPIRAM6404_txbuff.opt = 0x03  ; // = SPIRAM6404_CMD_R_READ ;  // 
         memset(SPIRAM6404_txbuff.buf, 0, SPIRAM6404_PLOAD_WIDTH);
//         memcpy( (SPIRAM6404_txbuff.buf + 3) , bufout , (strlen(bufout) + 1) );
         if (HAL_SPI_TransmitReceive(hspi, SPIRAM6404_txbuffpt, SPIRAM6404_rxbuffpt, (strlen(bufout) + 1), SPIRAM6404_SPI_TIMEOUT) != HAL_OK)
         {
//             return HAL_ERROR;
         }
         SPIRAM6404_CS_HIGH;
        printf("< SpiRam:IN: %s \r\n", SPIRAM6404_rxbuffpt);
        for(int i = 0; i < 32 ; i++ )
        {
          printf("%02X%c ", SPIRAM6404_rxbuffpt[i], SPIRAM6404_rxbuffpt[i] );
        }
        printf(" \r\n");


        /// only Test3 - XYZ Test - sems to work : ///
        printf("* SpiRam: TEST3: \r\n");

         SPIRAM6404_CS_LOW;
        SPIRAM6404_txbuff.opt = (uint8_t)0x02  ; // = SPIRAM6404_CMD_R_WRITE ;  // 
         if (HAL_SPI_TransmitReceive(hspi, SPIRAM6404_txbuffpt, SPIRAM6404_rxbuffpt, 1 , SPIRAM6404_SPI_TIMEOUT) != HAL_OK)
         {
//            return HAL_ERROR;
         }

        SPIRAM6404_txbuff.opt = (uint8_t)0x00  ; // = SPIRAM6404_CMD_R_WRITE ;  // 
         if (HAL_SPI_TransmitReceive(hspi, SPIRAM6404_txbuffpt, SPIRAM6404_rxbuffpt, 1 , SPIRAM6404_SPI_TIMEOUT) != HAL_OK)
         {
//            return HAL_ERROR;
         }
        SPIRAM6404_txbuff.opt = (uint8_t)0x00  ; // = SPIRAM6404_CMD_R_WRITE ;  // 
         if (HAL_SPI_TransmitReceive(hspi, SPIRAM6404_txbuffpt, SPIRAM6404_rxbuffpt, 1 , SPIRAM6404_SPI_TIMEOUT) != HAL_OK)
         {
//            return HAL_ERROR;
         }
        SPIRAM6404_txbuff.opt = (uint8_t)0x00  ; // = SPIRAM6404_CMD_R_WRITE ;  // 
         if (HAL_SPI_TransmitReceive(hspi, SPIRAM6404_txbuffpt, SPIRAM6404_rxbuffpt, 1 , SPIRAM6404_SPI_TIMEOUT) != HAL_OK)
         {
//            return HAL_ERROR;
         }

        SPIRAM6404_txbuff.opt = (uint8_t)'X'  ; // = SPIRAM6404_CMD_R_WRITE ;  // 
         if (HAL_SPI_TransmitReceive(hspi, SPIRAM6404_txbuffpt, SPIRAM6404_rxbuffpt, 1 , SPIRAM6404_SPI_TIMEOUT) != HAL_OK)
         {
//            return HAL_ERROR;
         }
        SPIRAM6404_txbuff.opt = (uint8_t)'Y'  ; // = SPIRAM6404_CMD_R_WRITE ;  // 
         if (HAL_SPI_TransmitReceive(hspi, SPIRAM6404_txbuffpt, SPIRAM6404_rxbuffpt, 1 , SPIRAM6404_SPI_TIMEOUT) != HAL_OK)
         {
//            return HAL_ERROR;
         }
        SPIRAM6404_txbuff.opt = (uint8_t)'Z'  ; // = SPIRAM6404_CMD_R_WRITE ;  // 
         if (HAL_SPI_TransmitReceive(hspi, SPIRAM6404_txbuffpt, SPIRAM6404_rxbuffpt, 1 , SPIRAM6404_SPI_TIMEOUT) != HAL_OK)
         {
//            return HAL_ERROR;
         }
        SPIRAM6404_txbuff.opt = (uint8_t)0x00  ; // = SPIRAM6404_CMD_R_WRITE ;  // 
         if (HAL_SPI_TransmitReceive(hspi, SPIRAM6404_txbuffpt, SPIRAM6404_rxbuffpt, 1 , SPIRAM6404_SPI_TIMEOUT) != HAL_OK)
         {
//            return HAL_ERROR;
         }
         SPIRAM6404_CS_HIGH ;

        ;

         SPIRAM6404_CS_LOW ;
        SPIRAM6404_txbuff.opt = (uint8_t)0x03  ; // = SPIRAM6404_CMD_R_READ ;  // 
         if (HAL_SPI_TransmitReceive(hspi, SPIRAM6404_txbuffpt, SPIRAM6404_rxbuffpt, 1 , SPIRAM6404_SPI_TIMEOUT) != HAL_OK)
         {
//            return HAL_ERROR;
         }

        SPIRAM6404_txbuff.opt = (uint8_t)0x00  ; // = 0 ;  // 
         if (HAL_SPI_TransmitReceive(hspi, SPIRAM6404_txbuffpt, SPIRAM6404_rxbuffpt, 1 , SPIRAM6404_SPI_TIMEOUT) != HAL_OK)
         {
//            return HAL_ERROR;
         }
        SPIRAM6404_txbuff.opt = (uint8_t)0x00  ; // = 0 ;  // 
         if (HAL_SPI_TransmitReceive(hspi, SPIRAM6404_txbuffpt, SPIRAM6404_rxbuffpt, 1 , SPIRAM6404_SPI_TIMEOUT) != HAL_OK)
         {
//            return HAL_ERROR;
         }
        SPIRAM6404_txbuff.opt = (uint8_t)0x00  ; // = 0 ;  // 
         if (HAL_SPI_TransmitReceive(hspi, SPIRAM6404_txbuffpt, SPIRAM6404_rxbuffpt, 1 , SPIRAM6404_SPI_TIMEOUT) != HAL_OK)
         {
//            return HAL_ERROR;
         }

        SPIRAM6404_txbuff.opt = (uint8_t)0xFF  ; // = 0 ;  // 
         if (HAL_SPI_TransmitReceive(hspi, SPIRAM6404_txbuffpt, SPIRAM6404_rxbuffpt, 1 , SPIRAM6404_SPI_TIMEOUT) != HAL_OK)
         {
//            return HAL_ERROR;
         }
printf("%c%02X" , SPIRAM6404_rxbuffpt[0] , SPIRAM6404_rxbuffpt[0] );
        SPIRAM6404_txbuff.opt = (uint8_t)0xFF  ; // = 0 ;  // 
         if (HAL_SPI_TransmitReceive(hspi, SPIRAM6404_txbuffpt, SPIRAM6404_rxbuffpt, 1 , SPIRAM6404_SPI_TIMEOUT) != HAL_OK)
         {
//            return HAL_ERROR;
         }
printf("%c%02X" , SPIRAM6404_rxbuffpt[0] , SPIRAM6404_rxbuffpt[0] );
        SPIRAM6404_txbuff.opt = (uint8_t)0xFF  ; // = 0 ;  // 
         if (HAL_SPI_TransmitReceive(hspi, SPIRAM6404_txbuffpt, SPIRAM6404_rxbuffpt, 1 , SPIRAM6404_SPI_TIMEOUT) != HAL_OK)
         {
//            return HAL_ERROR;
         }
printf("%c%02X" , SPIRAM6404_rxbuffpt[0] , SPIRAM6404_rxbuffpt[0] );
        SPIRAM6404_txbuff.opt = (uint8_t)0xFF  ; // = 0 ;  // 
         if (HAL_SPI_TransmitReceive(hspi, SPIRAM6404_txbuffpt, SPIRAM6404_rxbuffpt, 1 , SPIRAM6404_SPI_TIMEOUT) != HAL_OK)
         {
//            return HAL_ERROR;
         }
printf("%c%02X" , SPIRAM6404_rxbuffpt[0] , SPIRAM6404_rxbuffpt[0] );
         SPIRAM6404_CS_HIGH;

        printf(" \r\n");
}


//


/**
 * Initialize GPIO ports
 */
void  SPIRAM6404_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIO_CLK_ENABLE();

}

/**
 * Send a one-byte command or one-byte command with one-byte argument
 */
HAL_StatusTypeDef SPIRAM6404_cmd(SPI_HandleTypeDef *hspi, uint8_t cmd, uint8_t arg)
// SPI_HandleTypeDef  SPIRAM6404_cmd(SPI_HandleTypeDef *hspi, uint8_t cmd, uint8_t arg)
{
    SPIRAM6404_txbuff.opt    = cmd;
    SPIRAM6404_txbuff.buf[0] = arg;

    SPIRAM6404_CS_LOW;
    if (HAL_SPI_TransmitReceive(hspi, SPIRAM6404_txbuffpt, SPIRAM6404_rxbuffpt, 2, SPIRAM6404_SPI_TIMEOUT) != HAL_OK)
    {
        return HAL_ERROR ;
    }
    SPIRAM6404_CS_HIGH;

    //printf("cmd %02X:%02X, rx %02X\r\n", SPIRAM6404_txbuff.opt, SPIRAM6404_txbuff.buf[0], SPIRAM6404_rxbuff.opt);
    return HAL_OK ;
}

/**
 * Send a one-byte command and read the output
 */
HAL_StatusTypeDef SPIRAM6404_read( SPI_HandleTypeDef *hspi, uint8_t cmd, uint8_t len )
// SPI_HandleTypeDef  SPIRAM6404_read( SPI_HandleTypeDef *hspi, uint8_t cmd, uint8_t len )
{
    SPIRAM6404_txbuff.opt = cmd;
    memset(SPIRAM6404_txbuff.buf, 0, len);
    memset(SPIRAM6404_rxbuff.buf, 0, len);

    SPIRAM6404_CS_LOW;
    if (HAL_SPI_TransmitReceive(hspi, SPIRAM6404_txbuffpt, SPIRAM6404_rxbuffpt, len + 1, SPIRAM6404_SPI_TIMEOUT) != HAL_OK)
    {
        return HAL_ERROR;
    }
    SPIRAM6404_CS_HIGH;

printf("<<< SpiRam:IN: %s \r\n", SPIRAM6404_rxbuffpt );
    //printf("read 0x%02X\r\n", SPIRAM6404_rxbuff.opt);
    return HAL_OK;
}

/**
 * Send a one-byte command and followed with byte array input
 */
HAL_StatusTypeDef SPIRAM6404_write( SPI_HandleTypeDef *hspi, uint8_t cmd, const uint8_t *tx, uint8_t len )
// SPI_HandleTypeDef  SPIRAM6404_write( SPI_HandleTypeDef *hspi, uint8_t cmd, const uint8_t *tx, uint8_t len )
{
    SPIRAM6404_txbuff.opt = cmd;
    memset(SPIRAM6404_txbuff.buf, 0, SPIRAM6404_PLOAD_WIDTH);
    memcpy(SPIRAM6404_txbuff.buf, tx, len);
printf(">>> SpiRam:OUT: %s \r\n", SPIRAM6404_txbuffpt );

    SPIRAM6404_CS_LOW;
    if (HAL_SPI_TransmitReceive(hspi, SPIRAM6404_txbuffpt, SPIRAM6404_rxbuffpt, len + 1, SPIRAM6404_SPI_TIMEOUT) != HAL_OK)
    {
        return HAL_ERROR;
    }
    SPIRAM6404_CS_HIGH;

    //printf("write 0x%02X\r\n", SPIRAM6404_rxbuff.opt);
    return HAL_OK;
}

//

/**
 */
HAL_StatusTypeDef SPIRAM6404_initCheck(SPI_HandleTypeDef *hspi)
// SPI_HandleTypeDef  SPIRAM6404_initCheck(SPI_HandleTypeDef *hspi)
{
    uint8_t i;
    uint8_t *addr = (uint8_t *)SPIRAM6404_TEST_ADDR;

//    if (SPIRAM6404_write(hspi, SPIRAM6404_CMD_W_REGISTER | SPIRAM6404_REG_TX_ADDR, addr, SPIRAM6404_ADDR_WIDTH) != HAL_OK)
    if (SPIRAM6404_write(hspi, SPIRAM6404_CMD_R_WRITE , addr, SPIRAM6404_ADDR_WIDTH) != HAL_OK)
    {
        return HAL_ERROR;
    }

//    if (SPIRAM6404_read(hspi, SPIRAM6404_CMD_R_REGISTER | SPIRAM6404_REG_TX_ADDR, SPIRAM6404_ADDR_WIDTH) != HAL_OK)
    if (SPIRAM6404_read(hspi, SPIRAM6404_CMD_R_READ , SPIRAM6404_ADDR_WIDTH) != HAL_OK)
    {
        return HAL_ERROR;
    }

    for (i = 0; i < SPIRAM6404_ADDR_WIDTH; i++)
    {
        if (SPIRAM6404_rxbuff.buf[i] != *addr++)
            return HAL_ERROR;
    }

    return HAL_OK;
}


void SPIRAM6404_resetTX(SPI_HandleTypeDef *hspi)
{
//    SPIRAM6404_cmd(hspi, SPIRAM6404_CMD_W_REGISTER | SPIRAM6404_REG_STATUS, SPIRAM6404_STATUS_MAX_RT); // Clear max retry flag
    SPIRAM6404_cmd(hspi, SPIRAM6404_CMD_R_RSTE , SPIRAM6404_CMD_R_RSTR ); // Clear max retry flag

//    SPIRAM6404_CE_LOW;
//    SPIRAM6404_CE_HIGH;
}


///

