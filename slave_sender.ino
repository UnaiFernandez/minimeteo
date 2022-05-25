// Wire Slave Sender
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Sends data as an I2C/TWI slave device
// Refer to the "Wire Master Reader" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>
#include <SoftwareSerial.h>
#include <stdio.h>

#define RTS_pin 9

SoftwareSerial Anem(10, 11);

char msg [3] = ""; 
int data;

void setup() {
  pinMode(RTS_pin, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  Anem.begin(9600);
  Serial.begin(9600);
  delay(1000);
  
  Wire.begin(6);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
}

void loop() {
    digitalWrite(RTS_pin, HIGH);
    
    uint8_t Anemometer_request[] = {0x02, 0x03, 0x00, 0x00, 0x00, 0x01, 0x84, 0x39};
    Anem.write(Anemometer_request, sizeof(Anemometer_request));
    Anem.flush();
    
    digitalWrite(RTS_pin, LOW);
    
    uint8_t Anemometer_buff[8];
    Anem.readBytes(Anemometer_buff, 8);

    data = (int)Anemometer_buff[4];

    for(int j = 0; j < 7; j++){
      Serial.print(Anemometer_buff[j], HEX);
      Serial.print(" ");
    }
    Serial.print("  =====>  ");
    
    sprintf(msg, "%X", Anemometer_buff[4]);
    Serial.print(msg);
    Serial.println();
    delay(1000);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  static int i = 0;
  Wire.write(msg[i]); // respond with message of 6 bytes
  if(i < 3)
    i++;
  else
    i = 0;
  // as expected by master
}
