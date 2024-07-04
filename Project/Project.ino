#include <Arduino.h>
#include <Wire.h>   // Include library Wire
#include "RTClib.h" // Include libary RTClib
#include <SPI.h>    // Include library SPI
#include <SD.h>     // Include library SD

//declare sd card and rtc input value
RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//declare sensor input
int pirsensor = 7;              // choose the input pin (for PIR sensor)
int ledPin = 2;                 // choose the pin for the LED

//declare sensor value
int pirState = LOW;            
int val = 0;                   

//decalre counter time & reset
const unsigned long eventInterval = 8000;
unsigned long previousTime = 0;


//////////////////////////////////////////////////////////////////////


void setup() {
  Serial.begin(9600);

///////////////////////////SD CARD & RTC////////////////////////////////
  SPI.begin();
  Serial.println("CLEARSHEET");
  Serial.println("LABEL, Data, Tanggal, Waktu");
  
  rtc.begin();
///////////////////////////PIR DAN LED////////////////////////////////

  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(pirsensor, INPUT);     // declare sensor as input

}

void loop() {

///////////////////////////PIR DAN LED, COUNTER////////////////////////////////
  char buffer1[56];
  unsigned long currentTime = millis();

  DateTime now = rtc.now();

  val = digitalRead(pirsensor);      // read input value
  
  if (val == HIGH) {                // check if the input is HIGH
    digitalWrite(ledPin, LOW);     // turn LED ON

    Serial.print("DATA,");
    Serial.print(val);
    Serial.print("\t  >> Motion detected!");
    Serial.print(",");
    Serial.print("DATE,");
    Serial.print(",");    
    Serial.print("TIME");
    Serial.println("");    

    if (currentTime - previousTime >= eventInterval) {
    	previousTime = currentTime;
    } 
  } 
  
  else if(val == LOW) { 
    Serial.print("DATA,");
    Serial.print(val);
    Serial.print("\t  >> Motion not detected!");
    Serial.print(",");
    Serial.print("DATE");
    Serial.print(",");    
    Serial.print("TIME");
    Serial.println("");    

    delay(3000);
    digitalWrite(ledPin, HIGH);
  }
  

  delay(1000);

}