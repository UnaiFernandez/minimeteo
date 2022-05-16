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

//Egoera kodeak
#define TW_START 0x08
#define TW_RESTART 0x10
#define TW_SLAVE_W_ACK 0x18
#define TW_SLAVE_R_ACK 0x40
#define TW_DATA_ACK 0x28

// I2C modulua hasieratzeko funtzioa
void init_i2c();
// START egoera bidaltzeko funtzioa
int i2c_Start();
// RESTART egoera bidatzeko funztioa
int i2c_RStart();
// STOP egoera bidaltzeko funtzioa
void i2c_Stop();
// Esklabuari egin nahi den akzioa bidali
int i2c_addr(int addr, int r_w);
// Esklabuari mezua bidali
int i2c_Write(unsigned char data);
// Esklabutik mezua jaso
int i2c_Read(int en_ACK);

#endif //I2C_H
