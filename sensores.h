#ifndef _SENSORES_H
#define _SENSORES_H

#include <stdint.h>
#include <avr/io.h>
#include <stdio.h>

void sensor_init();
uint8_t get_sensor(uint8_t n_sensor);


#endif
