#ifndef I2C_H
#define I2C_H

//Egoera kodeak
#define TW_ST_SLA_ACK 0xA8
#define TW_ST_DATA_ACK 0xB8

// I2C modulua hasieratzeko funtzioa
void init_i2c_slave(int addr);
// Nagusiari mezua bidali
int i2c_slave_trasmit(unsigned char data);
// Nagusitik mezua jaso
int i2c_slave_reslave_read(int en_ACK);

#endif //I2C_H

