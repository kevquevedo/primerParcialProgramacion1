	/*
 * Informe.h
 *
 *  Created on: 8 may. 2020
 *      Author: VOPKEQUE
 */

#ifndef INFORME_H_
#define INFORME_H_

int info_imprimirArrayCantPubAct(Cliente* pArrayCli ,int lenCli, Publicacion* pArrayPub, int lenPub);
int info_imprimirArrayByEstado(Publicacion* pArrayPub, int lenPub, Cliente* pArrayCli, int lenCli);
int info_imprimirPubActivasByRubro(Publicacion* pArray, int len, int rubro);
int info_imprimirMaximosMinimosPubByRubros(Publicacion* pArray, int len, int MaxiOrMin);
int info_buscarRubro(Publicacion* pArray, int len, int rubro);
int info_calcularEImprmirAvisosCliente(Cliente* pArrayCli, int lenCli, Publicacion* pArrayPub, int lenPub, int estado);

#endif /* INFORME_H_ */
