/*
 * Publicacion.c
 *
 *  Created on: 8 may. 2020
 *      Author: VOPKEQUE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "Publicacion.h"
#include "Cliente.h"
#include "Informe.h"

/**
 * \brief Inicializa el array Publicaciones.
 * \param pArray Array de publicaciones a actualizar.
 * \param len Limite del array de publicaciones.
 * \return Retorna 0 si inicializó el array correctamente y -1 si tuvo algún error.
 *
 */
int pub_initializeArray(Publicacion* pArray, int len)
{
	int retorno = -1;
	int i;

	if(pArray != NULL && len > 0)//Valida que los datos de la funcion sean correctos.
	{
		for(i=0;i<len;i++)
		{
			pArray[i].isEmpty = 1;//Cambia el estado a "vacio" a todos los indices.
		}
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief Da de alta una publicacion en una posicion del array.
 * \param pArray Puntero al array de publicaciones a actualizar.
 * \param len Es la longitud del array.
 * \param indice Posicion a ser actualizada/cargada.
 * \param idPub Identificador unico asignado a la publicacion.
 * \param idCli Identificador unico del cliente.
 * \return Retorna 0 si dió de alta la publicacion correctamente y -1 si tuvo algún error.
 *
 */

int pub_altaArray(Publicacion* pArray, int len, int indice, int* idPub, int idCli)
{
	int retorno = -1;
	Publicacion auxiliar;

	if(pArray != NULL && len > 0 && indice < len && idPub != NULL && idCli > -1)//Valida que los datos de la funcion sean correctos.
	{
		if( !utn_getNumberInt(&auxiliar.numRubro,"Ingrese un rubro (Debe ser numerico entre 1-1000):\n","Rubro invalido.\n",0,1000,2) &&//Obtiene un numero de rubro entre el 0 y 1000.
			!utn_getDescription(auxiliar.textAviso,AVISO_LEN,"Ingrese una descripción (Máximo 64 caracteres):\n","Descripción invalida.\n",2))//Obtiene una descipcion de la publicacion.
		{
			retorno = 0;
			pArray[indice] = auxiliar;//Clona la informacion del array correspondiente al indice brindado en auxiliar.
			pArray[indice].idCliente = idCli;//Se le asigna el numero de ID brindado.
			pArray[indice].isEmpty = 0;//Se cambia el estado a "cargado".
			pArray[indice].estado = 1;//Se cambia el estado a "activo".
			pArray[indice].idPublicacion = *idPub;//Se le asigna un ID unico.
			(*idPub)++;//Se incrementa el ID.
		}
	}
	return retorno;
}

/**
 * \brief Imprime el array de publicaciones cuando los indices esten cargados.
 * \param pArray Puntero al array de publicaciones.
 * \param len Es la longitud del array.
 * \return \return Retorna 0 si imprimió correctamente y -1 si tuvo algún error.
 *
 */
int pub_imprimirArray(Publicacion* pArray,int len)
{
	int retorno = -1;
	int i;
	if(pArray != NULL && len > 0)//Valida que los datos de la funcion sean correctos.
	{
		retorno = 0;
		for(i=0;i<len;i++)
		{
			if(pArray[i].isEmpty == 0)//Valida que el estado sea "cargado".
			{
				printf("\nID Cliente: %d - ID Publicacion: %d - Rubro: %d - Texto del aviso: %s - Estado: %d.",pArray[i].idCliente,pArray[i].idPublicacion,pArray[i].numRubro,pArray[i].textAviso,pArray[i].estado);
			}
		}
	}
	return retorno;
}

/**
 * \brief Imprime las publicaciones de un ID de cliente.
 * \param pArray Puntero al array de publicaciones.
 * \param len Es la longitud del array.
 * \param idCliBuscado Es el ID del cliente a imprimir publicaciones.
 * \return \return Retorna 0 si imprimió correctamente y -1 si tuvo algún error.
 *
 */
int pub_imprimirPublicByCliente(Publicacion* pArray, int len, int idCliBuscado)
{
	int retorno = -1;
	int i;
	int contador = 0;
	if(pArray != NULL && len > 0 && idCliBuscado > -1)//Valida que los datos de la funcion sean correctos.
	{
		retorno = 0;
		for(i=0;i<len;i++)
		{
			if( pArray[i].isEmpty == 0 &&
				pArray[i].idCliente == idCliBuscado)//Valida que este "cargado el indice y que se encuentre el ID brindado.
			{
				contador++;
				printf("\nID Cliente: %d - ID Publicacion: %d - Rubro: %d - Texto del aviso: %s.",pArray[i].idCliente,pArray[i].idPublicacion,pArray[i].numRubro,pArray[i].textAviso);
			}
		}
		if(contador==0)//Si contador nunca se incrementó se imprime la siguiente leyenda.
		{
			printf("\nEl cliente no posee publicaciones.");
		}
		if(contador>0)//Si contador se incrementó se imprime la siguiente leyenda.
		{
			printf("\nEstas son las publicaciones del cliente.");
		}
	}
	return retorno;
}
/**
 * \brief Buscar la primer posición vacia en el array de publicaciones.
 * \param pArray Puntero al array de publicaciones.
 * \param len Es la longitud del array.
 * \return Retorna el indice de la posicion vacia si encontró un indice vacio y -1 si obtuvo algún error o no existen indices vacios.
 *
 */
int pub_getEmptyIndex(Publicacion* pArray, int len)
{
	int retorno = -1;
	int i;
	if(pArray != NULL && len > 0)//Valida que los datos de la funcion sean correctos.
	{
		for(i=0;i<len;i++)
		{
			if(pArray[i].isEmpty == 1)//valida que el indice este vacio.
			{
				retorno = i;//Devuelve el indice vacio.
				break;
			}
		}
	}
	return retorno;
}

/**
 * \brief Busca un ID de una publicacion y devuelve la posicion en la que se encuentra.
 * \param pArray Puntero al array de publicaciones.
 * \param len Es la longitud del array.
 * \param idBuscado Id a buscar en el array de publicaciones.
 * \return Retorna el indice de la posicion buscada en caso de existir y -1 si obtuvo algún error o no existe el indice buscado.
 *
 */
int pub_buscarId(Publicacion* pArray, int len, int idBuscado)
{
	int retorno = -1;
	int i;
	if(pArray != NULL && len > 0 && idBuscado > -1)//Valida que los datos de la funcion sean correctos.
	{
		for(i=0;i<len;i++)
		{
			if( pArray[i].isEmpty == 0 &&
				pArray[i].idPublicacion == idBuscado)//Valida que este "cargado el indice y que se encuentre el ID brindado.
			{
				retorno = i;//Devuelve el indice donde se encuentra el ID brindado.
				break;
			}
		}
	}
	return retorno;
}

/**
 * \brief Pone en estado "PAUSADA" una publicacion.
 * \param pArray Puntero al array de publicaciones.
 * \param len Es la longitud del array.
 * \param indice Posicion del array a pausar.
 * \return Retorna 0 si pausó la publicacion correctamente y -1 si tuvo algún error.
 *
 */
int pub_pausarArray(Publicacion* pArray,int len, int indice)
{
	int retorno = -1;
	if( pArray != NULL &&
		len > 0 &&
		indice > -1 &&
		pArray[indice].isEmpty == 0 &&
		pArray[indice].estado == 1)//Valida que los datos de la funcion sean correctos. Y que el indice brindado, esté cargado y activo.
	{
		pArray[indice].estado = 0;//Cambia el estado a "pausado".
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief Pone en estado "Activa" nuevamente una publicacion.
 * \param pArray Puntero al array de publicaciones.
 * \param len Es la longitud del array.
 * \param indice Posicion del array a reanudar.
 * \return Retorna 0 si reanudó la publicacion correctamente y -1 si tuvo algún error.
 *
 */
int pub_reanudarArray(Publicacion* pArray,int len, int indice)
{
	int retorno = -1;
	if( pArray != NULL &&
		len > 0 &&
		indice > -1 &&
		pArray[indice].isEmpty == 0 &&
		pArray[indice].estado == 0)//Valida que los datos de la funcion sean correctos. Y que el indice brindado, esté cargado y pausado.
	{
		pArray[indice].estado = 1;//Cambia el estado a "Activo".
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief Cuenta las publicaciones que tiene por ID de Cliente.
 * \param idCli Identificacion del cliente a buscar.
 * \param pArray Puntero al array de publicaciones.
 * \param len Es la longitud del array de publicaciones.
 * \return Retorna 0 si encontró al menos 1 aviso y -1 si tuvo algún error o si no encontró avisos.
 *
 */
int pub_contAvisos(Publicacion* pArray, int len, int idCli)
{
	int retorno = -1;
	int i;
	int contAvisos=0;

	if(pArray != NULL && len > 0 && idCli > -1 )//Valida que los datos de la funcion sean correctos.
	{
		for(i=0;i<len;i++)
		{
			if(	pArray[i].isEmpty == 0 &&
				pArray[i].idCliente == idCli)//Valida que este "cargado el indice y que se encuentre el ID brindado.
			{
				contAvisos++;//Incrementa el contador de avisos.
			}
		}
		retorno = contAvisos;//Retorna la cantidad de numeros de avisos encontrados.
	}
	return retorno;
}

/**
 * \brief Cuenta las publicaciones ACTIVAS que tiene por ID de Cliente.
 * \param idCli Identificacion del cliente a buscar.
 * \param pArray Puntero al array de publicaciones.
 * \param len Es la longitud del array de publicaciones.
 * \return Retorna 0 si encontró al menos 1 aviso y -1 si tuvo algún error o si no encontró avisos.
 *
 */
int pub_contAviAct(Publicacion* pArray, int len, int idCli)
{
	int retorno = -1;
	int i;
	int contAviAct=0;

	if(pArray != NULL && len > 0 && idCli > -1 )//Valida que los datos de la funcion sean correctos.
	{
		for(i=0;i<len;i++)
		{
			if( pArray[i].estado == 1 &&
				pArray[i].isEmpty == 0 &&
				pArray[i].idCliente == idCli)//Valida que este "cargado" y "activo" el indice y que se encuentre el ID brindado.
			{
				contAviAct++;//Incrementa el contador de avisos activos.
			}
		}
		retorno = contAviAct;//Retorna la cantidad de numeros de avisos activos encontrados.
	}
	return retorno;
}

/**
 * \brief Cuenta las publicaciones PAUSADAS que tiene por ID de Cliente.
 * \param idCli Identificacion del cliente a buscar.
 * \param pArray Puntero al array de publicaciones.
 * \param len Es la longitud del array de publicaciones.
 * \return Retorna 0 si encontró al menos 1 aviso y -1 si tuvo algún error o si no encontró avisos.
 *
 */
int pub_contAviPau(Publicacion* pArray, int len, int idCli)
{
	int retorno = -1;
	int i;
	int contAviPau=0;

	if(pArray != NULL && len > 0 && idCli > -1 )
	{
		for(i=0;i<len;i++)
		{
			if( pArray[i].estado == 0 &&
				pArray[i].isEmpty == 0 &&
				pArray[i].idCliente == idCli)//Valida que este "cargado" y "pausado" el indice y que se encuentre el ID brindado.
			{
				contAviPau++;//Incrementa el contador de avisos pausados.
			}
		}
		retorno = contAviPau;//Retorna la cantidad de numeros de avisos pausados encontrados.
	}
	return retorno;
}

/**
 * \ALTA FORZADA de una publicacion en una posicion del array.
 * \param pArray Puntero al array de publicaciones.
 * \param len Es la longitud del array.
 * \param indice Posicion del array a modificar.
 * \param idPub Identificador unico asignado a la publicacion.
 * \param idCli Identificador unico asignado al cliente.
 * \param numRubro Numero de rubro asignado a la publicacion.
 * \param aviso Descripcion de la publicacion.
 * \return Retorna 0 si lo dió de alta correctamente y -1 si tuvo algun error.
 *
 */
int pub_altaForzadaArray(Publicacion* pArray,int len, int indice, int* idPub, int idCli, int numRubro , char* aviso)

{
	int retorno = -1;
	Publicacion auxiliar;

	if(pArray != NULL && len > 0 && indice < len && indice > -1 && idPub != NULL)//Valida que los datos de la funcion sean correctos.
	{
		retorno = 0;
		strncpy(auxiliar.textAviso,aviso,AVISO_LEN);
		auxiliar.idCliente = idCli;
		auxiliar.numRubro = numRubro;
		auxiliar.idPublicacion = *idPub;
		auxiliar.isEmpty = 0;
		auxiliar.estado = 1;
		pArray[indice] = auxiliar; //COPIA TODOS LOS DATOS ASIGNADOS.
		(*idPub)++;
	}
	return retorno;
}


