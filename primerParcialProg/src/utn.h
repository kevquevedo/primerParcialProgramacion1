/*
 * utn.h
 *
 *  Created on: 8 may. 2020
 *      Author: VOPKEQUE
 */

#ifndef UTN_H_
#define UTN_H_

int utn_getNameOrSurname(char* pResultado, int len, char* mensaje, char* mensajeError, int reintentos);
int utn_getCuit(char* pResultado, int len, char* mensaje, char* mensajeError, int reintentos);
int utn_getNumberInt(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos);
int utn_getDescription(char* pResultado, int len, char* mensaje, char* mensajeError, int reintentos);

#endif /* UTN_H_ */
