/*====================================================================
 *
 *  Filename: defines.h
 *
 *  Description: Erabili behar diren aldagai orokorren definizioa
 *
 *  Version: 1.0
 *  Created: 2022-03-21
 *  Author: Unai Fernandez
 *
 ====================================================================*/
#ifndef DEFINES_H
#define DEFINES_H

//DHT11
extern int hezetasuna [2];
extern int tenperatura [2];
extern int checksum;
extern volatile int dht_timeout;
extern volatile int timeout_en;
extern volatile int timeout_init;

#endif //DEFINES_H
