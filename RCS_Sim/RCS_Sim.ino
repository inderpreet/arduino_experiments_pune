/*
  ASCII table

  Prints out byte values in all possible formats:
  - as raw binary values
  - as ASCII-encoded decimal, hex, octal, and binary values

  For more on ASCII, see http://www.asciitable.com and http://en.wikipedia.org/wiki/ASCII

  The circuit: No external hardware needed.

  created 2006
  by Nicholas Zambetti <http://www.zambetti.com>
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/ASCIITable
*/


/**
 * Global Variables
 */

unsigned char dataFrame[10];
unsigned long time1, time2;
unsigned char flag;

/**
 * Setup Function
 */
void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  for(int i=0; i<10; i++){
    dataFrame[i]=0x00;
  }
}

/** 
 *  Main Loop
 */
void loop() {
  
  flag = 0x0ff;
  time1 = 0x0300;
  
  dataFrame[0]=0x000; // all blocked and nothing received
  while( flag != 0x00 ){
    time1--;
    if(digitalRead(2)==LOW){
      dataFrame[0] |=0x01;
    }
    if(digitalRead(3)==LOW){
      dataFrame[0] |= 0x02;
    }
    if(digitalRead(4)==LOW){
      dataFrame[0] |.= 0x04;
    }

    if(time1 == 0x00){
      flag = 0x00;
    }
  }
  /**
   * Serial Frame Send
   */
  Serial.write('{'); // SOF
  Serial.write(dataFrame[0]); //B1
  Serial.write(dataFrame[1]); //2
  Serial.write(dataFrame[2]); //B3
  Serial.write(dataFrame[3]); //4
  Serial.write(dataFrame[4]); //B5
  Serial.write(dataFrame[5]); //6
  Serial.write(dataFrame[6]); //B7
  Serial.write(dataFrame[7]); //8
  Serial.write(dataFrame[8]); //B9
  Serial.write(dataFrame[9]); //10
  Serial.write(0xfe); // MLS
  Serial.write(0xff); // BUf1
  Serial.write(0xff); //BUF 2
  Serial.write(':');
  Serial.write('}'); //EOF
}
