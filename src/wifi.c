/*====================================================================
 *
 *  Filename: wifi.c
 *
 *  Description: Fitxategi honen bidez Atmega328p mikroa eta ESP-01 wifi
 *		 modulua elkarkomunikatzeko beharrezkoak dauden funtzioak
 *		 aurkituko dira.
 *
 *  Version: 1.0
 *  Created: 2022-02-11
 *  Author: Unai Fernandez
 *
 ====================================================================*/

#define F_CPU 16000000
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include <avr/io.h>

#include "wifi.h"
#include "USART.h"

/*
 * Funtzio honen bidez, komandoak bidali egingo dira ESP-01 modulura eta honen erantzuna itxarongo du.
 *
 * Parametroak:
 *  - command: Bidali nahi den komadoa
 *  - resp: Espero den erantzuna
 *
 * Erantzuna zuzena bada, RESPONSE_OK bueltetuko du eta kontrakoa bada, RESPONSE_ERROR.
 */
int send_command(char * command, char * resp){
    
    //Bidali komandoa
    USART_string(command);
    USART_string("\r\n");
    response_status = RESPONSE_WAITING;
    _delay_ms(10);  //mezua jasotzeko 1ms itxaron

    //LED berdea pizteko komandoa bidali
    if(strstr(response, resp) != NULL)
	response_status = RESPONSE_OK;
    else
	response_status = RESPONSE_ERROR;


    return response_status;
}

/*
 * Funtzio honen bidez, WiFi moduluaren fintzionamendu zuzena egiaztatuko da.
 *
 * Dena ondo badoa funtzioak 1 balioa bueltatuko du, bestela 0.
 */
int hello_ESP(){
    int init_ok = 0;
    int success = 0;

    //Bidali ATE0 komandoa, echo desgaitzeko. Modu honetan ESP-ak ez du komandoa errepikatuko erantzuteko orduan.
    if(send_command("ATE0", "OK") == RESPONSE_OK){
	success++;	
    }
    //Bidali AT funtzionatzen duen ikusteko.
    if(send_command("AT", "OK") == RESPONSE_OK)
	success++;

    if(success == 2 )
	init_ok = 1;

    return init_ok;
}


/*
 * Funtzio honen bitartez, Modulua AP moduan dagoenerako ssid-a eta pasahitza bezalako parametroak konfiguratzeko balioko du.
 *
 * Parametroak:
 *  -ssid: Wifiaren izena
 *  -pwd: Wifiaren pasahitza
 *  -channel: Kanala
 *  -enc: Enkripzio maila
 *
 *	-> 0 = OPEN
 *	-> 2 = WPA_PSK
 *	-> 3 = WPA2_PSK
 *	-> 4 = WPA_WPA2_PSK
 *
 * Dena ondo badoa, 1 bueltatuko du. Bestela 0.
 */
int AP_setup(char * ssid, char * pwd, int channel, int enc){
    char command[70] = "\0";

    sprintf(command, "AT+CWSAP=\"%s\",\"%s\",%d,%d", ssid, pwd, channel, enc);
    if(send_command(command, "OK") == RESPONSE_OK)
	return 1;
    return 0;
}

/*
 * Funtzio hau ESP moduluaren operazio modua aukeratzeko da.
 *
 * Parametroak:
 *  - mode: Operazio modua zehaztuko duen zenbakia.
 *	
 *	-> 1 = STA
 *	-> 2 = AP
 *	-> 3 = BOTH (bi moduak batera)
 */
int ESP_mode(int mode){
    char command[12] = "\0";

    sprintf(command, "AT+CWMODE=%d", mode);
    if(send_command(command, "OK") == RESPONSE_OK)
	return 1;
    return 0;
}

/*
 * Funtzio hau konexio bat baino gehiago egotea gaitzeko edo desgaitzeko balio du.
 *
 * Parametroak:
 *  - en: Balioa 0 bada konexio bakarra egongo da eta 1 bada konexio bat baino gehiago 
 *	    egotea ahalbidetuko du funtzioak
 */
int ESP_multiple_conn(int en){
    char command[12] = "\0";

    sprintf(command, "AT+CIPMUX=%d", en);
    if(send_command(command, "OK") == RESPONSE_OK)
	return 1;
    return 0;
}

/*
 * Funtzio hau ESP modulua zerbitzari moduan programatzeko balioko du.
 *
 * Parametroak:
 *  - en: Balioa 1 bada zerbitzari modua ahalbidetzen da eta 0 bada desaktibatu egiten da.
 *  - port: Portu zenbakia zehazteko.
 */
int ESP_server(int en, char* port){
    char command[22] = "\0";

    //ESP moduluak zerbitzari moduan lan egin dezan, konexio bat baino 
    //gehiago egotea ahalbidetua egon behar du.
    ESP_multiple_conn(1);
    sprintf(command, "AT+CIPSERVER=%d,%s", en, port);
    if(send_command(command, "OK") == RESPONSE_OK)
	return 1;
    return 0;
}


/*
 * Funtzio hau ESP modulua zerbitzari moduan dagoenean, bezeroarekin timeout 
 * bat konfiguratzeko balio du.
 *
 * Parametroak:
 *  - time: Konexioa isteko denbora.
 */
int ESP_server_timeout(char * time){
    char command[15] = "\0";

    sprintf(command, "AT+CIPSTO=%s", time);
    if(send_command(command, "OK") == RESPONSE_OK)
	return 1;
    return 0;
}

/*
 * Funtzio hau TCP bidez mezuak bidaltzeko balio du.
 *
 * Parametroak:
 *  - id: Konexioaren identifikadorea
 *  - msg: Bidali nahi den mezua. Kontuan eduki behar da mezua, '\r' 
 *	   karakterearekin bukatu behar duela.
 */
int TCP_send(int id, char * size, char* msg){
    char command [15] = "\0";
    int s = strlen(msg)+2;


    sprintf(command, "AT+CIPSEND=%d,%d", id, s);
    _delay_ms(100);
    if(send_command(command, "OK") == RESPONSE_OK){
	PORTB |= (1 << PORTB4); //LED berdea piztu
	//_delay_ms(100);
	USART_string(msg);
	USART_string("\n\r");
	return 1;
    }else
	PORTB |= (1 << PORTB5); //LED gorria piztu
    //if(send_command(command, "OK") == RESPONSE_ERROR)
	//PORTB |= (1 << PORTB5); //LED gorria piztu

    return 0;
}

int TCP_response(char * msg){
    //Get hitza badauka mezuak
    if(strstr(msg, "GET") != NULL){
	TCP_send(0, "2", "que tal");
	return 1;
    }
    return 0;
}

/*
 * Funtzio honen bidez TCP konexio bat itxi egingo da.
 *
 * Parametroak:
 *  - id: Konexioare identifikadorea
 */
int TCP_close(char id){
    char command[14] = "\0";
    
    sprintf(command, "AT+CIPCLOSE=%c", id);
    if(send_command(command, "OK") == RESPONSE_OK)
	return 1;
    return 0;
}
