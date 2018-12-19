#include <stdio.h>
#include <avr/interrupt.h>
#include "lib/avr_gpio.h"
#include "lib/avr_usart.h"
#include "lib/bits.h"
#include "sensores.h"

void sensor_init(){

	GPIO_C->DDR = 0x00; 		//entrada - direçao
	/* Configura modo */
	PCICR = (1<<PCIE1);
	PCMSK1 = SET(PCINT8) | SET(PCINT9 | SET(PCINT10) | SET(PCINT11));
}

volatile uint8_t sensores[4] = {0, 0, 0, 0};

ISR(PCINT1_vect){
	if(GPIO_PinTstBit(GPIO_C, PC0)){
		sensores[0] = 1;
	}
	else{
		sensores[0] = 0;
	}

	if(GPIO_PinTstBit(GPIO_C, PC1)){
		sensores[1] = 1;
	}
	else{
		sensores[1] = 0;
	}

	if(GPIO_PinTstBit(GPIO_C, PC2)){
		sensores[2] = 1;
	}
	else{
		sensores[2] = 0;
	}

	if(GPIO_PinTstBit(GPIO_C, PC3)){
		sensores[3] = 1;
	}
	else{
		sensores[3] = 0;
	}

}

uint8_t get_sensor(uint8_t n_sensor){

	if(n_sensor<4){
		return sensores[n_sensor];
	}
	return 0xff;
}
