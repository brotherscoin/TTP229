/*********************************** LICENCE **********************************\
| Copyright (c) 2014, A.E. TEC                                                 |
| All rights reserved.                                                         |
|                                                                              |
| Redistribution and use in source and binary forms, with or without           |
| modification, are permitted provided that the following conditions are met:  |
|                                                                              |
| * Redistributions of source code must retain the above copyright notice,     |
|   this list of conditions and the following disclaimer.                      |
| * Redistributions in binary form must reproduce the above copyright notice,  |
|   this list of conditions and the following disclaimer in the documentation  |
|   and/or other materials provided with the distribution.                     |
|                                                                              |
| THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"  |
| AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE    |
| IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE   |
| ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE    |
| LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR          |
| CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF         |
| SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS     |
| INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN      |
| CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)      |
| ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE   |
| POSSIBILITY OF SUCH DAMAGE.                                                  |
\******************************************************************************/
/************************************ USES ************************************\
| This sketch demonstrates the use of TTP229 Module, in 16 Buttons Mode.       |
| It displays the pressed number on the Terminal                               |
|                                                                              |
| It works with a TTP229 (16-Channel Digital Touch Capacitive Switch Sensor)   |
| using the 2-wires serial interface protocol - only 2 arduino pins.           |
\******************************************************************************/
/*********************************** CIRCUIT **********************************\
| 16 Buttons Mode:                                                             |
|	* TTP229 VCC to pin VCC                                                    |
|	* TTP229 GND to pin GND                                                    |
|	* TTP229 SCL to pin 2                                                      |
|	* TTP229 SDO to pin 3                                                      |
|	* TTP229 TP2 to GND via 1 Megohm resistor!                                 |
|	# See TTP229_Modes.jpg for help...                                         |
|                                                                              |
| Important:                                                                   |
|	* Must reconnect the TTP229 power so the mode changes will take effect     |
|	* The 1 Megohm resistors already exist on some TTP229 modules              |
\******************************************************************************/

// A extension for the ttp229 keypad, to be able to use it as a alphanumeric and some symbols keyboard
// Newline is implemented with \n , write your own code for tab and del ;)
// Note: see the jpg for placement of the characters on the keypad 
#include <LiquidCrystal_PCF8574.h>
#include <Wire.h>

LiquidCrystal_PCF8574 lcd(0x27); // set the LCD address to 0x27 for a 16 chars and 2 line display

int show = -1;
#include <TTP229.h>

const int SCL_PIN =2;  // The pin number of the clock pin.
const int SDO_PIN =3;  // The pin number of the data pin.
int toet;
int ltoet;
int ptoet;
String pres;
String calc;
String uit[60]={"","","","",
                "1","A","N","!","2","B","O",":","3","C","P","#","del","D","Q","-",
                "4","E","R","$","5","F","S","%","6","G","T","^","tab","H","U","+",
                "7","I","V","&","8","J","W","*","9","K","X","(","\n" ,"L","Y"," ",
                "0","M","Z",")",""};

//char enter=(12);
TTP229 ttp229(SCL_PIN,SDO_PIN); // TTP229(sclPin, sdoPin)

void setup()
{
	Serial.begin(9600);
	Serial.println("Ok");

 show = 0;
    lcd.begin(16, 2); // initialize the lcd
 lcd.setBacklight(255);
     lcd.cursor();
    //lcd.home();
    lcd.clear();
}

void loop()
{
toets();	
}
void toets()
{
  uint8_t key = ttp229.ReadKey16(); // test ttp229
if (key) toet=key;
if (ltoet==key) 
{
}
else 
{
  board();
ltoet=toet;
}
if (pres=="") 
{
}
else
{
  if(pres=="\n")
  {
    Serial.println("");//newline when enter is pressed
 
  Serial.println(calc.toInt());//if there's a number, calc has it
 lcd.print(pres);
  calc="";// cleaning all variables for next operation
 
}
  else
  {
  
  Serial.print(pres);//printing normal input to the Com
lcd.print(pres);
calc=calc+pres;// building the output string

  }
  pres="";// clean up the mess
ptoet=0;
ltoet=0;
}

}
void board()
{
//Serial.print(ptoet);
  //Serial.println(ltoet);
pres="";
switch (ltoet)
 {
 case 0:
 break;
 case 14:// setting ptoet for abc1;abc2 or symbol output
 ptoet=1;
 break;
 case 15:
 ptoet=2;
 break;
case 16:
 ptoet=3;
 break;
 default:
int sk=(ltoet*4)+ptoet;
pres=uit[sk];
break;
}
}
