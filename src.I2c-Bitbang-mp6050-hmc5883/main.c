/*

 : W806_I2C_BitBang_arduino_mpu6050_hmc5883.ino :

 - compiles on Arduino IDS for W806 chips.

 - This is the master controller for the Mpu6050 & Hmc5883 chips. 

 - This uses the I2S protocol
    using raw bit bang low-level code. 

*/

//

 #include "wm_hal.h"

/*
 #include <Arduino.h>
*/

#include <stdio.h>
#include <stdlib.h>

//

void  delayMicroseconds(int T)
{
  for(int i=0; i<(T*240/5); i++)
  {}
}

#define  byte  char  

#define  INPUT   0  
#define  OUTPUT  1  
#define  LOW     0  
#define  HIGH    1  

#define  bitRead(value,i)  ( value & (1 << i) ) 

void  pinMode( uint8_t Pin_ , uint8_t Dir )
{
GPIO_InitTypeDef GPIO_InitStruct = {0};

//  if( Dir )
//    Dir = 1;

  if( Pin_ < 16 )
  {
    if( ! Dir )
    {
      GPIOA->DIR &= ~( 1   << Pin_ ) ;
// GPIO_InitTypeDef GPIO_InitStruct = {0};
// __HAL_RCC_GPIO_CLK_ENABLE();
GPIO_InitStruct.Pin  = ( 1 << Pin_ ) ;
GPIO_InitStruct.Mode =               GPIO_MODE_INPUT;
GPIO_InitStruct.Pull = GPIO_NOPULL;
HAL_GPIO_Init( GPIOA , &GPIO_InitStruct );
    }
    else
    {
      GPIOA->DIR |=  ( 1   << Pin_ ) ;
// GPIO_InitTypeDef GPIO_InitStruct = {0};
// __HAL_RCC_GPIO_CLK_ENABLE();
GPIO_InitStruct.Pin  = ( 1 << Pin_ ) ;
GPIO_InitStruct.Mode =               GPIO_MODE_OUTPUT;
GPIO_InitStruct.Pull = GPIO_NOPULL;
HAL_GPIO_Init( GPIOA , &GPIO_InitStruct );
    }
  }
  else
  if( Pin_ < 48 )
  {
    Pin_ = (Pin_ - 16);
    if( ! Dir )
    {
//      GPIOB->DIR &= ~( 1   << Pin_ ) ;
// GPIO_InitTypeDef GPIO_InitStruct = {0};
// __HAL_RCC_GPIO_CLK_ENABLE();
GPIO_InitStruct.Pin  = ( 1 << Pin_ ) ;
GPIO_InitStruct.Mode =               GPIO_MODE_INPUT;
GPIO_InitStruct.Pull = GPIO_NOPULL;
HAL_GPIO_Init( GPIOB , &GPIO_InitStruct );
    }
    else
    {
//      GPIOB->DIR |=  ( 1   << Pin_ ) ;
// GPIO_InitTypeDef GPIO_InitStruct = {0};
// __HAL_RCC_GPIO_CLK_ENABLE();
GPIO_InitStruct.Pin  = ( 1 << Pin_ ) ;
GPIO_InitStruct.Mode =               GPIO_MODE_OUTPUT;
GPIO_InitStruct.Pull = GPIO_NOPULL;
HAL_GPIO_Init( GPIOB , &GPIO_InitStruct );
    }
  }

}

void  digitalWrite( uint8_t Pin_ , uint8_t Val_ )
{

//  if( Val )
//    Val = 1;

  if( Pin_ < 16 )
  {
    if( ! Val_ )
      GPIOA->DATA &= ~( 1   << Pin_ ) ;
    else
      GPIOA->DATA |=  ( 1   << Pin_ ) ;
HAL_GPIO_WritePin( GPIOA , (1 << Pin_) , Val_ );
  }
  else
  if( Pin_ < 48 )
  {
    Pin_ = (Pin_ - 16);
    if( ! Val_ )
      GPIOB->DATA &= ~( 1   << Pin_ ) ;
    else
      GPIOB->DATA |=  ( 1   << Pin_ ) ;
HAL_GPIO_WritePin( GPIOB , (1 << Pin_) , Val_ );
  }

}

