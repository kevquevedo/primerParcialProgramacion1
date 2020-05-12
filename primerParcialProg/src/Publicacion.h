/*
 * Publicacion.h
 *
 *  Created on: 8 may. 2020
 *      Author: VOPKEQUE
 */

#ifndef PUBLICACION_H_
#define PUBLICACION_H_

#define AVISO_LEN 65
#define ESTADO_PAUSADA	0
#define ESTADO_ACTIVA	1

typedef struct{
	int idCliente;
	int numRubro;
	char textAviso[AVISO_LEN];
	int idPublicacion;
	int isEmpty;
	int estado;
}Publicacion;

int pub_initializeArray(Publicacion* pArray, int len);
int pub_altaArray(Publicacion* pArray, int len, int indice, int* idPub, int idCli);
int pub_pausarArray(Publicacion* pArray,int len, int indice);
int pub_reanudarArray(Publicacion* pArray,int len, int indice);
int pub_imprimirArray(Publicacion* pArray,int len);
int pub_imprimirPublicByCliente(Publicacion* pArray, int len, int idCliBuscado);
int pub_getEmptyIndex(Publicacion* pArray, int len);
int pub_buscarId(Publicacion* pArray, int len, int indiceBuscado);
int pub_contAviAct(Publicacion* pArray, int len, int idCli);
int pub_contAviPau(Publicacion* pArray, int len, int idCli);
int pub_contAvisos(Publicacion* pArray, int len, int idCli);

int pub_altaForzadaArray(Publicacion* pArray,int len, int indice, int* idPub, int idCli, int numRubro , char* aviso);

#endif /* PUBLICACION_H_ */
