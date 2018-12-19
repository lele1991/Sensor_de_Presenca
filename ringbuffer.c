#include <stdint.h>
#include <avr/io.h>
#include <stdio.h>
#include "ringbuffer.h"

#define BUFFER_SIZE 64


typedef struct ringbuffer{
	uint8_t size;
	uint8_t rd;
	uint8_t wr;
	uint8_t buf[BUFFER_SIZE];
} t_ringbuffer;

volatile t_ringbuffer  rbuf;

void init(){
	rbuf.size=0;
	rbuf.rd = 0;
	rbuf.wr = 0;
}

uint8_t rbuf_empty(){


	if ((rbuf.size) == 0){
		return 1;
	} else {
		return 0;
	}
}
uint8_t rbuf_full(){

	if (rbuf.size == BUFFER_SIZE)
		return 1;
	else
		return 0;
}

uint8_t read(){
	char tmp = 0;

	if(!rbuf_empty(rbuf)){
		rbuf.size--;
		tmp = rbuf.buf[rbuf.rd];
		rbuf.rd = (rbuf.rd + 1) % BUFFER_SIZE;
	}
	return tmp;
}
uint8_t write(uint8_t byte){

	if(!rbuf_full()){
		rbuf.size++;
		rbuf.buf[rbuf.wr] = byte;
		rbuf.wr++;
		rbuf.wr = rbuf.wr & (BUFFER_SIZE - 1);

		return 1;
	}
	return 0;
}


uint8_t ring_buffer_size(){
	return rbuf.size;
}


