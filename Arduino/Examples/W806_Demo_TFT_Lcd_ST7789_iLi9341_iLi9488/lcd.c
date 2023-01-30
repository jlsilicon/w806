///
/// LCD.C : St7789 / iLi9341 : ///
///

#include "lcd.h"


#ifdef  ILI9341_E

#define ILI9341_CMD_NOP                             0x00
#define ILI9341_CMD_SOFTWARE_RESET                  0x01
#define ILI9341_CMD_READ_DISP_ID                    0x04
#define ILI9341_CMD_READ_DISP_STATUS                0x09
#define ILI9341_CMD_READ_DISP_MADCTRL               0x0B
#define ILI9341_CMD_READ_DISP_PIXEL_FORMAT          0x0C
#define ILI9341_CMD_READ_DISP_IMAGE_FORMAT          0x0D
#define ILI9341_CMD_READ_DISP_SIGNAL_MODE           0x0E
#define ILI9341_CMD_READ_DISP_SELF_DIAGNOSTIC       0x0F
#define ILI9341_CMD_ENTER_SLEEP_MODE                0x10
#define ILI9341_CMD_SLEEP_OUT                       0x11
#define ILI9341_CMD_PARTIAL_MODE_ON                 0x12
#define ILI9341_CMD_NORMAL_DISP_MODE_ON             0x13
#define ILI9341_CMD_DISP_INVERSION_OFF              0x20
#define ILI9341_CMD_DISP_INVERSION_ON               0x21
#define ILI9341_CMD_GAMMA_SET                       0x26
#define ILI9341_CMD_DISPLAY_OFF                     0x28
#define ILI9341_CMD_DISPLAY_ON                      0x29
#define ILI9341_CMD_COLUMN_ADDRESS_SET              0x2A
#define ILI9341_CMD_PAGE_ADDRESS_SET                0x2B
#define ILI9341_CMD_MEMORY_WRITE                    0x2C
#define ILI9341_CMD_COLOR_SET                       0x2D
#define ILI9341_CMD_MEMORY_READ                     0x2E
#define ILI9341_CMD_PARTIAL_AREA                    0x30
#define ILI9341_CMD_VERT_SCROLL_DEFINITION          0x33
#define ILI9341_CMD_TEARING_EFFECT_LINE_OFF         0x34
#define ILI9341_CMD_TEARING_EFFECT_LINE_ON          0x35
#define ILI9341_CMD_MEMORY_ACCESS_CONTROL           0x36
#define ILI9341_CMD_VERT_SCROLL_START_ADDRESS       0x37
#define ILI9341_CMD_IDLE_MODE_OFF                   0x38
#define ILI9341_CMD_IDLE_MODE_ON                    0x39
#define ILI9341_CMD_COLMOD_PIXEL_FORMAT_SET         0x3A
#define ILI9341_CMD_WRITE_MEMORY_CONTINUE           0x3C
#define ILI9341_CMD_READ_MEMORY_CONTINUE            0x3E
#define ILI9341_CMD_SET_TEAR_SCANLINE               0x44
#define ILI9341_CMD_GET_SCANLINE                    0x45
#define ILI9341_CMD_WRITE_DISPLAY_BRIGHTNESS        0x51
#define ILI9341_CMD_READ_DISPLAY_BRIGHTNESS         0x52
#define ILI9341_CMD_WRITE_CTRL_DISPLAY              0x53
#define ILI9341_CMD_READ_CTRL_DISPLAY               0x54
#define ILI9341_CMD_WRITE_CONTENT_ADAPT_BRIGHTNESS  0x55
#define ILI9341_CMD_READ_CONTENT_ADAPT_BRIGHTNESS   0x56
#define ILI9341_CMD_WRITE_MIN_CAB_LEVEL             0x5E
#define ILI9341_CMD_READ_MIN_CAB_LEVEL              0x5F
 #define ILI9341_CMD_READ_XD3                        0xD3
 #define ILI9341_CMD_READ_XD9                        0xD9
#define ILI9341_CMD_READ_ID1                        0xDA
#define ILI9341_CMD_READ_ID2                        0xDB
#define ILI9341_CMD_READ_ID3                        0xDC

#endif  // - end ILI9341_E . //


#ifdef  ILI9488_E2

#ifndef DRIVERS_GFX_ILI9488_ILI9488_REGS_H_INCLUDED
#define DRIVERS_GFX_ILI9488_ILI9488_REGS_H_INCLUDED

