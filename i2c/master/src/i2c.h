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
#define TW_MT_SLA_ACK 0x18
#define TW_MR_SLA_ACK 0x40
#define TW_MT_DATA_ACK 0x28

// I2C modulua hasieratzeko funtzioa
void init_i2c_master();
// START egoera bidaltzeko funtzioa
void i2c_Start();
// RESTART egoera bidatzeko funztioa
void i2c_RStart();
// STOP egoera bidaltzeko funtzioa
void i2c_Stop();
// Esklabuari egin nahi den akzioa bidali
void i2c_slave_addr(int addr, int r_w);
// Esklabuari mezua bidali
void i2c_master_transmit(unsigned char data);
// Esklabutik mezua jaso
char i2c_master_receive(int en_ACK);

#endif //I2C_H

