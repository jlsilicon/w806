/******************************************************************************
** 
 * \file        main.c
 * \brief       Demo code of Spi Ram Ips6404
 *              
******************************************************************************/

/*

// / *
//  	#CE  \/	+Vcc 
//  	SO   	sio3 
//  	sio2 	SCLK 
//  	-Gnd 	SI   
// * /

//

#define  DATAOUT      11 //MOSI
#define  DATAIN       12 //MISO
#define  SPICLOCK     13 //sck
#define  SLAVESELECT  10 //ss

/// SEEP OpCodes : ///
//#define  WREN  6
//#define  WRDI  4
//#define  RDSR  5
//#define  WRSR  1
//#define  READ  3
//#define  WRITE 2

/// SPIRAM OpCodes : ///
#define  WREN  0x00  // 6
#define  WRDI    // 4
#define  RDSR    // 5
#define  WRSR    // 1
#define  READ  0x03  // 3
#define  WRITE 0x02  // 2
/// for Standby Mode : ///
#define  RSTE  0x66
#define  RST   0x99

byte  eeprom_output_data;
byte  eeprom_input_data = 0;
byte  clr;
long  address = 0;
/// data buffer : ///
char  buffer [128];
char  bufin[16];
//

*/


/*

// / *
//  	#CE  	1  \/	8	+Vcc 
//  	SO   	2	7	(sio3) 
//  	(sio2) 	3	6	SCLK 
//  	-Gnd 	4	5	SI   
// * /

// CS: B4, B14
#define SPIRAM6404_CS_PORT      GPIOB
#define SPIRAM6404_CS_PIN       GPIO_PIN_14

// SCK: B1, B2, B15, B24
#define SPIRAM6404_SCK_PORT     GPIOB
#define SPIRAM6404_SCK_PIN      GPIO_PIN_15

// MOSI: B5, B17, B26, PA7
#define SPIRAM6404_MOSI_PORT    GPIOB
#define SPIRAM6404_MOSI_PIN     GPIO_PIN_17

// MISO: B0, B3, B16, B25
#define SPIRAM6404_MISO_PORT    GPIOB
#define SPIRAM6404_MISO_PIN     GPIO_PIN_16

*/


#include "wm_hal.h"
#include "SpiRam6404.h"


extern  SPIRAM6404_bufStruct  SPIRAM6404_txbuff ;
extern  SPIRAM6404_bufStruct  SPIRAM6404_rxbuff ;
extern  uint8_t *  SPIRAM6404_txbuffpt ;
extern  uint8_t *  SPIRAM6404_rxbuffpt ;

////void  SPIRAM6404_Test(void);
 void  SPIRAM6404_Test(SPI_HandleTypeDef *hspi , char*bufout , char* bufin );

//

void Error_Handler(void) ;

SPI_HandleTypeDef  hspi ;

//

static void SPI_Init(void)
{
    hspi.Instance               = SPI ;
    hspi.Init.Mode              = SPI_MODE_MASTER ;
    hspi.Init.CLKPolarity       = SPI_POLARITY_LOW ;
    hspi.Init.CLKPhase          = SPI_PHASE_1EDGE ;
    hspi.Init.NSS               = SPI_NSS_SOFT ;
    hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4 ;
    hspi.Init.FirstByte         = SPI_LITTLEENDIAN ;

    if (HAL_SPI_Init(&hspi) != HAL_OK)
    {
        Error_Handler();
    }
}

//

//long  address = 0;
char*  address = 0;
/// data buffer : ///
char  bufout [128];
char  bufin  [128];

int main(void)
{
    SystemClock_Config(CPU_CLK_240M);
    SPIRAM6404_GPIO_Init();
    SPI_Init();
      ;

      while (1)
      {

        ;

        printf("\r\n");
        printf("* SpiRam: TEST1: \r\n");
        strcpy( bufout , "*** Hello SpiRam ! ***" );
        strcpy( &SPIRAM6404_txbuff  , "*** Hello SpiRam ! ***" );
        address = bufout ;
        printf("> bufout : %s \r\n", address );
        if( SPIRAM6404_write( &hspi, SPIRAM6404_CMD_R_WRITE , bufout , strlen( bufout ) ) != HAL_OK )
        {
          printf("SPIRAM6404_write(HelloSpiRam) : ERROR \n");
        }

        if( SPIRAM6404_read( &hspi, SPIRAM6404_CMD_R_READ , ( 127 ) ) != HAL_OK )
        {
          printf("SPIRAM6404_write(HelloSpiRam) : ERROR \n");
        }
        // else
        // {
          printf("<< SpiRam:IN: %s \r\n", SPIRAM6404_rxbuff.buf );
          printf("<< SpiRam:IN: %s \r\n", &SPIRAM6404_rxbuff);
          for(int i = 0; i < 32 ; i++ )
          {
            printf("%02X%c ", SPIRAM6404_rxbuff.buf[i], SPIRAM6404_rxbuff.buf[i] );
          }
          printf(" \r\n");

        // } 

        ;

        printf("* SpiRam: TEST2: \r\n");

        SPIRAM6404_Test( &hspi , bufout , bufin );


      }  // - end while(1) .

}

//

/*
void HAL_GPIO_EXTI_Callback(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin)
{
    if(
          (GPIOx == SPIRAM6404_IRQ_PORT) 
       && (GPIO_Pin == SPIRAM6404_IRQ_PIN)
      )
    {
        SPIRAM6404_handelIrqFlag(&hspi);
        for (uint8_t i = 0; i < SPIRAM6404_PLOAD_WIDTH; i++)
        {
            printf("%02X ", SPIRAM6404_rxbuff.buf[i]);
        }
        printf("\r\n");
    }
}
*/

void Error_Handler(void)
{
    while (1);
}

void assert_failed(uint8_t *file, uint32_t line)
{
    printf("Wrong parameters value: file %s on line %d\r\n", file, line);
}


///