uint8_t  digitalRead( uint8_t Pin_ )
{
uint8_t  Val_ = 0 ;

  if( Pin_ < 16 )
  {
    Val_ = ( GPIOA->DATA & ( 1   << Pin_ ) );
Val_ = HAL_GPIO_ReadPin( GPIOA , (1 << Pin_) );
  }
  else
  if( Pin_ < 48 )
  {
    Pin_ = (Pin_ - 16);
    Val_ = ( GPIOB->DATA & ( 1   << Pin_ ) );
Val_ = HAL_GPIO_ReadPin( GPIOB , (1 << Pin_) );
  }

  if( Val_ )
    Val_ = 1;

return( Val_ );
}

//

 // #define USE_ARDUINO_E  1 
#ifdef  USE_ARDUINO_E 
 #define  SDA  A4
  #define  SCL  A5
#else
  #define  SDA  4
  #define  SCL  1
#endif

//

/// Enable I2C DEVICES : ///
 //// #define  DS1307_E   1
 #define  MPU6050_E   1
 #define  HMC5883_E   1


/// I2C DEVICE ADDRESSES : ///

//#define  DS1307_ADDR_R  = 0xD1 ;  // the DS1307 7-bit address 1101000 with READ  bit (1) = 11010001 = D1
//#define  DS1307_ADDR_W  = 0xD0 ;  // DS1307   : xD0 = b 1101 0000 == (MPU6050  : x68 = b 0110 1000 <<1) 
#define    DS1307_ADDR      0xD0    // DS1307   : xD0 = b 1101 0000 

//#define  MPU6050_ADDR_R = 0x69 ;  // MPU6050 
//#define  MPU6050_ADDR_W = 0x68 ;  // MPU6050  : x68 = b 0110 1000
// #define  MPU6050_ADDR_W = (0x68 <<1) ;  // MPU6050  : 0xD0 = b 1101 0000  // - ??? 
#define    MPU6050_ADDR     (0x68)    // MPU6050 
#define    MPU6050_ADDR_2   (0x69)    // MPU6050 

//#define  HMC5883_ADDR_R = 0x1F ;  // HMC5883L 
//#define  HMC5883_ADDR_W = 0x1E ;  // HMC5883L : x1E = b 0001 1110
// #define  HMC5883_ADDR_W = (0x1E <<1) ;  // HMC5883L  : x3C = b 0011 1100  // - ??? 
#define    HMC5883_ADDR     (0x1E)    // HMC5883L  


/// Set Current Device ADDRESS Function : ///
#define  DeviceSet(D)  (CHIP_ADDR=(D << 1)) 

//

 uint8_t  CHIP_ADDR = 0              ;
 // uint8_t  CHIP_ADDR = DS1307_ADDR_W  ;
// uint8_t  CHIP_ADDR = MPU6050_ADDR_W ;
// uint8_t  CHIP_ADDR = HMC5883_ADDR_W ;

//

int32_t  AcX, AcY, AcZ,  Tmp,  GcX, GcY, GcZ ;

int cX,cY,cZ; //triple axis data
// int xmin,xmax,ymin,ymax,zmin,zmax;

int  Id ;

//


#define  MSBFIRST  81 
#define  LSBFIRST  18 
//// shiftOut(SDA, SCL, MSBFIRST, value); : ////
void shiftOut(int datpin, int clkpin, int dir, int val) 
{
  // pinMode(datpin, OUTPUT);

  if( dir == MSBFIRST )
  {
    // MSBFIRST : send out the 8 bits 
    for (int i=7; i>=0; i--) 
    {
      digitalWrite(clkpin, LOW);
       digitalWrite(datpin, bitRead(val,i));
/*
       if(bitRead(val,i))
         pinMode(datpin,INPUT_PULLUP)
       else
       {
         pinMode(datpin,OUTPUT);
         digitalWrite(datpin, HIGH);
       }
*/
      digitalWrite(clkpin, HIGH);
    }
  }
  else  
  {
    // LSBFIRST : send out the 8 bits 
    for (int i=0; i<=7; i++) 
    {
      digitalWrite(clkpin, LOW);
       digitalWrite(datpin, bitRead(val,i));
/*
       if(bitRead(val,i))
         pinMode(datpin,INPUT_PULLUP)
       else
       {
         pinMode(datpin,OUTPUT);
         digitalWrite(datpin, LOW);
       }
*/
      digitalWrite(clkpin, HIGH);
    }
  }
  
  digitalWrite(clkpin, LOW); // must have this last LOW
}


