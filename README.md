# Automatic Detect The Presence of Human Activator Light Sensor System

## Introduction

The **Automatic Detect The Presence of Human Activator Light Sensor System** is an intelligent device designed for use in buildings, homes, and industries. This system automatically turns lights on when it detects human presence and off when the room is empty, thus saving energy and enhancing convenience. The system integrates various components, including a PIR sensor, an LED, an SD card for data logging, and a real-time clock (RTC) to timestamp events.

## Features

1. **Automatic Light Control**: Lights turn on automatically when motion is detected and turn off when no motion is detected for a specified duration.
2. **Energy Efficiency**: By turning off lights when the room is empty, the system conserves energy.
3. **Real-Time Logging**: Events are logged with timestamps, allowing for monitoring and analysis.
4. **Ease of Installation**: The system is designed to be easily integrated into existing electrical setups.

## Components

1. **PIR Sensor**: Detects human presence.
2. **LED**: Indicates the system's status.
3. **RTC Module**: Keeps track of the current time and date.
4. **SD Card Module**: Logs data for later analysis.
5. **Arduino**: The microcontroller that processes inputs and controls outputs.

## Prototype Schematic
![Prototype Proyek](https://github.com/Alfanfuad/Automatic-Detect-The-Present-of-Human-Activator-Light-Sensor-System/assets/71118100/1b7d2570-68a2-4715-ba64-6b0a240bd24f)


## Code Overview

The following Arduino code handles the operation of the system. It reads inputs from the PIR sensor and controls the LED based on motion detection. It also logs events to an SD card with timestamps from the RTC.

```c
#include <Arduino.h>
#include <Wire.h>
#include "RTClib.h"
#include <SPI.h>
#include <SD.h>

// Declare RTC and sensor inputs
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int pirsensor = 7;  // PIR sensor pin
int ledPin = 2;     // LED pin

// Declare sensor values and timing variables
int pirState = LOW; 
int val = 0;                   
const unsigned long eventInterval = 8000;
unsigned long previousTime = 0;

void setup() {
  Serial.begin(9600);

  // Initialize SD card and RTC
  SPI.begin();
  Serial.println("CLEARSHEET");
  Serial.println("LABEL, Data, Tanggal, Waktu");
  rtc.begin();

  // Initialize PIR sensor and LED
  pinMode(ledPin, OUTPUT);
  pinMode(pirsensor, INPUT);
}

void loop() {
  char buffer1[56];
  unsigned long currentTime = millis();
  DateTime now = rtc.now();
  val = digitalRead(pirsensor);

  if (val == HIGH) {
    digitalWrite(ledPin, LOW);
    Serial.print("DATA,");
    Serial.print(val);
    Serial.print("\t  >> Motion detected!");
    Serial.print(",DATE,");
    Serial.print(now.day());
    Serial.print("/");
    Serial.print(now.month());
    Serial.print("/");
    Serial.print(now.year());
    Serial.print(",TIME,");
    Serial.print(now.hour());
    Serial.print(":");
    Serial.print(now.minute());
    Serial.print(":");
    Serial.println(now.second());

    if (currentTime - previousTime >= eventInterval) {
      previousTime = currentTime;
    }
  } else if (val == LOW) {
    Serial.print("DATA,");
    Serial.print(val);
    Serial.print("\t  >> Motion not detected!");
    Serial.print(",DATE,");
    Serial.print(now.day());
    Serial.print("/");
    Serial.print(now.month());
    Serial.print("/");
    Serial.print(now.year());
    Serial.print(",TIME,");
    Serial.print(now.hour());
    Serial.print(":");
    Serial.print(now.minute());
    Serial.print(":");
    Serial.println(now.second());

    delay(3000);
    digitalWrite(ledPin, HIGH);
  }
  
  delay(1000);
}
```

## Explanation:
- **Initialization**: The setup function initializes the serial communication, SPI, RTC, and sensor pins.
- **Loop Function**: Continuously checks the PIR sensor for motion detection. If motion is detected, the LED is turned on, and the event is logged with the current date and time. If no motion is detected, the LED is turned off after a delay.

## How to Use
1. **Set up the hardware**: Connect the PIR sensor, LED, RTC, and SD card module to the Arduino as per the pin configuration in the code.
2. **Upload the code**: Use the Arduino IDE to upload the code to the Arduino board.
3. **Monitor the system**: Open the Serial Monitor in the Arduino IDE to view real-time data and verify the system's operation.

## Result Data Logging
![Data Log_Simulasi](https://github.com/Alfanfuad/Automatic-Detect-The-Present-of-Human-Activator-Light-Sensor-System/assets/71118100/a2c387c4-68ef-4a48-a6c6-7748f9d8c747)

## Video Demonstration
For a detailed walkthrough of the project, please watch the video demonstration >>>>>>>> [YouTube Link](https://youtu.be/PIXv2q5NlKo)
