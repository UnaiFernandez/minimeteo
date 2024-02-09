/*====================================================================
 *
 *  Filename: wifi.c
 *
 *  Description: Fitxategi honen bidez Atmega328p mikroa eta ESP8266 wifi
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
#include <stdlib.h>

#include "wifi.h"
#include "USART.h"
#include "defines.h"
#include "timers.h"


int response_status;
/*
 * Funtzio honen bidez, komandoak bidali egingo dira ESP8266 modulura eta honen erantzuna itxarongo du.
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
    t2_count = 0;
    delay_ms(10);  //mezua jasotzeko 10ms itxaron

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


void ESP_RST(){
    send_command("AT+RST", "OK");
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
int TCP_send(int id, char* msg){
    char command [24] = "\0";
    int size = strlen(msg)+2;


    sprintf(command, "AT+CIPSEND=%d,%d", id, size);
    t2_count = 0;
    delay_ms(100);
    if(send_command(command, "OK") == RESPONSE_OK){
	PORTB &=~ (1 << PORTB3); //LED horia itzali
	USART_string(msg);
	USART_string("\n\r");
	return 1;
    }else{
	PORTB |= (1 << PORTB5); //LED gorria piztu
    }
    return 0;
}

/*
 * Funtzio honek bezeroari erantzun bat bidaliko dio jasotako mezuaren arabera
 *
 * Parametroak:
 *  - msg: Bezeroak bidalitako mezua.
 */
int TCP_response(char * msg){
    //Get hitza badauka mezuak
    t2_count = 0;
    delay_ms(10);//invent
    int conn_id = msg[5]-'0';
    if(strstr(msg, "GET") != NULL){
	char m[22] = "\0";
	char h_1[4];
	char h_2[4];
	char t_1[4];
	char t_2[4];


	itoa(hezetasuna[0], h_1, 10);
	itoa(hezetasuna[1], h_2, 10);
	itoa(tenperatura[0], t_1, 10);
	itoa(tenperatura[1], t_2, 10);

	sprintf(m, "OK:%s.%s:%s.%s:%s", h_1, h_2, t_1, t_2, anem);
	TCP_send(conn_id, m);
	return 1;
    }else{
	TCP_send(conn_id, "ERROR");
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


/*---------------------------------------------------------------------*/