/* Level 1 Commands (from the display Datasheet) */
#define ILI9488_CMD_NOP                             0x00
#define ILI9488_CMD_SOFTWARE_RESET                  0x01
#define ILI9488_CMD_READ_DISP_ID                    0x04
#define ILI9488_CMD_READ_DSI_ERRORS                 0x05
#define ILI9488_CMD_READ_DISP_STATUS                0x09
#define ILI9488_CMD_READ_DISP_POWER_MODE            0x0A
#define ILI9488_CMD_READ_DISP_MADCTRL               0x0B
#define ILI9488_CMD_READ_DISP_PIXEL_FORMAT          0x0C
#define ILI9488_CMD_READ_DISP_IMAGE_MODE            0x0D
#define ILI9488_CMD_READ_DISP_SIGNAL_MODE           0x0E
#define ILI9488_CMD_READ_DISP_SELF_DIAGNOSTIC       0x0F
#define ILI9488_CMD_SLEEP_IN                        0x10
#define ILI9488_CMD_SLEEP_OUT                       0x11
#define ILI9488_CMD_PARTIAL_MODE_ON                 0x12
#define ILI9488_CMD_NORMAL_DISP_MODE_ON             0x13
#define ILI9488_CMD_DISP_INVERSION_OFF              0x20
#define ILI9488_CMD_DISP_INVERSION_ON               0x21
#define ILI9488_CMD_ALL_PIXELS_OFF                  0x22
#define ILI9488_CMD_ALL_PIXELS_ON                   0x23
#define ILI9488_CMD_DISPLAY_OFF                     0x28
#define ILI9488_CMD_DISPLAY_ON                      0x29
#define ILI9488_CMD_COLUMN_ADDRESS_SET              0x2A
#define ILI9488_CMD_PAGE_ADDRESS_SET                0x2B
#define ILI9488_CMD_MEMORY_WRITE                    0x2C
#define ILI9488_CMD_MEMORY_READ                     0x2E
#define ILI9488_CMD_PARTIAL_AREA                    0x30
#define ILI9488_CMD_VERT_SCROLL_DEFINITION          0x33
#define ILI9488_CMD_TEARING_EFFECT_LINE_OFF         0x34
#define ILI9488_CMD_TEARING_EFFECT_LINE_ON          0x35
#define ILI9488_CMD_MEMORY_ACCESS_CONTROL           0x36
#define ILI9488_CMD_VERT_SCROLL_START_ADDRESS       0x37
#define ILI9488_CMD_IDLE_MODE_OFF                   0x38
#define ILI9488_CMD_IDLE_MODE_ON                    0x39
#define ILI9488_CMD_INTERFACE_PIXEL_FORMAT          0x3A
#define ILI9488_CMD_WRITE_MEMORY_CONTINUE           0x3C
#define ILI9488_CMD_READ_MEMORY_CONTINUE            0x3E
#define ILI9488_CMD_WRITE_TEAR_SCANLINE             0x44
#define ILI9488_CMD_READ_TEAR_SCANLINE              0x45
#define ILI9488_CMD_WRITE_DISPLAY_BRIGHTNESS        0x51
#define ILI9488_CMD_READ_DISPLAY_BRIGHTNESS         0x52
#define ILI9488_CMD_WRITE_CTRL_DISPLAY              0x53
#define ILI9488_CMD_READ_CTRL_DISPLAY               0x54
#define ILI9488_CMD_WRITE_CONTENT_ADAPT_BRIGHTNESS  0x55
#define ILI9488_CMD_READ_CONTENT_ADAPT_BRIGHTNESS   0x56
#define ILI9488_CMD_WRITE_MIN_CAB_LEVEL             0x5E
#define ILI9488_CMD_READ_MIN_CAB_LEVEL              0x5F
#define ILI9488_CMD_READ_BRIGHTNESS_DIAG_RESULT     0x68
#define ILI9488_CMD_READ_ID1                        0xDA
#define ILI9488_CMD_READ_ID2                        0xDB
#define ILI9488_CMD_READ_ID3                        0xDC