void sendStart(byte addr) 
{
  pinMode(SDA, OUTPUT);
  digitalWrite(SDA, HIGH);
  digitalWrite(SCL, HIGH);
  digitalWrite(SDA, LOW);  

  // send out the 8 bits
  for(int i=7; i>=0; i-- ) 
  {
    digitalWrite(SCL, LOW);
    digitalWrite(SDA, bitRead(addr,i) );
/*
       if(bitRead(val,i))
         pinMode(SDA,INPUT_PULLUP)
       else
       {
         pinMode(SDA,OUTPUT);
         digitalWrite(SDA, LOW);
       }
*/
    digitalWrite(SCL, HIGH);
  }
  
  digitalWrite(SCL, LOW); // must have this last LOW
}


void sendStart_BitStream(byte addr) 
{
  pinMode(SDA, OUTPUT);
  digitalWrite(SDA, HIGH);
  digitalWrite(SCL, HIGH);
  digitalWrite(SDA, LOW);  


  // send out the 8 bits :
  digitalWrite(SCL, LOW);
  digitalWrite(SDA, bitRead(addr,7));
  digitalWrite(SCL, HIGH);

  digitalWrite(SCL, LOW);
  digitalWrite(SDA, bitRead(addr,6));
  digitalWrite(SCL, HIGH);

  digitalWrite(SCL, LOW);
  digitalWrite(SDA, bitRead(addr,5));
  digitalWrite(SCL, HIGH);

  digitalWrite(SCL, LOW);
  digitalWrite(SDA, bitRead(addr,4));
  digitalWrite(SCL, HIGH);

  digitalWrite(SCL, LOW);
  digitalWrite(SDA, bitRead(addr,3));
  digitalWrite(SCL, HIGH);

  digitalWrite(SCL, LOW);
  digitalWrite(SDA, bitRead(addr,2));
  digitalWrite(SCL, HIGH);

  digitalWrite(SCL, LOW);
  digitalWrite(SDA, bitRead(addr,1));
  digitalWrite(SCL, HIGH);

  digitalWrite(SCL, LOW);
  digitalWrite(SDA, bitRead(addr,0));
  digitalWrite(SCL, HIGH);

  digitalWrite(SCL, LOW); // must have this last LOW
}


// this also works using the shiftOut command
void sendStart_works(byte addr) 
{
   pinMode(SDA, OUTPUT);
   
   digitalWrite(SDA, HIGH);
  digitalWrite(SCL, HIGH);
   digitalWrite(SDA, LOW);
  digitalWrite(SCL, LOW);

  shiftOut(SDA, SCL, MSBFIRST, addr);   // send out the 8 bits
}


void sendStop() 
{
   pinMode(SDA, OUTPUT);
   
   digitalWrite(SDA, LOW);
  digitalWrite(SCL, HIGH);
   digitalWrite(SDA, HIGH);
   
   pinMode(SDA, INPUT);
}


void sendNack() 
{
   pinMode(SDA, OUTPUT);
  digitalWrite(SCL, LOW);
   digitalWrite(SDA, HIGH);
  digitalWrite(SCL, HIGH);
  digitalWrite(SCL, LOW);
   pinMode(SDA, INPUT);
}


void sendAck() 
{
   pinMode(SDA, OUTPUT);
  digitalWrite(SCL, LOW);
   digitalWrite(SDA, LOW);
  digitalWrite(SCL, HIGH);
  digitalWrite(SCL, LOW);
   pinMode(SDA, INPUT);
}


byte waitForAck()   // - getAck() ??? 
{
   pinMode(SDA, INPUT);
  digitalWrite(SCL, HIGH);

byte ack = digitalRead(SDA);  //ACK bit should be LOW

  digitalWrite(SCL, LOW);
return ack;
}


