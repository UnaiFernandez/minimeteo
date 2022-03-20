/*====================================================================
 *
 *  Filename: wifi.h
 *
 *  Description: wifi.c-rako beharrezkoak diren funtzioen eta aldagaien 
 *		 definizioak
 *
 *  Version: 1.0
 *  Created: 2022-02-11
 *  Author: Unai Fernandez
 *
 ====================================================================*/
#ifndef WIFI_H
#define WIFI_h


enum RESPONSE_STATUS{
    RESPONSE_WAITING,
    RESPONSE_OK,
    RESPONSE_TIMEOUT,
    RESPONSE_ERROR
};

enum WIFI_MODE{
    STA=1,
    AP,
    BOTH,
};

int response_status;
int hezetasuna[2];
int tenperatura[2];
/*FUNTZIOAK*/
//Bidali komandoa
int send_command(char * command, char * resp);
//Funtzionamendua egiaztatu
int hello_ESP();
//AP konfiguratu
int AP_setup(char * ssid, char * pwd, int channel, int enc);
//ESP-aren operazio modua aukeratu
int ESP_mode(int mode);
//ESP-ak konexio bat edo gehiago gaitzeko Funtzioa
int ESP_multiple_conn(int conn);
//ESP-a zerbitzari moduan konfiguratu
int ESP_server(int en, char * port);
//Zerbitzariaren timeouta konfiguratu
int ESP_server_timeout(char * time);
//TCP bidez mezu bat bidaltzeko
int TCP_send(int id, char* msg);
//TCP mezuari erantzun
int TCP_response(char * msg);
//TCP konexio bat itxi
int TCP_close(char id);
#endif //WIFI_H
