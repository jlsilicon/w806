To install W06 Libraries on Arduino IDE :

Arduino IDE : 2.0.3 / 1.8.2
Processor : W806

Arduino : 

menu:  File:Preferences:
Add below to 'Additional Board Manager URLs' box :
https://raw.githubusercontent.com/Hi-LinkDuino/w80x_arduino/main/package_w80x_index.json 1
https://github.com/jlsilicon/w806/blob/main/package_w80x_proxy_index.json 2

menu: Sketch : Include Library : Manage Libraries :
 - search for W806 then click Install btn

Board : search for: w80x_duino 
 - Cpu = w806 
 - Cpu frequnency = 240MHz

Further Instructions here :
  https://www.instructables.com/W806-Microcontroller-Code-Projects/
