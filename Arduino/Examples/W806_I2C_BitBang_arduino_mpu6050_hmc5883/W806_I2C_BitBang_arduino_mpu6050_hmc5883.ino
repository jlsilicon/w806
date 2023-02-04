/*

 : W806_I2C_BitBang_arduino_mpu6050_hmc5883.ino :

 - compiles on Arduino IDS for W806 chips.

 - This is the master controller for the Mpu6050 & Hmc5883 chips. 

 - This uses the I2S protocol
    using raw bit bang low-level code. 

*/

//

#include <Arduino.h>

#include <stdio.h>
#include <stdlib.h>

//

 // #define USE_ARDUINO_E  1 
#ifdef  USE_ARDUINO_E7 
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
    value |= (currentBit << 7-i);

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

void setup() 
{
#ifdef  USE_ARDUINO_E 
 Serial.begin(9600);
#endif

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
  for(int i=0x01; i<=0xFF; i+=2)
  {
    CHIP_ADDR = ( i ) ;
   printf( "* dvc%02X: r%02X = %02X  ,"   , i , 0    , readRegister(0)    );
   printf( "  dvc%02X: r%02X = %02X \r\n" , i , 0x75 , readRegister(0x75) );
   
    if( readRegister(0) != 0xFF )
    {
      for(int i=0x01; i<=0xFF; i+=2)
      {
        CHIP_ADDR = ( HMC5883_ADDR ) ;
       printf( " %02X ," , readRegister(i)    );
      }
      printf("\r\n");
    }
  }
#endif

  //

 printf( "\r\n" );
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

  AcX = ( (AcX >= 0x8000) ? (AcX = AcX - 0x10000) : (AcX = AcX) );
  AcY = ( (AcY >= 0x8000) ? (AcY = AcY - 0x10000) : (AcY = AcY) );
  AcZ = ( (AcZ >= 0x8000) ? (AcZ = AcZ - 0x10000) : (AcZ = AcZ) );
  Tmp = Tmp ;
  GcX = ( (GcX >= 0x8000) ? (GcX = GcX - 0x10000) : (GcX = GcX) );
  GcY = ( (GcY >= 0x8000) ? (GcY = GcY - 0x10000) : (GcY = GcY) );
  GcZ = ( (GcZ >= 0x8000) ? (GcZ = GcZ - 0x10000) : (GcZ = GcZ) );

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

  cX = ( (cX >= 0x8000) ? (cX = cX - 0x10000) : (cX = cX) );
  cY = ( (cY >= 0x8000) ? (cY = cY - 0x10000) : (cY = cY) );
  cZ = ( (cZ >= 0x8000) ? (cZ = cZ - 0x10000) : (cZ = cZ) );

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

 printf( "\r\n" );

  HAL_Delay(500);
}

///