/* Level 2 Commands (from the display Datasheet) */
#define ILI9488_CMD_INTERFACE_MODE_CONTROL          0xB0
#define ILI9488_CMD_FRAME_RATE_CONTROL_NORMAL       0xB1
#define ILI9488_CMD_FRAME_RATE_CONTROL_IDLE_8COLOR  0xB2
#define ILI9488_CMD_FRAME_RATE_CONTROL_PARTIAL      0xB3
#define ILI9488_CMD_DISPLAY_INVERSION_CONTROL       0xB4
#define ILI9488_CMD_BLANKING_PORCH_CONTROL          0xB5
#define ILI9488_CMD_DISPLAY_FUNCTION_CONTROL        0xB6
#define ILI9488_CMD_ENTRY_MODE_SET                  0xB7
#define ILI9488_CMD_COLOR_ENHANCEMENT_CTRL_1        0xB9
#define ILI9488_CMD_COLOR_ENHANCEMENT_CTRL_2        0xBA
#define ILI9488_CMD_HS_LANES_CONTROL                0xBE
#define ILI9488_CMD_POWER_CONTROL_1                 0xC0
#define ILI9488_CMD_POWER_CONTROL_2                 0xC1
#define ILI9488_CMD_POWER_CONTROL_3                 0xC2
#define ILI9488_CMD_POWER_CONTROL_4                 0xC3
#define ILI9488_CMD_POWER_CONTROL_5                 0xC4
#define ILI9488_CMD_VCOM_CONTROL_1                  0xC5
#define ILI9488_CMD_CABC_CONTROL_1                  0xC6
#define ILI9488_CMD_CABC_CONTROL_2                  0xC8
#define ILI9488_CMD_CABC_CONTROL_3                  0xC9
#define ILI9488_CMD_CABC_CONTROL_4                  0xCA
#define ILI9488_CMD_CABC_CONTROL_5                  0xCB
#define ILI9488_CMD_CABC_CONTROL_6                  0xCC
#define ILI9488_CMD_CABC_CONTROL_7                  0xCD
#define ILI9488_CMD_CABC_CONTROL_8                  0xCE
#define ILI9488_CMD_CABC_CONTROL_9                  0xCF
#define ILI9488_CMD_NVMEM_WRITE                     0xD0
#define ILI9488_CMD_NVMEM_PROTECTION_KEY            0xD1
#define ILI9488_CMD_NVMEM_STATUS_READ               0xD2
#define ILI9488_CMD_READ_ID4                        0xD3
#define ILI9488_CMD_ADJUST_CONTROL_1                0xD7
#define ILI9488_CMD_READ_ID4_CHECK                  0xD8
#define ILI9488_CMD_POSITIVE_GAMMA_CTRL             0xE0
#define ILI9488_CMD_NEGATIVE_GAMMA_CTRL             0xE1
#define ILI9488_CMD_DIGITAL_GAMMA_CONTROL_1         0xE2
#define ILI9488_CMD_DIGITAL_GAMMA_CONTROL_2         0xE3
#define ILI9488_CMD_SET_IMAGE_FUNCTION              0xE9
#define ILI9488_CMD_ADJUST_CONTROL_2                0xF2
#define ILI9488_CMD_ADJUST_CONTROL_3                0xF7
#define ILI9488_CMD_ADJUST_CONTROL_4                0xF8
#define ILI9488_CMD_ADJUST_CONTROL_5                0xF9
#define ILI9488_CMD_SPI_READ_CMD_SETTING            0xFB
#define ILI9488_CMD_ADJUST_CONTROL_6                0xFC
#define ILI9488_CMD_ADJUST_CONTROL_7                0xFF

#endif /* DRIVERS_GFX_ILI9488_ILI9488_REGS_H_INCLUDED */

#endif  // - end ILI9488_E2 . //


//


///
void LCD_Reset_On(void)
{
#if ST7789_SPI
    S_RESET_LOW;
#endif
#if ST7789_8080
    P_RESET_LOW;
#endif
}

///
void LCD_Reset_Off(void)
{
#if ST7789_SPI
    S_RESET_HIGH;
#endif
#if ST7789_8080
    P_RESET_HIGH;
#endif
}

///
void LCD_Back_On(void)
{
#if ST7789_SPI
    S_Back_On();
#endif
#if ST7789_8080
    P_Back_On();
#endif
}

///
void LCD_Back_Off(void)
{
#if ST7789_SPI
    S_Back_Off();
#endif
#if ST7789_8080
    P_Back_Off();
#endif
}

///
static void LCD_WriteReg(uint8_t reg)
{
#if ST7789_SPI
    S_WriteReg(reg);
#endif
#if ST7789_8080
    P_WriteReg(reg);
#endif
}

///
static void LCD_WriteData8(uint8_t data)
{
#if ST7789_SPI
    S_WriteData8(data);
#endif
#if ST7789_8080
    P_WriteData8(data);
#endif
}

///
static void LCD_WriteData16(uint16_t data)
{
#if ST7789_SPI
    S_WriteData16(data);
#endif
#if ST7789_8080
    P_WriteData16(data);
#endif
}

///
static void LCD_WriteData(uint8_t *data, uint32_t len)
{
    uint32_t t1 = 0, t2 = 0;
    
#if ST7789_SPI
    t1 = HAL_GetTick();
    S_WriteData(data, len);
    t2 = HAL_GetTick();
    printf("s_t = %d\r\n", t2 - t1);
#endif
#if ST7789_8080
    t1 = HAL_GetTick();
    P_WriteData(data, len);
    t2 = HAL_GetTick();
    printf("p_t = %d\r\n", t2 - t1);
#endif
}


 // #define  ST7789_E
 // #define  ILI9341_E
 #define  ILI9488_E1 
 // #define  ILI9488_E2 


