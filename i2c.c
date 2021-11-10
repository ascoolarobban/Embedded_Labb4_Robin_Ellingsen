#include "i2c.h"


 void i2c_init(void) {

    //TWEN bit set in TWCR register to enable TWI.

    TWCR = (1 << TWEN);
    TWSR = 0x00;

    TWBR = 0x48;
}
void i2c_meaningful_status(uint8_t status) {
    //TWI Logic Status
    switch (status) {
        case 0x08:
        printf_P(PSTR("START\n"));
    }
}
inline void i2c_start() {

    //TWEN, TWINT, TWISTA bit set in TWCR register to enable SCL and SDA.

    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    while (!(TWCR & (1 << TWINT)));
}
inline void i2c_stop() {

    //TWINT bit set in TWCR register
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);

    while ((TWCR & (1 << TWSTO)));
}
inline uint8_t i2c_get_status(void) {

    uint8_t status;
    status = TWSR & 0xF8;

    return status;
}
inline void i2c_xmit_addr(uint8_t eeprom_addr, uint8_t i2c_rw) {

    //TWDR contains the next byte to be transmitted
    TWDR = (eeprom_addr & 0xfe) | (i2c_rw & 0x01);
    //TWINT & TWEN bit set in TWCR register
    TWCR = (1 << TWINT) | (1 << TWEN);

    while (!(TWCR & (1 << TWINT)));
}
inline void i2c_xmit_byte(uint8_t byte) {



  //  Assign TWDR register with byte to send
    TWDR = byte;

    // TWINT bit set in TWCR register
    TWCR = (1 << TWINT) | (1 << TWEN);

    while (!(TWCR & (1 << TWINT)));
}
inline uint8_t i2c_read_NAK() {

    //enable SCL and SDA pins
    TWCR = (1 << TWINT) | (1 << TWEN);

    //TWINT bit set in TWCR register clears the interrupt flag.
    while (!(TWCR & (1 << TWINT)));

    return TWDR;
}
inline void eeprom_wait_until_write_complete() {

    while (i2c_get_status() != 0x18) {
        i2c_start();
        i2c_xmit_addr(EEPROM_ADDR, I2C_W);
    }
}

uint8_t eeprom_read_byte(uint8_t eeprom_addr_write) {

    uint8_t readByte;
    //Start communication
    i2c_start();
    //Transmit address to the EEPROM memory and Write
    i2c_xmit_addr(EEPROM_ADDR, I2C_W);
    //Transmit the location in memory
    i2c_xmit_byte(eeprom_addr_write);

    //Start communication
    i2c_start();
    //Transmit address to the EEPROM memory and Read
    i2c_xmit_addr(EEPROM_ADDR, I2C_R);

    //Read byte on location and save
    readByte = i2c_read_NAK();
    //com stop.
    i2c_stop();

    return readByte;
}
void eeprom_write_byte(uint8_t eeprom_addr_write, uint8_t byte) {

    //Start communication
    i2c_start();
    //Transmit address to the EEPROM memory and Write
    i2c_xmit_addr(EEPROM_ADDR, I2C_W);

    //Transmit the location in memory
    i2c_xmit_byte(eeprom_addr_write);
    //Transmit the byte to write
    i2c_xmit_byte(byte);

    //Stop communication
    i2c_stop();
    eeprom_wait_until_write_complete();

}

