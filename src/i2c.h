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

void init_i2c();
void i2c_Start();
void i2c_Stop();
void i2c_Write(unsigned char data);
int i2c_ACK();
int i2c_NACK();

#endif //I2C_H
