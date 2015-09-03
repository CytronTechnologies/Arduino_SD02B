/*=========================================================
- This example code is written for controlling 
  SD02B Stepper Motor Driver by Cytron Technologies
  through the UART interface.
- Stepper motor will rotate clockwise & counter-clockwise
  continuously at two different microstepping modes.
- Please visit www.cytron.com.my for more information.
=========================================================*/

void setup()
{
  Serial.begin(9600);
  
// Uncomment the code below if you've forgot what's the current 
// baudrate set to SD02B.
/*  Serial.print('U');  // set motor controller baudrate to
  Serial.write(1);    // 9600bps
  Serial.begin(19200);
  Serial.print('U');  // set motor controller baudrate to
  Serial.write(1);    // 9600bps
  Serial.begin(38400);
  Serial.print('U');  // set motor controller baudrate to
  Serial.write(1);    // 9600bps
  Serial.begin(57600);
  Serial.print('U');  // set motor controller baudrate to
  Serial.write(1);    // 9600bps
  Serial.begin(9600); // use to communicate 9600 after this  */
}

void loop()
{
  Serial.print('O');  // turn on stepper motor
  Serial.print('S');  // set speed
  Serial.write(10);   // to 10

  Serial.print('<');  // rotate counterclockwise
  Serial.print('M');  // set micro-stepping to
  Serial.write(1);    // 1
  Serial.print('G');  // run the stepper motor
  delay(3000);
  
  Serial.print('>');  // rotate counterclockwise
  Serial.print('M');  // set micro-stepping to
  Serial.write(10);   // 10
  Serial.print('G');  // run the stepper motor
  delay(3000);
}

