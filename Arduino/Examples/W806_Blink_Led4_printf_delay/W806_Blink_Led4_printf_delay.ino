/*
  W806
  Serial: 115200

  Led 4 

*/

#include <stdio.h>
#include <Arduino.h>



void setup() 
{
//  Serial.begin(115200);
  printf("Led Demo\r\n");

  pinMode(      4 , OUTPUT   );   // -> PA4 
  digitalWrite( 4 , LOW      );   // -> PA4 

  delay(300);  // - 0.3sec 

}


void loop() 
{
  digitalWrite( 4 , HIGH );   // -> PA4 
  delay(500);  // - 0.5sec 

  digitalWrite( 4 , LOW );
  delay(500);  // - 0.5sec 

}

///

