/*====================================================================
 *
 *  Filename: slave_sender.ino
 *
 *  Description: Fitxategi honen bidez morroiaren i2c modulua
 *               konfiguratu eta funtzio nagusiak definitzen dira.
 *
 *  Version: 1.0
 *  Created: 2022-06-19
 *  Author: Unai Fernandez
 *
 ====================================================================*/

#include <Wire.h>
#include <SoftwareSerial.h>
#include <stdio.h>

//MAX485-reko kontrol hankatxoa
#define RTS_pin 9

//I2C definizioak
#define TW_START 0x08
#define TW_ST_SLA_ACK 0xA8
#define TW_ST_DATA_ACK 0xB8
#define TW_ST_DATA_NACK 0xC0

//Anemometroarekin komunikazioa hasieratu
SoftwareSerial Anem(10, 11);


/*
 * Funtzio honen bidez, I2C modulua hasieratuko da.
 */
void init_TWI_slave(){
    DDRC &=~ (1 << PORTC5);
    DDRC &=~ (1 << PORTC4);
    PORTC = (1 << PORTC4) | (1 << PORTC5);
    TWBR = 72;
    TWCR  = (1 << TWEN) | (1 << TWEA);
    TWAR = 0x06 << 1;
}


/*
 * Funtzio honen bidez I2C moduluak datu eskaera bat detektatuko du.
 */
void TWI_slave_write_match(){
    TWCR = (1 << TWEA) | (1 << TWEN) | (1 << TWINT);
    while(!(TWCR & (1 << TWINT)));
    while((TWSR & 0xF8) != TW_ST_SLA_ACK);
}


/*
 * Funtzio honen bitartez, I2C moduluak datu bat bidaliko dio nagusiari
 */
void TWI_slabe_write_data(unsigned char data){
    TWDR = data;

    if((TWSR & 0xF8) == TW_ST_DATA_NACK){
        TWCR = (1 << TWEN) | (1 << TWINT);
    }else{
        TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);
    }
}


/*
 * Funtzio honek anemometrotik datuak eskuratuko ditu.
 */
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


/*
 * Funtzio honen barruan erabiliko diren modulu guztiak hasieratuko dira.
 */
void setup() {
    //Anemometroa hasieratu
    pinMode(RTS_pin, OUTPUT);
    Anem.begin(9600);
    delay(2000);
    //I2C modulua hasieratu
    init_TWI_slave();
}


/*
 * Funtzio hau begizta infinitu baten barruan exekutatzen da, beraz barruko
 * kodea etengabe exekutatuko da.
 */
void loop() {
    static int i = 0;
    static char msg [3] = "00";

    //Eskaera topatu
    TWI_slave_write_match();
    //Datua bidali
    TWI_slabe_write_data(msg[i]);

    if(i < 3){
        i++;
    }else{
        i = 0;
        //Datu osoa bidali denez, berri bat eskatzen zaio anemometroari
        get_anem(msg);
    }
    
    delay(100);
}
