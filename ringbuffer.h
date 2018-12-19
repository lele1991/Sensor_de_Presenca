#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

#include <stdint.h>
#include <avr/io.h>
#include <stdio.h>


void init();
uint8_t rbuf_empty();
uint8_t rbuf_full();
uint8_t read();
uint8_t write(uint8_t byte);

uint8_t ring_buffer_size();


#endif /* RINGBUFFER_H_ */
