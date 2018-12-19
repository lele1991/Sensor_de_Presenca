/*
 * 03_main_uart_debug.c
 *
 *  Created on: Aug 30, 2018
 *      Author: xtarke
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lib/avr_gpio.h"
#include "lib/bits.h"

#include "lib/avr_usart.h"
#include "sensores.h"
#include "modbus.h"

#include "ringbuffer.h"

int main(){

	/* Habilita IRQ global */
	sei();

	uint8_t i=0;

	/* Obtem o stream de depuração */
	FILE *debug = get_usart_stream();


	stdout = debug;

	/* Inicializa hardware da USART */
	USART_Init(B9600);

	//inicializa ring buffer
	init();

	/*INICIALIZA�AO DO SENSOR*/
	sensor_init();
	GPIO_B->DDR= SET(PB5);


	uint8_t modbus_busy = 0;

	while (1){

		if (modbus_busy){ // se ele nao esta ocupado // se for 1
			modbus_busy = modbus_write(get_sensor(i),(0x05+i)); //modbus_write retorna 1 quando termina de enviar o pacote //1
		}

		modbus_busy = modbus_receive(); // 0 se tiver certo e 1 se tiver cheio e 2 errado

		if (modbus_busy){
			i++;
		}

		if(i==4)
			i=0;

		_delay_ms(500);

	}
}
