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
    _delay_ms(1);  //mezua jasotzeko 1ms itxaron

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
int AP_setup(char * ssid, char * pwd, char channel, char enc){
    char command[70];

    sprintf(command, "AT+CWSAP=\"%s\",\"%s\",%c,%c", ssid, pwd, channel, enc);
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
    char m = mode + '0';
    char command[12];

    sprintf(command, "AT+CWMODE=%c", m);
    if(send_command(command, "OK") == RESPONSE_OK)
	return 1;
    return 0;
}

/*
 * Funtzio hau konexio bat baino gehiago egotea gaitzeko edo desgaitzeko balio du.
 *
 * Parametroak:
 *  - conn: Balioa 0 bada konexio bakarra egongo da eta 1 bada konexio bat baino gehiago 
 *	    egotea ahalbidetuko du funtzioak
 */
int ESP_multiple_conn(int conn){
    char command[12];
    char c = conn + '0';

    sprintf(command, "AT+CIPMUX=%c", c);
    if(send_command(command, "OK") == RESPONSE_OK)
	return 1;
    return 0;
}
