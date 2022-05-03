/*====================================================================
 *
 *  Filename: i2c.c
 *
 *  Description: Fitxategi honen bidez bi Atmega328p mikroen artean 
 *		 komunikazioa i2c-ren bidez egon dadin beharrezkoak 
 *		 diren funtzioak sortuko dira. 
 *
 *  Version: 1.0
 *  Created: 2022-05-03
 *  Author: Unai Fernandez
 *
 ====================================================================*/
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>


