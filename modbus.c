/* modbus.c
 *
 *  Created on: Nov 1, 2018
 *      Author: xtarke
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "lib/avr_gpio.h"
#include "lib/avr_usart.h"
#include "ringbuffer.h"
#include "lib/bits.h"


uint16_t CRC16_2(uint8_t *buf, int len)
{
  uint32_t crc = 0xFFFF;
  int i;

  for (i = 0; i < len; i++)
  {
    crc ^= (uint16_t)buf[i];          // XOR byte into least sig. byte of crc

    for (int i = 8; i != 0; i--) {    // Loop over each bit
      if ((crc & 0x0001) != 0) {      // If the LSB is set
        crc >>= 1;                    // Shift right and XOR 0xA001
        crc ^= 0xA001;
      }
      else                            // Else LSB is not set
        crc >>= 1;                    // Just shift right
    }
  }
  // Note, this number has low and high bytes swapped, so use it accordingly (or swap bytes)
  return crc;
}

uint8_t is_pkg_ready(uint8_t size){
	if (ring_buffer_size() == size)
		return 1;
	else
		return 0;
}


uint8_t modbus_write(uint8_t dados, uint8_t endereco){
	uint8_t pkg_sensores[8] = {0x15, 0x01, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00}; //end, R/W, reg, dados, crc
	uint8_t i;
	uint16_t crc;

	CLR_BIT(GPIO_B->PORT, PB5);
//PRIMEIRO PACOTE (s0)
	//big_endian
	pkg_sensores[3] =endereco;
	pkg_sensores[4] = dados >> 8;
	pkg_sensores[5] = dados & 0xff;

	crc = CRC16_2(pkg_sensores,6);

	pkg_sensores[6] = crc >> 8;
	pkg_sensores[7] = crc & 0xff;

	for (i=0; i < 8; i++){
		USART_tx(pkg_sensores[i]); //enviando para a usart todo o pacote s0
	}

	return 1;
}

uint8_t modbus_receive(){

	uint8_t i,pkg;

	if (is_pkg_ready(8)){ //se for vazio
		return 1;
	}

	for (i=0; i < 8; i++){
		pkg = read();
		if (i == 1){
			if (pkg == 0x01){
				return 0;
			}
		}
	}

	return 2;
}
