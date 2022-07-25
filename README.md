# w806
Wm W806

This is a collection of projects for the W806 microcontroller.

- still adding Projects - Work In Progress

drop these src* directories into app , and rename as src folder.

---

/src.74hc165_PISO/ : Shifts In (8) pins from the 74hc165 Parallel In Serial Out chip.

/src.SpiRam6404/ : uses the IPS6404 SPI RAM chip on the SPI bus.

/src.adc_4ch/ : loops through the (4) ADC ports and prints them out.

/src.gpio_Ports/ : Prints out the PortA and PortB as 32bit ints. 

---

  : W806 pinout :

Gnd	|    | Gnd

 PB5 |   | PB4
 
 PB6 |   | PB27

PB7	|    | PB3

 PB8 |   | PB2
 
 PB9 |    | PB1
 
PB12 |    | PB0

PB13 |   | PA15

PB14 |   | PA14

PB15 |   | PA13

PB10 |   | PA12

PB11 |   | PA11

PB16 |   | PA10

PB17 |   | PA9

PB18 |   | PA8

PB26 |   | PA7  

PB25 |   | PA6

PB24 |   | PA5

PB22 |   | PA4

PB21 |   | PA3

PB20 |   | PA2

PB19 |   | PA1

 WkUp |   | PA0

 RstN |    | +3.3V

--

PA1-PA8 :	  20MHz

PA9-PA15 : 50MHz

PB0-PB5 :	80MHz

PB6-PB16 : 50MHz

PB17 :	  20MHz 

PB18-PB22 :   10MHz

PB23-PB26 :  20MHz

PB27 :	80MHz

---
Also see :
https://www.instructables.com/W806-Microcontroller-Code-Projects/

---
