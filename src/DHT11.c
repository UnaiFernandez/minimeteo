#include <avr/io.h>
#include <util/delay.h>




void dht_start(){
    //1 Pin-a irteera moduan konfiguratu
    DDRB |= (1 << PORTB1);
    //2 Pin-a LOW jarri
    PORTB1 &=~ (1 << PORTB1);
    //3 itxaron 18ms
    _delay_ms(18);
    //4 Pin-a HIGH jarri
    PORTB1 |= (1 << PORTB1);
    //5 itxaron 30 us
    _delay_us(30);
    //6 Pin-a sarrera moduan konfiguratu
    DDRB &=~ (1 << PORTB1);
}

void dht_response(){

}

void dht_data(){

}
