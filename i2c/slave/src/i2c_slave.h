#ifndef I2C_H
#define I2C_H

//Egoera kodeak
#define TW_ST_SLA_ACK 0xA8
#define TW_ST_DATA_ACK 0xB8

// I2C modulua hasieratzeko funtzioa
void init_i2c_slave();
// Nagusiari mezua bidali
void i2c_slave_transmit_match();
// Nagusitik mezua jaso
void i2c_slave_write(char data);

#endif //I2C_H

