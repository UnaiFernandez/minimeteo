#include <avr/io.h>
#include <util/delay.h>




void dht_timeout_error(){
    DDRB |= (1 << PORTB1); //Irteera moduan konfiguratu
    PORTB &=~ (1 << PORTB1); //HIGH egoeran jarri
    PORTB |= (1 << PORTB0); //DHT11-ren LED gorria piztu
}

void dht_init(){
    DDRB |= (1 << PORTB1); //Pin-a irteera moduan konfiguratu
    PORTB |= (1 << PORTB1); //LOW egoeran jarri
    
    //LED-aren konfigurazioa
    DDRB |= (1 << PORTB0);
    PORTB &=~ (1 << PORTB0);
}

void dht_start(){
    //2 LOW egoeran jarri Pin-a
    PORTB &=~ (1 << PORTB1);
    //3 itxaron 18ms
    _delay_ms(18);
    //4 Pin-a HIGH jarri
    PORTB |= (1 << PORTB1);
    //5 itxaron 30 us
    _delay_us(30);
    //Lo del while va aqui
    //6 Pin-a sarrera moduan konfiguratu
    DDRB &=~ (1 << PORTB1);
}

void dht_response(){

}

void dht_data(){

}