byte readByte() 
{
  pinMode(SDA, INPUT);
byte value = 0;
byte currentBit = 0;

  for (int i = 0; i < 8; ++i) 
  {
    digitalWrite(SCL, HIGH);

    currentBit = digitalRead(SDA);
    value |= (currentBit << (7 - i));

    delayMicroseconds(1);

    digitalWrite(SCL, LOW);
  }
return value;
}


void writeByte(byte value) 
{
  pinMode(SDA, OUTPUT);

  // send out the 8 bits
  for (int i=7; i>=0; i--) 
  {
    digitalWrite(SCL, LOW);
     digitalWrite(SDA, bitRead(value,i));
    digitalWrite(SCL, HIGH);
  }
  
  digitalWrite(SCL, LOW); // must have this last LOW
}


// this also works using the shiftOut command
void writeByte_2(byte value) 
{
  pinMode(SDA, OUTPUT);
  shiftOut(SDA, SCL, MSBFIRST, value);
}


byte readRegister(byte reg) 
{
byte readValue=0;

  sendStart( CHIP_ADDR ); // set write mode
  waitForAck();

  writeByte(reg);           // send register address to read from
  waitForAck();

  sendStop();
  sendStart( CHIP_ADDR | 0x01 ); // change to read mode
  waitForAck();

  readValue = readByte();   // read data from register
  sendNack();
  sendStop();

return readValue;
}


void writeRegister(byte reg, byte value) 
{
  sendStart( CHIP_ADDR );
  waitForAck();

  writeByte(reg);   // send register address
  waitForAck();

  writeByte(value); // send data to store in register
  waitForAck();

  sendStop();
}

byte decToBcd(byte val) 
{
  return ((val/10*16) + (val%10));
}
byte bcdToDec(byte val) 
{
  return ((val/16*10) + (val%16));
}


//


static void GPIO_Init(void)
{
//    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    __HAL_RCC_GPIO_CLK_ENABLE();    // - needed for HAL_GPIO_ReadPin() 
}

;

void  loop()  ;

;

int  main()
// void setup() 
{
#ifdef  USE_ARDUINO_E 
 Serial.begin(9600);
#endif

    SystemClock_Config(CPU_CLK_160M);    // - needed for HAL_Delay() 
//    SystemClock_Config(CPU_CLK_240M);
    printf(":I2C BitBang: Main() : \r\n");

    HAL_Init();
    GPIO_Init();    // - needed for HAL_GPIO_ReadPin() 
    
  pinMode(SCL, OUTPUT);
  //pinMode(SDA, OUTPUT); // set in the low-level functions

  //

#ifdef  DS1307_E   
 Serial.println("DS1307");
//   CHIP_ADDR = DS1307_ADDR_W ;
  DeviceSet( DS1307_ADDR );

  writeRegister(0x00,0x00); // set the seconds register
                            // note: reset bit 7 of register 0 to 0 to enable the clock
  writeRegister(0x01,decToBcd(15)); // set the minutes register
  writeRegister(0x02,decToBcd(8)); // set the hours register
  writeRegister(0x07,0x10); // set control register to enable SQW to 1Hz output
 Serial.println(freadRegister(0x07));
#endif

  //

#ifdef  MPU6050_E   
 printf(": MP6050 :\r\n");
//   CHIP_ADDR = MPU6050_ADDR_W ;
 // CHIP_ADDR = DS1307_ADDR_W ;  // -??? 
  DeviceSet( MPU6050_ADDR );
  
  writeRegister(0x6B,0x00); // PWR_MGMT_1 register , set to zero (wakes up the MPU-6050) 
 printf( "%02X \n" , readRegister(0x75) );
#endif

  //

#ifdef  HMC5883_E   
 printf(": HMC5883 :\r\n");
//   CHIP_ADDR = HMC5883_ADDR_W ;
  DeviceSet( HMC5883_ADDR );

  writeRegister(0x02,0x00); //select mode register - continuous measurement mode
#endif

  //

 // #define SNOOP_E  1 
#ifdef  SNOOP_E
 printf(": I2C Snoop : \r\n");
  for(int i=0x00; i<=0xFF; i+=1)
  {
    CHIP_ADDR = ( i ) ;
   printf( "* dvc%02X: r%02X = %02X  ,"   , i , 0    , readRegister(0)    );
   printf( "  dvc%02X: r%02X = %02X \r\n" , i , 0x75 , readRegister(0x75) );
   
    if( readRegister(0) != 0xFF )
    {
      for(int j=0x00; j<=0xFF; j+=1)
      {
        CHIP_ADDR = ( i ) ;
       printf( " %02X ," , readRegister(j)    );
      }
      printf("\r\n");
    }
  }
#endif

  //

 printf( "\r\n" );


  //
  while(1)
  {
    loop();
  }
  //

return(0);
}


