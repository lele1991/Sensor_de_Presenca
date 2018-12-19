#ifndef _MODBUS_H
#define _MODBUS_H

#include <stdint.h>
#include <avr/io.h>
#include <stdio.h>

uint8_t modbus_write(uint8_t dados,uint8_t endereco);
uint8_t modbus_receive();


#endif