/// LCD INIT : ///
void LCD_Init(void)
{

#ifdef  ST7789_E

    LCD_Reset_On();
    HAL_Delay(120);
    LCD_Reset_Off();
    HAL_Delay(120);
    LCD_Back_On();
    HAL_Delay(100);
    LCD_WriteReg(0x11);
    HAL_Delay(120);
    
    LCD_WriteReg(0x36);    // left->right top->bottom
    LCD_WriteData8(0x00);
    
    LCD_WriteReg(0x3A);    // rgb565
    LCD_WriteData8(0x05);
    
    LCD_WriteReg(0xB2);
    LCD_WriteData8(0x0C);
    LCD_WriteData8(0x0C);
    LCD_WriteData8(0x00);
    LCD_WriteData8(0x33);
    LCD_WriteData8(0x33);
    
    LCD_WriteReg(0xB7);
    LCD_WriteData8(0x35);
    
    LCD_WriteReg(0xBB);
    LCD_WriteData8(0x19);
    
    LCD_WriteReg(0xC0);
    LCD_WriteData8(0x2C);
    
    LCD_WriteReg(0xC2);
    LCD_WriteData8(0x01);
    
    LCD_WriteReg(0xC3);
    LCD_WriteData8(0x12);
    
    LCD_WriteReg(0xC4);
    LCD_WriteData8(0x20);
    
    LCD_WriteReg(0xC6);
    LCD_WriteData8(0x0F);
    
    LCD_WriteReg(0xD0);
    LCD_WriteData8(0xA4);
    LCD_WriteData8(0xA1);
    
    LCD_WriteReg(0xE0);
    LCD_WriteData8(0xD0);
    LCD_WriteData8(0x04);
    LCD_WriteData8(0x0D);
    LCD_WriteData8(0x11);
    LCD_WriteData8(0x13);
    LCD_WriteData8(0x2B);
    LCD_WriteData8(0x3F);
    LCD_WriteData8(0x54);
    LCD_WriteData8(0x4C);
    LCD_WriteData8(0x18);
    LCD_WriteData8(0x0D);
    LCD_WriteData8(0x0B);
    LCD_WriteData8(0x1F);
    LCD_WriteData8(0x23);
    
    LCD_WriteReg(0xE1);
    LCD_WriteData8(0xD0);
    LCD_WriteData8(0x04);
    LCD_WriteData8(0x0C);
    LCD_WriteData8(0x11);
    LCD_WriteData8(0x13);
    LCD_WriteData8(0x2C);
    LCD_WriteData8(0x3F);
    LCD_WriteData8(0x44);
    LCD_WriteData8(0x51);
    LCD_WriteData8(0x2F);
    LCD_WriteData8(0x1F);
    LCD_WriteData8(0x1F);
    LCD_WriteData8(0x20);
    LCD_WriteData8(0x23);
    
    LCD_WriteReg(0x21);
    LCD_WriteReg(0x29);

#else
 #ifdef  ILI9341_E

   LCD_Reset_On();
   HAL_Delay(120);

   LCD_Reset_Off();
   HAL_Delay(120);

   LCD_Back_On();
   HAL_Delay(100);

//    LCD_WriteReg(0x11);
    /// ILI9341_CMD_SOFTWARE_RESET : ///
    LCD_WriteReg(0x01);
    LCD_WriteData8(0x00);
   HAL_Delay(120);
    
    LCD_WriteReg(0x36);  LCD_WriteData8(0x00);  LCD_WriteData8(0x00);
    
//

    /// ILI9341_CMD_POWER_CONTROL_B : ///
//    (0xCF), 3,                  //ILI9341_CMD_POWER_CONTROL_B
//    0x00, 0x8B, 0x30,
    LCD_WriteReg(0xCF);  LCD_WriteData8(0x00);  LCD_WriteData8(0x8B);  LCD_WriteData8(0x30);

//    (0xED), 4,                  //ILI9341_CMD_POWER_ON_SEQ_CONTROL
//    0x67, 0x03, 0x12, 0x81,
    LCD_WriteReg(0xED);  LCD_WriteData8(0x67);  LCD_WriteData8(0x03);  LCD_WriteData8(0x12);  LCD_WriteData8(0x81);

//    (0xE8), 3,                  //ILI9341_CMD_DRIVER_TIMING_CONTROL_A
//    0x85, 0x10, 0x7A,
    LCD_WriteReg(0xE8);  LCD_WriteData8(0x85);  LCD_WriteData8(0x10);  LCD_WriteData8(0x7A);

//    (0xCB), 5,                  //ILI9341_CMD_POWER_CONTROL_A
//    0x39, 0x2C, 0x00, 0x34, 0x02,
    LCD_WriteReg(0xCB);  LCD_WriteData8(0x39);  LCD_WriteData8(0x2C);  LCD_WriteData8(0x00);  LCD_WriteData8(0x34);  LCD_WriteData8(0x02);

//    (0xF7), 1,                  //ILI9341_CMD_PUMP_RATIO_CONTROL
//    0x20,
    LCD_WriteReg(0xF7);  LCD_WriteData8(0x20);

//    (0xEA), 2,                  //ILI9341_CMD_DRIVER_TIMING_CONTROL_B
//    0x00, 0x00,
    LCD_WriteReg(0xEA);  LCD_WriteData8(0x00);  LCD_WriteData8(0x00);

//    (0xC0), 1,                  //ILI9341_CMD_POWER_CONTROL_1
//    0x1B,                       /* VRH[5:0]                     */
    LCD_WriteReg(0xC0);  LCD_WriteData8(0x1B);

//    (0xC1), 1,                  //ILI9341_CMD_POWER_CONTROL_2
//    0x10,                       /* SAP[2:0];BT[3:0]             */
    LCD_WriteReg(0xC1);  LCD_WriteData8(0x10);

//    (0xC5), 2,                  //ILI9341_CMD_VCOM_CONTROL_1
//    0x3F, 0x3C,
    LCD_WriteReg(0xC5);  LCD_WriteData8(0x3F);  LCD_WriteData8(0x3C);

//    (0xC7), 1,                  //ILI9341_CMD_VCOM_CONTROL_2
//    0xB7,
    LCD_WriteReg(0xC7);  LCD_WriteData8(0xB7);

//    (0x36), 1,                  //ILI9341_CMD_MEMORY_ACCESS_CONTROL
//    0x08,
    LCD_WriteReg(0x36);  LCD_WriteData8(0x08);

//    (0x3A), 1,                  //ILI9341_CMD_COLMOD_PIXEL_FORMAT_SET
//    0x55,
    LCD_WriteReg(0x3A);  LCD_WriteData8(0x55);

//    (0xB1), 2,                  //ILI9341_CMD_FRAME_RATE_CONTROL_NORMAL
//    0x00, 0x1B,
    LCD_WriteReg(0xB1);  LCD_WriteData8(0x00);  LCD_WriteData8(0x1B);

//    (0xB4), 1, 0x00,            //Inversion Control [02] .kbv NLA=1, NLB=1, NLC=1  Extended anyway
    LCD_WriteReg(0xB4);  LCD_WriteData8(0x00);

//    (0xB6), 2,                  //ILI9341_CMD_DISPLAY_FUNCTION_CONTROL
//    0x0A, 0xA2,
    LCD_WriteReg(0xB6);  LCD_WriteData8(0x0A);  LCD_WriteData8(0xA2);

//    (0xF2), 1,                  //ILI9341_CMD_ENABLE_3_GAMMA_CONTROL
//    0x00,                       /* 3Gamma Function Disable      */
    LCD_WriteReg(0xF2);  LCD_WriteData8(0x00);

//    (0x26), 1,                  //ILI9341_CMD_GAMMA_SET
//    0x01,
    LCD_WriteReg(0x26);  LCD_WriteData8(0x01);

//    (0xE0), 15,                 //ILI9341_CMD_POSITIVE_GAMMA_CORRECTION
//    0x0F, 0x2A, 0x28, 0x08, 0x0E, 0x08, 0x54, 0XA9, 0x43, 0x0A, 0x0F, 0x00,
//    0x00, 0x00, 0x00,
    LCD_WriteReg(0xE0);  LCD_WriteData8(0x0F);  LCD_WriteData8(0x2A);  
                         LCD_WriteData8(0x28);  LCD_WriteData8(0x08);
                         LCD_WriteData8(0x0E);  LCD_WriteData8(0x08);
                         LCD_WriteData8(0x54);  LCD_WriteData8(0xA9);
                         LCD_WriteData8(0x43);  LCD_WriteData8(0x0A);
                         LCD_WriteData8(0x0F);  LCD_WriteData8(0x00);
                         LCD_WriteData8(0x00);  LCD_WriteData8(0x00);
                         LCD_WriteData8(0x00);  

//    (0xE1), 15,                 //ILI9341_CMD_NEGATIVE_GAMMA_CORRECTION
//    0x00, 0x15, 0x17, 0x07, 0x11, 0x06, 0x2B, 0x56, 0x3C, 0x05, 0x10, 0x0F,
//    0x3F, 0x3F, 0x0F,
    LCD_WriteReg(0xE1);  LCD_WriteData8(0x00);  LCD_WriteData8(0x15);  
                         LCD_WriteData8(0x17);  LCD_WriteData8(0x07);
                         LCD_WriteData8(0x11);  LCD_WriteData8(0x06);
                         LCD_WriteData8(0x2B);  LCD_WriteData8(0x56);
                         LCD_WriteData8(0x3C);  LCD_WriteData8(0x05);
                         LCD_WriteData8(0x10);  LCD_WriteData8(0x0F);
                         LCD_WriteData8(0x3F);  LCD_WriteData8(0x3F);
                         LCD_WriteData8(0x0F);  

//    (0x11), 0,             //ILI9341_CMD_SLEEP_OUT
    LCD_WriteReg(0x11);

//            TFTLCD_DELAY8, 150,   // .kbv
   HAL_Delay(150);

//    (0x29), 0,                  //ILI9341_CMD_DISPLAY_ON
    LCD_WriteReg(0x29);

//

 #else

  #ifdef  ILI9488_E1

/// _Using_the_TFTLCD_ILI9488_InitFn.c : ///

//    // reset LCD
//    P2OUT &= (~LCD_RST);
    LCD_Reset_On();
     HAL_Delay(120);

//    delay_ms(100);
//    P2OUT |= (LCD_RST);
    LCD_Reset_Off();
     HAL_Delay(120);

    LCD_Back_On();
     HAL_Delay(100);


//    // software reset
//    send_command(0x01);
//    delay_ms(100);
    LCD_WriteReg(0x01);
     HAL_Delay(120);

//    // sleep out
//    send_command(0x11);
//    delay_ms(100);
    LCD_WriteReg(0x11);
     HAL_Delay(120);

//    // memory acces control
//    send_command(0x36);
//    send_data(0xE8);
//    delay_ms(100);
    LCD_WriteReg(0x36);
    LCD_WriteData8(0xE8);
     HAL_Delay(100);

//    // set dbi
//    send_command(0x3A);
//    send_data(0x06);
//    delay_ms(100);
    LCD_WriteReg(0x3A);
    LCD_WriteData8(0x06);
     HAL_Delay(100);

//    // partial mode on
//    send_command(0x12);
//    delay_ms(100);
    LCD_WriteReg(0x12);
     HAL_Delay(100);

//    // display on
//    send_command(0x29);
//    delay_ms(100);
    LCD_WriteReg(0x29);
     HAL_Delay(100);

//    // set cursor
//    send_command(0x2A);
    LCD_WriteReg(0x2A);
//    // set start x
//    send_data(0x06);
//    send_data(0x06);
    LCD_WriteData8(0x06);
    LCD_WriteData8(0x06);
//    // set end x
//    send_data(0x01);
//    send_data(0xDF);
    LCD_WriteData8(0x01);
    LCD_WriteData8(0xDF);
//    send_command(0x00);
    LCD_WriteReg(0x00);

//    send_command(0x2B);
    LCD_WriteReg(0x2B);
//    // set start y
//    send_data(0x00);
//    send_data(0x00);
    LCD_WriteData8(0x00);
    LCD_WriteData8(0x00);
//    // set end y
//    send_data(0x01);
//    send_data(0x3F);
    LCD_WriteData8(0x01);
    LCD_WriteData8(0x3F);
//    send_command(0x00);
    LCD_WriteReg(0x00);

//    delay_ms(100);
     HAL_Delay(100);

//    // set brightness
//    send_command(0x51);
//    send_data(0x0F);
//    delay_ms(100);
    LCD_WriteReg(0x51);
    LCD_WriteData8(0x0F);
     HAL_Delay(100);

//    // set brightness control
//    send_command(0x53);
//    send_data(0x2C);
//    delay_ms(100);
    LCD_WriteReg(0x53);
    LCD_WriteData8(0x2C);
     HAL_Delay(100);

//    // set framerate
//    send_command(0xB1);
//    send_data(0xB0);
//    send_data(0x11);
//    delay_ms(50);
    LCD_WriteReg(0xB1);
    LCD_WriteData8(0xB0);
    LCD_WriteData8(0x11);
     HAL_Delay(50);

//    set_bgcolor(0, 0, 0);

//    P2OUT |= (LCD_CS);
//    delay_ms(100);

  #else

   #ifdef  ILI9488_E2

//	// PGAMCTRL - Positive Gamma Control
////                 #define ILI9488_CMD_POSITIVE_GAMMA_CTRL             0xE0
//	ili9488_send_command(ILI9488_CMD_POSITIVE_GAMMA_CTRL);
//	ili9488_send_byte(0x00);
//	ili9488_send_byte(0x07);
//	ili9488_send_byte(0x0f);
//	ili9488_send_byte(0x0D);
//	ili9488_send_byte(0x1B);
//	ili9488_send_byte(0x0A);
//	ili9488_send_byte(0x3c);
//	ili9488_send_byte(0x78);
//	ili9488_send_byte(0x4A);
//	ili9488_send_byte(0x07);
//	ili9488_send_byte(0x0E);
//	ili9488_send_byte(0x09);
//	ili9488_send_byte(0x1B);
//	ili9488_send_byte(0x1e);
//	ili9488_send_byte(0x0f);
//	ili9488_wait_for_send_done();
//	ili9488_deselect_chip();

//	// NGAMCTRL - Negative Gamma Control
////                 #define ILI9488_CMD_NEGATIVE_GAMMA_CTRL             0xE1
//	ili9488_send_command(ILI9488_CMD_NEGATIVE_GAMMA_CTRL);
//	ili9488_send_byte(0x00);
//	ili9488_send_byte(0x22);
//	ili9488_send_byte(0x24);
//	ili9488_send_byte(0x06);
//	ili9488_send_byte(0x12);
//	ili9488_send_byte(0x07);
//	ili9488_send_byte(0x36);
//	ili9488_send_byte(0x47);
//	ili9488_send_byte(0x47);
//	ili9488_send_byte(0x06);
//	ili9488_send_byte(0x0a);
//	ili9488_send_byte(0x07);
//	ili9488_send_byte(0x30);
//	ili9488_send_byte(0x37);
//	ili9488_send_byte(0x0f);
//	ili9488_wait_for_send_done();
//	ili9488_deselect_chip();

//	// Power Control 1
////                 #define ILI9488_CMD_POWER_CONTROL_1                 0xC0
//	ili9488_send_command(ILI9488_CMD_POWER_CONTROL_1);
//	ili9488_send_byte(0x10);
//	ili9488_send_byte(0x10);
//	ili9488_wait_for_send_done();
//	ili9488_deselect_chip();

//	// Power Control 2
////                 #define ILI9488_CMD_POWER_CONTROL_2                 0xC1
//	ili9488_send_command(ILI9488_CMD_POWER_CONTROL_2);
//	ili9488_send_byte(0x41);
//	ili9488_wait_for_send_done();
//	ili9488_deselect_chip();

//	// VCOM Control
////                 #define ILI9488_CMD_VCOM_CONTROL_1                  0xC5
//	ili9488_send_command(ILI9488_CMD_VCOM_CONTROL_1);
//	ili9488_send_byte(0x00);
//	ili9488_send_byte(0x22);
//	ili9488_send_byte(0x80);
//	ili9488_wait_for_send_done();
//	ili9488_deselect_chip();
   
//	// Memory Access Control
////                 #define ILI9488_CMD_MEMORY_ACCESS_CONTROL           0x36
//	ili9488_send_command(ILI9488_CMD_MEMORY_ACCESS_CONTROL);
//	ili9488_send_byte(0x68);
//	ili9488_wait_for_send_done();
//	ili9488_deselect_chip();

//	//Interface Mode Control
//	// Set up used SPI lines and RGB interface
////                 #define ILI9488_CMD_INTERFACE_MODE_CONTROL          0xB0
//	ili9488_send_command(ILI9488_CMD_INTERFACE_MODE_CONTROL);
//	ili9488_send_byte(0x00);
//	ili9488_wait_for_send_done();
//	ili9488_deselect_chip();

//	//Frame rate 70HZ
////                 #define ILI9488_CMD_FRAME_RATE_CONTROL_NORMAL       0xB1
//	ili9488_send_command(ILI9488_CMD_FRAME_RATE_CONTROL_NORMAL);
//	ili9488_send_byte(0xB0);
//	ili9488_send_byte(0x11);
//	ili9488_wait_for_send_done();
//	ili9488_deselect_chip();

//	// Display Inversion
////                 #define ILI9488_CMD_DISPLAY_INVERSION_CONTROL       0xB4
//	ili9488_send_command(ILI9488_CMD_DISPLAY_INVERSION_CONTROL);
//	ili9488_send_byte(0x02);
//	ili9488_wait_for_send_done();
//	ili9488_deselect_chip();

//	// Entry Set Mode
////                 #define ILI9488_CMD_ENTRY_MODE_SET                  0xB7
//	ili9488_send_command(ILI9488_CMD_ENTRY_MODE_SET);
//	ili9488_send_byte(0xC6);
//	ili9488_wait_for_send_done();
//	ili9488_deselect_chip();

//#ifndef CONF_ILI9488_SPI

//	// Interface Pixel Format
////                 #define ILI9488_CMD_INTERFACE_PIXEL_FORMAT          0x3A
//	ili9488_send_command(ILI9488_CMD_INTERFACE_PIXEL_FORMAT);
//	ili9488_send_byte(0x55);// DPI: 16bpp  DBI: 16bpp
//	ili9488_wait_for_send_done();
//	ili9488_deselect_chip();
	
//	// Set Image Function
//	// enable 24 bit data bus
////                 #define ILI9488_CMD_SET_IMAGE_FUNCTION              0xE9
//	ili9488_send_command(ILI9488_CMD_SET_IMAGE_FUNCTION);
//	ili9488_send_byte(0x01);
//	ili9488_wait_for_send_done();
//	ili9488_deselect_chip();

//#else

//	// Interface Pixel Format
////                 #define ILI9488_CMD_INTERFACE_PIXEL_FORMAT          0x3A
//	ili9488_send_command(ILI9488_CMD_INTERFACE_PIXEL_FORMAT);
//	ili9488_send_byte(0x51);// DPI: 16bpp  DBI: 16bpp
//	ili9488_wait_for_send_done();
//	ili9488_deselect_chip();
	
//	// Set Image Function
////                 #define ILI9488_CMD_SET_IMAGE_FUNCTION              0xE9
//	ili9488_send_command(ILI9488_CMD_SET_IMAGE_FUNCTION);
//	ili9488_send_byte(0x00);
//	ili9488_wait_for_send_done();
//	ili9488_deselect_chip();

//#endif

//	// Adjustment Control 3
//	// fixed settings and DSI packet setup
////                 #define ILI9488_CMD_ADJUST_CONTROL_3                0xF7
//	ili9488_send_command(ILI9488_CMD_ADJUST_CONTROL_3);
//	ili9488_send_byte(0xA9);
//	ili9488_send_byte(0x51);
//	ili9488_send_byte(0x2C);
//	ili9488_send_byte(0x82);
//	ili9488_wait_for_send_done();
//	ili9488_deselect_chip();

//	// Set Interface Mode
////                 #define ILI9488_CMD_DISPLAY_FUNCTION_CONTROL        0xB6
//	ili9488_send_command(ILI9488_CMD_DISPLAY_FUNCTION_CONTROL);
//	ili9488_send_byte(0x00);// RGB or other interface
//	ili9488_send_byte(0x22);
//	ili9488_send_byte(0x3B);
//	ili9488_wait_for_send_done();
//	ili9488_deselect_chip();

//	ili9488_set_orientation(0);
////  
////  
//	ili9488_set_limits(0, 0, ILI9488_DEFAULT_WIDTH,	ILI9488_DEFAULT_HEIGHT);

   #endif  // - end ILI9488_E2 . //

  #endif  // - end ILI9488_E1 . //

 #endif  // - end ILI9341_E . //

#endif  // - end ST7789_E . //

}


