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
	uint8_t counter=0;

	sei();
	//writing R to eeprom.
	eeprom_write_byte(EEPROM_ADDR_WRITE, 'R');
	eeprom_write_byte(EEPROM_ADDR_WRITE+1, 'o');
	eeprom_write_byte(EEPROM_ADDR_WRITE+2, 'b');
	eeprom_write_byte(EEPROM_ADDR_WRITE+3, 'i');
	eeprom_write_byte(EEPROM_ADDR_WRITE+4, 'n');
	while (1) {

	    printf_P(PSTR("%c"), eeprom_read_byte(EEPROM_ADDR_WRITE+counter));
	    counter++;
	    if(counter == 5){
	        counter = 0;
	        printf_P(PSTR("\n"));
	    }

	}
	return 0;
}

