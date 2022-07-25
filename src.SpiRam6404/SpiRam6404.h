/*****************************************************************************
******************************************************************************/


#ifndef ___SPIRAM6404_H___
#define ___SPIRAM6404_H___

/*

// / *
//  	#CE  \/	+Vcc 
//  	SO   	sio3 
//  	sio2 	SCLK 
//  	-Gnd 	SI   
// * /

//

#define  DATAOUT      11  // MOSI
#define  DATAIN       12  // MISO
#define  SPICLOCK     13  // sck
#define  SLAVESELECT  10  // ss

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
//  	#CE  \/	+Vcc 
//  	SO   	sio3 
//  	sio2 	SCLK 
//  	-Gnd 	SI   
// * /

// CS: B4, B14
#define SPIRAM6404_CS_PORT      GPIOB
#define SPIRAM6404_CS_PIN       GPIO_PIN_14

// SCK: B1, B2, B15, B24
#define SPIRAM6404_SCK_PORT     GPIOB
#define SPIRAM6404_SCK_PIN      GPIO_PIN_15

// MISO: B0, B3, B16, B25
#define SPIRAM6404_MISO_PORT    GPIOB
#define SPIRAM6404_MISO_PIN     GPIO_PIN_16

// MOSI: B5, B17, B26, PA7
#define SPIRAM6404_MOSI_PORT    GPIOB
#define SPIRAM6404_MOSI_PIN     GPIO_PIN_17

*/

#include "wm_hal.h"


// #define SPIRAM6404_MODE         SPIRAM6404_modeRX


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

// #define SPIRAM6404_IRQn         GPIOB_IRQn
// #define SPIRAM6404_IRQ_PORT     GPIOB
// #define SPIRAM6404_IRQ_PIN      GPIO_PIN_10

// #define SPIRAM6404_CE_PORT      GPIOB
// #define SPIRAM6404_CE_PIN       GPIO_PIN_11

#define SPIRAM6404_CS_LOW       __HAL_SPI_SET_CS_LOW(hspi)
#define SPIRAM6404_CS_HIGH      __HAL_SPI_SET_CS_HIGH(hspi)

// #define SPIRAM6404_CE_LOW       HAL_GPIO_WritePin(SPIRAM6404_CE_PORT, SPIRAM6404_CE_PIN, GPIO_PIN_RESET)
// #define SPIRAM6404_CE_HIGH      HAL_GPIO_WritePin(SPIRAM6404_CE_PORT, SPIRAM6404_CE_PIN, GPIO_PIN_SET)

// #define SPIRAM6404_IRQ          HAL_GPIO_ReadPin(NRF24_GPIOx,NRF24_PIN_IRQ)

#define SPIRAM6404_ADDR_WIDTH         5    // RX/TX address width
#define SPIRAM6404_PLOAD_WIDTH        32   // Payload width
#define SPIRAM6404_SPI_TIMEOUT        500  // milliseconds
#define SPIRAM6404_TEST_ADDR          "nRF24"


#pragma pack(push, 1)

typedef struct{
	uint8_t     opt;
	uint8_t     buf[SPIRAM6404_PLOAD_WIDTH];
} SPIRAM6404_bufStruct ;

#pragma pack(pop)


typedef enum
{
  SPIRAM6404_modeRX  = 0x00,
  SPIRAM6404_modeTX  = 0x01
} SPIRAM6404_mode;

//

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

//  SPI/QPI PSRAM device is byte−addressable. 64M device is addressed with A[22:0] 
//  The page size is 1K Bytes. Read and write operations are always linear address space 

// SPI(SPIRAM6404) commands
// #define SPIRAM6404_CMD_R_REGISTER     0x00 // Register read (use with registers)

// Register CONFIG bits definitions
//#define SPIRAM6404_CONFIG_PRIM_RX     0x01 // PRIM_RX bit in CONFIG register

// Register FEATURE bits definitions
//#define SPIRAM6404_FEATURE_EN_DYN_ACK 0x01 // EN_DYN_ACK bit in FEATURE register, enables the W_TX_PAYLOAD_NOACK command

// Register STATUS bits definitions
//#define SPIRAM6404_STATUS_RX_DR       0x40 // RX_DR bit (data ready RX FIFO interrupt)

// Register Read ID definitions : 
#define SPIRAM6404_READID_PASS    0x5D // Read ID Pass Result 
#define SPIRAM6404_READID_FAIL    0x55 // Read ID Fail Result 

// #define SPIRAM6404_CMD_C_WREN     0x06 // Write Enable 
#define SPIRAM6404_CMD_C_WREN     0x00 // Write Enable 
// #define SPIRAM6404_CMD_C_WRDI     0x04 // Write Data Ins 
// #define SPIRAM6404_CMD_R_RDSR     0x05 // Read Status Reg 
// #define SPIRAM6404_CMD_R_WRSR     0x01 // Write Status Reg 
#define SPIRAM6404_CMD_R_READ     0x03 // Read Data 
#define SPIRAM6404_CMD_R_WRITE    0x02 // Write Data 
#define SPIRAM6404_CMD_R_RSTE     0x66 // Standby Reset Enable 
#define SPIRAM6404_CMD_R_RSTR     0x99 // Standby Reset 

#define SPIRAM6404_CMD_R_FREAD    0x0B // Fast Read Data 
// #define SPIRAM6404_CMD_R_QUADWRITE   0x38 // QuadWrite Data 
#define SPIRAM6404_CMD_R_READID   0x9F // Read ID 

#define SPIRAM6404_CMD_NOP        0xFF // No operation (used for reading status register)

//

void  SPIRAM6404_GPIO_Init(void) ;

HAL_StatusTypeDef SPIRAM6404_cmd(SPI_HandleTypeDef *hspi, uint8_t cmd, uint8_t arg);
HAL_StatusTypeDef SPIRAM6404_read(SPI_HandleTypeDef *hspi, uint8_t cmd, uint8_t len);
HAL_StatusTypeDef SPIRAM6404_write(SPI_HandleTypeDef *hspi, uint8_t cmd, const uint8_t *tx, uint8_t len);
HAL_StatusTypeDef SPIRAM6404_initCheck(SPI_HandleTypeDef *hspi);

HAL_StatusTypeDef SPIRAM6404_config(SPI_HandleTypeDef *hspi, uint8_t *tx_addr, uint8_t *rx_addr);

// .

#endif