/// ADDRESS SET : ///
void LCD_Address_Set(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye)
{
    /// #define ILI9341_CMD_COLUMN_ADDRESS_SET  0x2A : ///
    LCD_WriteReg(0x2A);
    LCD_WriteData16(xs);
    LCD_WriteData16(xe);

    // #define ILI9341_CMD_PAGE_ADDRESS_SET  0x2B : ///
    LCD_WriteReg(0x2B);
    LCD_WriteData16(ys);
    LCD_WriteData16(ye);

    /// #define ILI9341_CMD_MEMORY_WRITE  0x2C : ///
    LCD_WriteReg(0x2C);
}

/// FILL SCREEN : ///
void LCD_Fill(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint16_t color)
{
    uint16_t i, j;
    
    LCD_Address_Set(xs, ys, xe - 1, ye - 1);
    for (i = ys; i < ye; i++)
    {
        for (j = xs; j < xe; j++)
        {
            LCD_WriteData16(color);
        }
    }
}

/// DRAW POINT : ///
void LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t color)
{
    LCD_Address_Set(x, y, x, y);
    LCD_WriteData16(color);
}

/// DRAW LINE : ///
void LCD_DrawLine(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint16_t color)
{
    uint16_t i;
    int x = 0, y = 0, dx, dy, offset;
    int stepx, stepy, nowx, nowy;
    
    dx = xe - xs;
    dy = ye - ys;
    
    nowx = xs;
    nowy = ys;
    
    stepx = (dx > 0) ? 1 : ((dx == 0) ? 0 : -1);
    stepy = (dy > 0) ? 1 : ((dy == 0) ? 0 : -1);
    dx = (stepx >= 0) ? dx : -dx;
    dy = (stepy >= 0) ? dy : -dy;
    offset = (dx > dy) ? dx : dy;
    
    for (i = 0; i < (offset + 1); i++)
    {
        LCD_DrawPoint(nowx, nowy, color);
        x += dx;
        y += dy;
        if (x > offset)
        {
            x -= offset;
            nowx += stepx;
        }
        if (y > offset)
        {
            y -= offset;
            nowy += stepy;
        }
    }
}

