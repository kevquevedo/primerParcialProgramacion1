/*
 * Cliente.h
 *
 *  Created on: 8 may. 2020
 *      Author: VOPKEQUE
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_
#include "Publicacion.h"

#define NOMBRE_LEN 20
#define APELLIDO_LEN 20
#define CUIT_LEN 14

typedef struct{
	char nombre[NOMBRE_LEN];
	char apellido[APELLIDO_LEN];
	char cuit[CUIT_LEN];
	int idCliente;
	int isEmpty;
}Cliente;

int cli_initializeArray(Cliente* pArray, int len);
int cli_altaArray(Cliente* pArray, int len, int indice, int* id);
int cli_modificarArray(Cliente* pArray,int len, int indice);
int cli_bajaArray(Cliente* pArrayCli,int lenCli, int id,Publicacion* pArrayPub, int lenPub);
int cli_imprimirArray(Cliente* pArray,int len);
int cli_imprimirClienteByIdPub(Cliente* pArrayCli, int lenCli, int idPubBuscado, Publicacion* pArrayPub, int lenPub);
int cli_getEmptyIndex(Cliente* pArray, int len);
int cli_buscarId(Cliente* pArray, int len, int idBuscado);

int cli_altaForzadaArray(Cliente* pArray,int len, int indice, int* id,char* nombre,char* apellido,char* cuit);

#endif /* CLIENTE_H_ */
