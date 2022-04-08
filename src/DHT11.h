/*====================================================================
 *
 *  Filename: DHT11.h
 *
 *  Description: DHT11.c-rako beharrezkoak diren funtzioen definizioak 
 *
 *  Version: 1.0
 *  Created: 2022-03-18
 *  Author: Unai Fernandez
 *
 ====================================================================*/
#ifndef DHT11_H
#define DHT11_H


/*FUNTZIOAK*/
//Timeout errorea
void dht_timeout_error();
//Beharrezko hasieraketak egin
void dht_init();
//Start seinalea bidali sentsoreari
void dht_start();
//Sentsorearen erantzuna jaso
void dht_response();
//Sentsoreak bidalitako datuen prozesamendua
int dht_data();
//Datuen zuzentasuna egiaztatu
int dht_checksum(int h_osoa, int h_hamar, int t_osoa, int t_hamar, int checksum);
//Sentsoreari datu eskaera prozesu osoa
void get_dht_data();
#endif //DHT11_H


