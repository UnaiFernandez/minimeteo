/*====================================================================
 *
 *  Filename: twi_master_receiver.h
 *
 *  Description: twi_master_receiver.c-rako beharrezkoak diren aldagai
 *               eta funtzioen definizioak.
 *
 *  Version: 1.0
 *  Created: 2022-05-20
 *  Author: Unai Fernandez
 *
 ====================================================================*/

#ifndef TWI_MASTER_RECEIVER_H
#define TWI_MASTER_RECEIVER_H

//definizioak
#define TW_START 0x08
#define TW_MR_SLA_ACK 0x40
#define TW_MR_DATA_ACK 0x50

//Funtzioak
void init_TWI();
void TWI_master_start();
void TWI_master_stop();
void TWI_master_read_addr(unsigned char addr);
unsigned char TWI_master_read_data();


#endif //TWI_MASTER_RECEIVER_H
