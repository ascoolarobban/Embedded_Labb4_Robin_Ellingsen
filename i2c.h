#ifndef _I2C_H_
#define _I2C_H_


#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>

#include "adc.h"
#include "gpio.h"
#include "serial.h"
#include "timer.h"



#define EEPROM_ADDR 0xA0
 #define EEPROM_ADDR_WRITE 0x10



// I2C Read/Write flags
#define I2C_R	1
#define I2C_W	0

#define EEPROM_ADDR_WRITE 0x10


void i2c_init(void);

void i2c_start(void);
void i2c_stop(void);

uint8_t i2c_get_status(void);
void i2c_meaningful_status(uint8_t status);

void i2c_xmit_addr(uint8_t address, uint8_t rw);
void i2c_xmit_byte(uint8_t data);

void eeprom_wait_until_write_complete(void);

uint8_t eeprom_read_byte(uint8_t eeprom_addr_write);
void eeprom_write_byte(uint8_t eeprom_addr_write, uint8_t byte);

void eeprom_wait_until_write_complete(void);

#endif // _I2C_H_