/// DRAW RECT : ///
void LCD_DrawRectangle(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint16_t color)
{
    LCD_DrawLine(xs, ys, xe, ys, color);
    LCD_DrawLine(xe, ys, xe, ye, color);
    LCD_DrawLine(xe, ye, xs, ye, color);
    LCD_DrawLine(xs, ye, xs, ys, color);
}

/// DRAW CIRCLE : ///
void LCD_DrawCircle(uint16_t x, uint16_t y, uint8_t r, uint16_t color)
{
    int a, b;
    
    a = 0;
    b = r;
    while (a <= b)
    {
        LCD_DrawPoint(x - b, y - a, color);
        LCD_DrawPoint(x - b, y + a, color);
        LCD_DrawPoint(x + b, y - a, color);
        LCD_DrawPoint(x + b, y + a, color);
        LCD_DrawPoint(x + a, y - b, color);
        LCD_DrawPoint(x - a, y - b, color);
        LCD_DrawPoint(x + a, y + b, color);
        LCD_DrawPoint(x - a, y + b, color);
        a++;
        if ((a * a + b * b) > (r * r))
        {
            b--;
        }
    }
}

/// SHOW PICTURE : ///
void LCD_ShowPicture(uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint8_t *data)
{
    LCD_Address_Set(x, y, x + length - 1, y + width - 1);
    LCD_WriteData(data, length * width * 2);
}

//

#ifdef  ILI9488_E1

/*
Writing data to screen
After the initialization procedure, finally we can write data to screen. To write in the screen the command number is 0×2C, any data sent after this command will be write in the display, at the predetermined cursor position. The basic procedure to write the pixel in a given position with a given color is shown bellow.
*/
// write pixel at position
void write_pixel(unsigned short x, unsigned short y, unsigned char r, unsigned char g, unsigned char b)
{
//    set_address(x, y);

    // set cursor
    LCD_WriteReg(0x2A);
    // set start x
    LCD_WriteData16( x );
    // set end x
    LCD_WriteData16( x );
    LCD_WriteReg(0x00);

    LCD_WriteReg(0x2B);
    // set start y
    LCD_WriteData16( y );
    // set end y
    LCD_WriteData16( y );
    LCD_WriteReg(0x00);

//    P2OUT &= (~LCD_CS);

//    send_command(0x2C);
//    send_data(r);
//    send_data(g);
//    send_data(b); 
    LCD_WriteReg(0x2C);
    LCD_WriteData8( r );
    LCD_WriteData8( g );
    LCD_WriteData8( b );
//     HAL_Delay(100);

}

#endif

///
