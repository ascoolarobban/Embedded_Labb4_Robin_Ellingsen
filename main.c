#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>

#include "adc.h"
#include "gpio.h"
#include "i2c.h"
#include "serial.h"
#include "timer.h"


int main (void) {
    //start i2c.
	i2c_init();
	//start com.
	uart_init();

	sei();
	//writing R to eeprom.
	eeprom_write_byte(EEPROM_ADDR_WRITE, 'R');
	while (1) {
	    //reading stored R with \n
	    printf_P(PSTR("%c \n"), eeprom_read_byte(EEPROM_ADDR_WRITE));
	}
	return 0;
}

