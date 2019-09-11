/*
 * funciones.h
 *
 *  Created on: 4 sep. 2019
 *      Author: almustafa
 */

#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include "global.h"
#include <stdlib.h>

void copy(uint8_t *src, uint8_t* dest);

void diferencia(uint8_t *img1, uint8_t* img2, uint8_t umbral);
int conteo(uint8_t* img);

void binarizar(uint8_t *img, uint8_t umbral);

// Morfología
void dilatacion(uint8_t *img);
void erosion(uint8_t *img);
void apertura(uint8_t *img);
void cierre(uint8_t *img);

void bound_rectangulo(uint8_t *img, uint8_t valor, uint16_t* rect);
void filtrar_x_area(uint8_t *img, int min_area, uint16_t* rectangulos);

void vecinos(uint8_t *img, uint8_t valor, int x, int y, int* area);

#endif /* FUNCIONES_H_ */
