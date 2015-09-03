/*=========================================================
- This example code is written for controlling 
  SD02B Stepper Motor Driver by Cytron Technologies
  through the UART interface.

- Turn on SD02B and run stepper motor continuously at 
  1/10 micro-stepping.

- Keep requesting current encoder value from SD02B and display 
  on LCD keypad Shield:
  http://www.cytron.com.my/viewProduct.php?pcode=SHIELD-LCD&name=LCD%20keypad%20Shield

- For more information about SD02B Stepper Motor Driver, 
  please visit www.cytron.com.my
=========================================================*/
#include <LCD4Bit_mod.h> 
//create object to control an LCD.  
//number of lines in display=2
LCD4Bit_mod lcd = LCD4Bit_mod(2); 


void setup()
{
  pinMode(13, OUTPUT);    // set on board LED
  digitalWrite(13, LOW);
  
  Serial.begin(9600);
  
  lcd.init();
  lcd.clear();
  lcd.printIn("  CYTRON TECH.  ");
  lcd.cursorTo(2, 1);
  lcd.printIn("Encoder=");
}

void loop()
{
  unsigned char enc_H=0, enc_L=0;
  unsigned int  encoder=0;
  char enc_str[6];
  
  Serial.print('R');    // reset encoder

  Serial.print('O');    // turn on stepper motor

  Serial.print('S');    // set speed
  Serial.write(10);     // to 10

  Serial.print('>');    // rotate counterclockwise

  Serial.print('M');    // set micro-stepping to
  Serial.write(10);     // 10 = 1/10 microstepping

  Serial.print('G');    // run the stepper motor

  while(1)
  {
    Serial.print('E');  // request current encoder value
    
    if (Serial.available()>0) // if uart receive buffer is not empty
    {
      enc_H = Serial.read();  // read a byte
      enc_L = Serial.read();  // read a byte
      
////=========================================
////   For checking incoming data bytes
////-----------------------------------------
//      // convert decimal to characters
//      enc_str[0] = enc_H / 100 + '0';
//      enc_H %= 100;
//      enc_str[1] = enc_H / 10 + '0';
//      enc_str[2] = enc_H % 10 + '0';
//      enc_str[3] = '\0';
//      
//      lcd.cursorTo(1, 0);  // line=1, x=0
//      lcd.printIn("H=");   // print string
//      lcd.cursorTo(1, 2);  // line=1, x=2
//      lcd.printIn(enc_str);// print string
//      
//      // convert decimal to characters
//      enc_str[0] = enc_L / 100 + '0';
//      enc_L %= 100;
//      enc_str[1] = enc_L / 10 + '0';
//      enc_str[2] = enc_L % 10 + '0';
//      enc_str[3] = '\0';
//      
//      lcd.cursorTo(1, 5);      // line=1, x=6
//      lcd.printIn(" L=      ");// print string
//      lcd.cursorTo(1, 8);      // line=1, x=8
//      lcd.printIn(enc_str);    // print string
////=========================================
      
      // combine two bytes 
      encoder = (enc_H << 8) & 0xFF00;
      encoder = encoder ^ (enc_L & 0x00FF);
      
      // convert decimal to characters
      enc_str[0] = encoder / 10000 + '0';
      encoder %= 10000;
      enc_str[1] = encoder / 1000 + '0';
      encoder %= 1000;
      enc_str[2] = encoder / 100 + '0';
      encoder %= 100;
      enc_str[3] = encoder / 10 + '0';
      enc_str[4] = encoder % 10 + '0';
      enc_str[5] = '\0';
      
      lcd.cursorTo(2, 10);   // line=2, x=10
      lcd.printIn(enc_str);  // print string
  
      digitalWrite(13, !digitalRead(13));  // toggle LED
    }// if (Serial.available()>0)
    
    delay(500);  //delay 500ms
  }// while(1)
  
}//void loop()
