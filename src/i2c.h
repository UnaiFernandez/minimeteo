/*====================================================================
 *
 *  Filename: i2c.h
 *
 *  Description: i2c.c-rako beharrezkoak diren konfigurazio eta 
 *		 funtzioak 
 *
 *  Version: 1.0
 *  Created: 2022-05-03
 *  Author: Unai Fernandez
 *
 ====================================================================*/
#ifndef I2C_H
#define I2C_H

void initI2C();
void i2cWaitForComplete();
void i2cstart();
void i2cStop();
void i2cSend();
int i2cReadAck();
int i2cReadNoAck();

#endif //I2C_H
