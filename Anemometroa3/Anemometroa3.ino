#include <SoftwareSerial.h>

#define RTS_pin 9

SoftwareSerial Anem(10, 11);

void setup(){

  pinMode(RTS_pin, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  Anem.begin(9600);
  Serial.begin(9600);
  delay(1000);
}
void loop(){
    digitalWrite(RTS_pin, HIGH);
    
    uint8_t Anemometer_request[] = {0x02, 0x03, 0x00, 0x00, 0x00, 0x01, 0x84, 0x39};
    Anem.write(Anemometer_request, sizeof(Anemometer_request));
    Anem.flush();
    
    digitalWrite(RTS_pin, LOW);
    
    uint8_t Anemometer_buff[8];
    Anem.readBytes(Anemometer_buff, 8);

    Serial.print("speed --> ");
    //if(Anemometer_buff[3] != 0x00){
      //Serial.print(Anemometer_buff[3]);  
    //}
    Serial.print(Anemometer_buff[4]);
    Serial.print("m/s");
    Serial.print("\r\n");
    
    if(Anemometer_buff[4] < 10){
      digitalWrite(12, 0);
      digitalWrite(13, 1);  
    }else{
      digitalWrite(13, 0);
      digitalWrite(12, 1);  
    }
    delay(500); 
}
