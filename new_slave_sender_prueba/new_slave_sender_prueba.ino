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
//definizioak
#define TW_START 0x08
#define TW_ST_SLA_ACK 0xA8
#define TW_ST_DATA_ACK 0xB8
#define TW_ST_DATA_NACK 0xC0

SoftwareSerial Anem(10, 11);

//char msg [3] = ""; 
//int data;
//int req = 1;

void init_TWI_slave(){
    DDRC &=~ (1 << PORTC5);
    DDRC &=~ (1 << PORTC4);
    PORTC = (1 << PORTC4) | (1 << PORTC5);
    TWBR = 72;
    TWCR  = (1 << TWEN) | (1 << TWEA);
    TWAR = 0x06 << 1;
}


void TWI_slave_write_match(){
    TWCR = (1 << TWEA) | (1 << TWEN) | (1 << TWINT);
    while(!(TWCR & (1 << TWINT)));
    while((TWSR & 0xF8) != TW_ST_SLA_ACK);
}


void TWI_slabe_write_data(unsigned char data){
    TWDR = data;

    if((TWSR & 0xF8) == TW_ST_DATA_NACK){
        TWCR = (1 << TWEN) | (1 << TWINT);
    }else{
        TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);
    }
}


void get_anem(char* msg){
   
   digitalWrite(RTS_pin, Anem);
   uint8_t Anemometer_request[] = {0x02, 0x03, 0x00, 0x00, 0x00, 0x01, 0x84, 0x39};
   Anem.write(Anemometer_request, sizeof(Anemometer_request));
   Anem.flush();
   digitalWrite(RTS_pin, LOW);

   
   uint8_t Anemometer_buff[8];
   Anem.readBytes(Anemometer_buff, 8);

   sprintf(msg, "%X", Anemometer_buff[4]);
}
//char msg [3] = "2A"; 
//int data;
//char msg[3] = "1A";
//int i = 0;

void setup() {
  pinMode(RTS_pin, OUTPUT);
  Anem.begin(9600);
  delay(2000);
  init_TWI_slave();
}

void loop() {
    static int i = 0;
    //static int req = 1;
    static char msg [3] = "00";
    //static int data;
    
    TWI_slave_write_match();
    TWI_slabe_write_data(msg[i]);

    if(i < 3){
      i++;
    }else{
      i = 0;
      //msg[0] = msg[0] + 1;
      //if(msg[0] == '9')
        //msg[0] = '1';
      get_anem(msg);
      //digitalWrite(13, HIGH);
      //req = 1;
      //delay(100);
    }
    
    //Serial.print(msg);
    //Serial.println();
    delay(100);
}
