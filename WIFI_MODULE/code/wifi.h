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

/*FUNTZIOAK*/
//Bidali komandoa
int send_command(char * command, char * resp);
//Funtzionamendua egiaztatu
int hello_ESP();
//AP konfiguratu
int AP_setup(char * ssid, char * pwd, char channel, char enc);
//ESP-aren operazio modua aukeratu
int ESP_mode(int mode);

#endif //WIFI_H
