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
#define TW_ST_SLA_ACK 0xA8
#define TW_ST_DATA_ACK 0xC0

//Funtzioak
void init_TWI_slave();
void TWI_slave_write_match();
void TWI_slabe_write_data(unsigned char data);


#endif //TWI_MASTER_RECEIVER_H