void loop() 
{

  //

#ifdef  DS1307_E   
 printf("%d ",bcdToDec(readRegister(2)));
 printf(":");
 printf("%d ",bcdToDec(readRegister(1)));
 printf(":");
 printf("%d \n",bcdToDec(readRegister(0)));
#endif

  //

#ifdef  MPU6050_E   
//   CHIP_ADDR = MPU6050_ADDR_W ;
  DeviceSet( MPU6050_ADDR );
  
  writeRegister(0x6B,0x00); // PWR_MGMT_1 register , set to zero (wakes up the MPU-6050) 

  Id = readRegister(0x75);
 printf( " Id=%0X "   , Id );

 // #define PRT_REGS_1  1 
#ifdef  PRT_REGS_1 
 printf( "%02X" ,  readRegister(0x3B) );
 printf( "%02X " ,  readRegister(0x3C) );
 printf( "%02X" ,  readRegister(0x3D) );
 printf( "%02X " ,  readRegister(0x3E) );
 printf( "%02X" ,  readRegister(0x3F) );
 printf( "%02X " ,  readRegister(0x40) );
 printf( "%02X" ,  readRegister(0x41) );
 printf( "%02X " ,  readRegister(0x42) );
 printf( "%02X" ,  readRegister(0x43) );
 printf( "%02X " ,  readRegister(0x44) );
 printf( "%02X" ,  readRegister(0x45) );
 printf( "%02X " ,  readRegister(0x46) );
 printf( "%02X" ,  readRegister(0x47) );
 printf( "%02X \r\n" ,  readRegister(0x48) );
#endif

  AcX = readRegister(0x3B)<<8 | readRegister(0x3C) ;  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY = readRegister(0x3D)<<8 | readRegister(0x3E) ;  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = readRegister(0x3F)<<8 | readRegister(0x40) ;  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = readRegister(0x41)<<8 | readRegister(0x42) ;  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GcX = readRegister(0x43)<<8 | readRegister(0x44) ;  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GcY = readRegister(0x45)<<8 | readRegister(0x46) ;  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GcZ = readRegister(0x47)<<8 | readRegister(0x48) ;  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

/*
  AcX = ( (AcX >= 0x8000) ? (AcX = AcX - 0x10000) : (AcX = AcX) );
  AcY = ( (AcY >= 0x8000) ? (AcY = AcY - 0x10000) : (AcY = AcY) );
  AcZ = ( (AcZ >= 0x8000) ? (AcZ = AcZ - 0x10000) : (AcZ = AcZ) );
  Tmp = Tmp ;
  GcX = ( (GcX >= 0x8000) ? (GcX = GcX - 0x10000) : (GcX = GcX) );
  GcY = ( (GcY >= 0x8000) ? (GcY = GcY - 0x10000) : (GcY = GcY) );
  GcZ = ( (GcZ >= 0x8000) ? (GcZ = GcZ - 0x10000) : (GcZ = GcZ) );
*/

  if( AcX >= 0x8000 )
    AcX = (AcX - 0x10000) ; 
  else
    AcX = AcX ;

  if( AcY >= 0x8000 )
    AcY = (AcY - 0x10000) ; 
  else
    AcY = AcY ;

  if( AcZ >= 0x8000 )
    AcZ = (AcZ - 0x10000) ; 
  else
    AcZ = AcZ ;

  Tmp = Tmp ;

  if( GcX >= 0x8000 )
    GcX = (GcX - 0x10000) ; 
  else
    GcX = GcX ;

  if( GcY >= 0x8000 )
    GcY = (GcY - 0x10000) ; 
  else
    GcY = GcY ;

  if( GcZ >= 0x8000 )
    GcZ = (GcZ - 0x10000) ; 
  else
    GcZ = GcZ ;


 // #define PRT_REGS_2  1 
#ifdef  PRT_REGS_2 
 printf( "aX=%04X  "   , AcX & 0xFFFF );
 printf( "aY=%04X  "   , AcY & 0xFFFF );
 printf( "aZ=%04X    " , AcZ & 0xFFFF );
 printf( "(T=%fC"       , (Tmp / 340.00) + 36.53 );
 printf( "=%fF)    "    , ((Tmp / 340.00 + 36.53) * (9.0/5.0) + 32.0) );
 printf( "gX=%04X  "   , GyX & 0xFFFF );
 printf( "gY=%04X  "   , GyY & 0xFFFF );
 printf( "gZ=%04X  "   , GyZ & 0xFFFF );
 printf( "\r\n" );
#endif

 printf( "aX=%d  "     , AcX );
 printf( "aY=%d  "     , AcY );
 printf( "aZ=%d    "   , AcZ );
 printf( "T=%fC"       , (Tmp / 340.00) + 36.53 );
 printf( "=%fF    "    , ((Tmp / 340.00 + 36.53) * (9.0/5.0) + 32.0) );
 printf( "gX=%d  "   ,   GcX );
 printf( "gY=%d  "   ,   GcY );
 printf( "gZ=%d  "   ,   GcZ );
 printf( "\r\n" );
#endif

  //

#ifdef  HMC5883_E   

//   CHIP_ADDR = HMC5883_ADDR_W ;
  DeviceSet( HMC5883_ADDR );

 // #define SNOOP_DVC_E  1 
#ifdef  SNOOP_DVC_E 
 printf(": I2C Snoop : \r\n");
  for(int i=0x01; i<=0xFF; i+=2)
  {
    CHIP_ADDR = ( HMC5883_ADDR ) ;
   printf( "* %02X  ," , readRegister(i)    );
  }
 printf("\r\n");
#endif

  
 // CHIP_ADDR = HMC5883_ADDR_W ;
  DeviceSet( HMC5883_ADDR );

  Id = readRegister(0x75);
 printf( " Id=%0X "   , Id );

  writeRegister(0x02,0x00); //select mode register - continuous measurement mode

 // #define PRT_REGS_3  1 
#ifdef  PRT_REGS_3 
 printf( "%02X" ,  readRegister(0x03) );
 printf( "%02X " ,  readRegister(0x04) );
 printf( "%02X" ,  readRegister(0x05) );
 printf( "%02X " ,  readRegister(0x06) );
 printf( "%02X" ,  readRegister(0x07) );
 printf( "%02X " ,  readRegister(0x08) );
#endif

  cX = readRegister(0x03)<<8 | readRegister(0x04) ; 
  cZ = readRegister(0x05)<<8 | readRegister(0x06) ; 
  cY = readRegister(0x07)<<8 | readRegister(0x08) ; 

/*
  cX = ( (cX >= 0x8000) ? (cX = cX - 0x10000) : (cX = cX) );
  cY = ( (cY >= 0x8000) ? (cY = cY - 0x10000) : (cY = cY) );
  cZ = ( (cZ >= 0x8000) ? (cZ = cZ - 0x10000) : (cZ = cZ) );
*/

  if( cX >= 0x8000 )
    cX = (cX - 0x10000) ; 
  else
    cX = cX ;

  if( cY >= 0x8000 )
    cY = (cY - 0x10000) ; 
  else
    cY = cY ;

  if( cZ >= 0x8000 )
    cZ = (cZ - 0x10000) ; 
  else
    cZ = cZ ;


 // #define PRT_REGS_4  1 
#ifdef  PRT_REGS_4 
 printf( "  cX=%04X  " , cX & 0xFFFF );
 printf( "cY=%04X  "   , cY & 0xFFFF );
 printf( "cZ=%04X  "   , cZ & 0xFFFF );
// printf( "\r\n" );
#endif

 printf( "  cX=%d  " , cX  );
 printf( "cY=%d  "   , cY  );
 printf( "cZ=%d  "   , cZ  );
 printf( "\r\n" );
#endif

  //


  /// PCA965 : ///

 // #define  PCA9685_E  1 
#ifdef  PCA9685_E 
/*
  x00  Mode1
  x01  Mode2
  x02  SubAdr1
  x03  SubAdr2
  x04  SubAdr3
  x05  AllCallAdr
  x06  Led0_ON_L    // 0 to 4095
  x07  Led0_ON_H    // ...
  x08  Led0_OFF_H   // 0 to 4095
  x09  Led0_OFF_H   // ...
  ...  
  x42  Led15_ON_L
  x43  Led15_ON_H
  x44  Led15_OFF_L
  x45  Led15_OFF_H
  ...  
  xFA  ALL_Led_ON_L
  xFB  ALL_Led_ON_H
  xFC  ALL_Led_OFF_L
  xFD  ALL_Led_OFF_H
  xFE  PreScale    // - prescale_value = round( clock_rate/(4096 * update_rate ) – 1
  xFF  TestMode
*/

    ////i2c_init(i2c_freq);                 //Initializing I2C communication at 100KHz

    i2c_start();                        //Start signal
    i2c_write(pca_addr=0x40);           //Specifying slave address in write mode
    i2c_write(0x00);                    //Control register set to address 00h
    i2c_write(0x21);                    //Mode 1 configured to with AI=1 and ALLCALL=1
    i2c_stop();                         //Stop signal

    /// PRE_SCALE register 
    ///  is hardware limited to have a minimum value of 3 (03h) and a maximum value of 255 (FFh). 
    ///  Thus using the 25MHz internal oscillator, 
    ///   the maximum value of update_rate is 1526 Hz (prescale_value=0x03h) 
    ///   and the minimum value of update_rate is 24 Hz (prescale_value=0xFFh).
    ///  By default, the PRE_SCALE register is loaded with the value 30 (0x1Eh) 
    ///   giving us an update_rate of 200 Hz with the 25MHz internal oscillator.

    /// Delay = 10% of 4096 = 409.6 ~ 410.
    ///  Count starts from 0 to 4095 (must be subtracted by 1), so ON count = 409 = 0x199h.
    ///  Thus, LED0_ON_H = 0x01h and LED_ON_L = 0x99h
    on_count  = 0x0199 ;
    /// Duty cycle = 30% of 4096 = 1228.8 ~ 1229
    ///  So OFF count = Delay + Duty cycle = 409 + 1229 = 1638 = 0x666h
    ///  Thus, LED0_OFF_H = 0x06h and LED_OFF_L = 0x66h
    off_count = 0x0666h ;
    i2c_start();                        //Start signal
    i2c_write(pca_addr=0x40);           //Specifying slave address in write mode
    i2c_write(((ledn=0x00)*4)+6);       //Control register set to address LEDn_ON_L
    i2c_write(on_count&0xFF);           //Writing 8 LSB bits of ON count
    i2c_write((on_count&0xF00)>>8);     //Writing 4 MSB bits of ON count
    i2c_write(off_count&0xFF);          //Writing 8 LSB bits of OFF count
    i2c_write((off_count&0xF00)>>8);    //Writing 4 MSB bits of ON count    
    i2c_stop();                         //Stop signal

  //

  #define  I2CAdd 0x40
  /// ... 
  #define  I2CAdd 0x7F
  HCPCA9685 HCPCA9685(I2CAdd);

  HCPCA9685.Init(SERVO_MODE);
  HCPCA9685.Sleep(false);  // Wakeup 
  
  Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40);

  pwm.setPWMFreq(1000)

  pulselength = map(degrees, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(15, 1024, 3072)


  pwm.setPWM(pin, 4096, 0);  // PON 

  pwm.setPWM(pin, 0, 4096);  // POFF 


  HCPCA9685.Servo(1, Pos);


#endif

  //

 printf( "\r\n" );

  HAL_Delay(500);
 // HAL_Delay(1);

}

///
