/*
 * Cliente.c
 *
 *  Created on: 8 may. 2020
 *      Author: VOPKEQUE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "Cliente.h"
#include "Publicacion.h"
#include "Informe.h"

/**
 * \brief Inicializa el array Clientes.
 * \param pArray Array de clientes a actualizar.
 * \param len Limite del array de cliente.
 * \return Retorna 0 si inicializó el array correctamente y -1 si tuvo algún error.
 *
 */
int cli_initializeArray(Cliente* pArray, int len)
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
 * \brief Da de alta un cliente en una posicion del array.
 * \param pArray Puntero al array de clientes a actualizar.
 * \param len Es la longitud del array.
 * \param indice Posicion a ser actualizada/cargada.
 * \param id Identificador unico asignado al cliente.
 * \return Retorna 0 si dió de alta al cliente correctamente y -1 si tuvo algún error.
 *
 */
int cli_altaArray(Cliente* pArray, int len, int indice, int* id)
{
	int retorno = -1;
	Cliente auxiliar;

	if(pArray != NULL && len > 0 && indice < len && id != NULL)//Valida que los datos de la funcion sean correctos.
	{
		if( !utn_getNameOrSurname(auxiliar.nombre,NOMBRE_LEN,"Ingrese un nombre: \n","El nombre no es válido.\n",2) &&//Obtiene un nombre.
			!utn_getNameOrSurname(auxiliar.apellido,APELLIDO_LEN,"Ingrese un apellido: \n","El apellido no es válido.\n",2) &&//Obtiene un apellido.
			!utn_getCuit(auxiliar.cuit,CUIT_LEN,"Ingrese un CUIT: \n","El CUIT no es válido.\n",2))//Obtiene un cuit.
		{
			retorno = 0;
			pArray[indice] = auxiliar;
			pArray[indice].isEmpty = 0;
			pArray[indice].idCliente = *id;
			(*id)++;
		}
	}
	return retorno;
}

/**
 * \brief Imprime los datos de un cliente.
 * \param pElemento Puntero al producto que se busca imprimir.
 * \return Retorna 0 imprimió con exito y -1 si se produjo algun error.
 *
 */
int cli_imprimir(Cliente* pCliente)
{
	int retorno=-1;
	if(pCliente != NULL && pCliente->isEmpty == 0)//Valida que los datos de la funcion sean correctos. y que se encuentre "cargado".
	{
		retorno=0;
		printf("\nID Cliente: %d - Nombre: %s - Apellido: %s - Cuit: %s",pCliente->idCliente,pCliente->nombre,pCliente->apellido,pCliente->cuit);
	}
	return retorno;
}

/**
 * \brief Imprime el array de clientes.
 * \param pArray Puntero al array de clientes.
 * \param len Es la longitud del array.
 * \return \return Retorna 0 si imprimió correctamente y -1 si tuvo algún error.
 *
 */
int cli_imprimirArray(Cliente* pArray,int len)
{
	int retorno = -1;
	int i;
	if(pArray != NULL && len > 0)//Valida que los datos de la funcion sean correctos.
	{
		retorno = 0;
		for(i=0;i<len;i++)
		{
			if(pArray[i].isEmpty == 0)//Valida que este "cargado" para imprimir.
			{
				printf("\nID Cliente: %d - Nombre: %s - Apellido: %s - Cuit: %s.",pArray[i].idCliente,pArray[i].nombre,pArray[i].apellido,pArray[i].cuit);
			}
		}
	}
	return retorno;
}

/**
 * \brief Imprime la informacion de un cliente por ID.
 * \param pArray Puntero al array de clientes.
 * \param len Es la longitud del array.
 * \param idCliBuscado Es el ID del cliente a encontrar.
 * \return \return Retorna 0 si imprimió correctamente y -1 si tuvo algún error.
 *
 */
int cli_imprimirClienteByIdPub(Cliente* pArrayCli, int lenCli, int idPubBuscado, Publicacion* pArrayPub, int lenPub)
{
	int retorno = -1;
	int i;
	int j;

	if(pArrayCli != NULL && lenCli > 0 && idPubBuscado > -1 && pArrayPub != NULL && lenPub > 0)//Valida que los datos de la funcion sean correctos.
	{
		for(i=0;i<lenPub;i++)
		{
			if( pArrayPub[i].idPublicacion == idPubBuscado &&
				pArrayPub[i].isEmpty == 0 )
			{
				for(j=0;j<lenCli;j++)
				{
					if( pArrayPub[i].idCliente == pArrayCli[j].idCliente &&
						pArrayCli[j].isEmpty == 0)
					{
						retorno = 0;
						printf("\nID Cliente: %d - Nombre: %s - Apellido: %s - Cuit: %s.",pArrayCli[j].idCliente,pArrayCli[j].nombre,pArrayCli[j].apellido,pArrayCli[j].cuit);
						break;
					}
				}
			}
		}
	}
	return retorno;
}

/**
 * \brief Buscar la primer posición vacia en el array de clientes.
 * \param pArray Puntero al array de clientes.
 * \param len Es la longitud del array.
 * \return Retorna el indice de la posicion vacia si encontró un indice vacio y -1 si obtuvo algún error o no existen indices vacios.
 *
 */
int cli_getEmptyIndex(Cliente* pArray, int len)
{
	int retorno = -1;
	int i;
	if(pArray != NULL && len > 0)//Valida que los datos de la funcion sean correctos.
	{
		for(i=0;i<len;i++)
		{
			if(pArray[i].isEmpty == 1)//Valida que el indice se encuentre "vacio".
			{
				retorno = i;//Retorna el valor del indice.
				break;
			}
		}
	}
	return retorno;
}

/**
 * \brief Modifica los datos ingresados de un cliente por ID.
 * \param pArray Puntero al array de clientes.
 * \param len Es la longitud del array.
 * \param id Identificacion del cliente a modificar.
 * \return Retorna 0 si modifico los datos del cliente correctamente y -1 si tuvo algún error.
 *
 */
int cli_modificarArray(Cliente* pArray,int len, int id)
{
	int retorno = -1;
	int i;
	Cliente auxiliar;

	if(pArray != NULL && len > 0 && id > -1)//Valida que los datos de la funcion sean correctos.
	{
		for(i=0;i<len;i++)
		{
			if(pArray[i].idCliente == id)//Busca el id brindado en los indices del array clientes.
			{
				auxiliar = pArray[i];
				if( !utn_getNameOrSurname(auxiliar.nombre,NOMBRE_LEN,"Ingrese un nombre: \n","El nombre no es válido.\n",2) &&//Obtiene un nombre.
					!utn_getNameOrSurname(auxiliar.apellido,APELLIDO_LEN,"Ingrese un apellido: \n","El apellido no es válido.\n",2) &&//Obtiene un apellido.
					!utn_getCuit(auxiliar.cuit,CUIT_LEN,"Ingrese un CUIT: \n","El CUIT no es válido.\n",2))//Obtiene un cuit.
				{
					retorno = 0;
					pArray[i] = auxiliar;//copia el valor de auxiliar en el indice del array cliente.
					break;
				}
			}
		}
	}
	return retorno;
}


/**
 * \brief Busca un ID de un cliente y devuelve la posicion en la que se encuentra.
 * \param pArray Puntero al array de clientes.
 * \param len Es la longitud del array.
 * \param idBuscado Id a buscar en el array de clientes.
 * \return Retorna el indice de la posicion buscada en caso de existir y -1 si obtuvo algún error o no existe el indice buscado.
 *
 */
int cli_buscarId(Cliente* pArray, int len, int idBuscado)
{
	int retorno = -1;
	int i;
	if(pArray != NULL && len > 0 && idBuscado > -1)//Valida que los datos de la funcion sean correctos.
	{
		for(i=0;i<len;i++)
		{
			if( pArray[i].isEmpty == 0 &&
				pArray[i].idCliente == idBuscado)//Valida que este "cargado" el indice y que se encuentre el ID brindado.
			{
				retorno = i;//Retorna el indice encontrado.
				break;
			}
		}
	}
	return retorno;
}

/**
 * \brief Da de baja los datos ingresados de un cliente como asi tambien sus publicaciones.
 * \param pArrayCli Puntero al array de clientes.
 * \param lenCli Es la longitud del array de clientes.
 * \param id Identificacion del cliente a dar de baja.
 * \param pArrayPub Puntero al array de publicaciones.
 * \param lenPub Es la longitud del array de publicaciones.
 * \return Retorna 0 si dió de baja a un cliente correctamente y -1 si tuvo algún error.
 *
 */
int cli_bajaArray(Cliente* pArrayCli,int lenCli, int id,Publicacion* pArrayPub, int lenPub)
{
	int retorno = -1;
	int i;
	int j;

	if(pArrayCli != NULL && lenCli > 0 && id > -1 && pArrayPub != NULL && lenPub > 0)//Valida que los datos de la funcion sean correctos.
	{
		for(i=0;i<lenCli;i++)
		{
			if(pArrayCli[i].idCliente == id)//Busca el ID del cliente en el array clientes.
			{
				retorno = 0;
				pArrayCli[i].isEmpty = 1;//Cuando lo encuentra, le cambia el estado a "vacio".
				for(j=0;j<lenPub;j++)
				{
					if(pArrayPub[j].idCliente == id)//Busca el ID del cliente en el array publicaciones.
					{
						pArrayPub[j].isEmpty = 1;//Cuando los encuentra, le cambia el estado a "vacio".
					}
				}
				break;
			}
		}
	}
	return retorno;
}

/**
 * \ALTA FORZADA de un cliente en una posicion del array.
 * \param pArray Puntero al array de clientes.
 * \param len Es la longitud del array.
 * \param indice Posicion del array a modificar.
 * \param id Identificador unico asignado al cliente.
 * \param nombre Nombre del cliente.
 * \param apellido Apellido del cliente.
 * \param Cuit Apellido del cliente.
 * \return Retorna 0 si lo dió de alta correctamente y -1 si tuvo algun error.
 *
 */
int cli_altaForzadaArray(Cliente* pArray,int len, int indice, int* id,char* nombre,char* apellido,char* cuit)

{
	int retorno = -1;
	Cliente auxiliar;

	if(pArray != NULL && len > 0 && indice < len && indice > -1 && id != NULL)//Valida que los datos de la funcion sean correctos.
	{
		retorno = 0;
		strncpy(auxiliar.nombre,nombre,NOMBRE_LEN);
		strncpy(auxiliar.apellido,apellido,APELLIDO_LEN);
		strncpy(auxiliar.cuit,cuit,CUIT_LEN);
		auxiliar.idCliente = *id;
		auxiliar.isEmpty = 0;
		pArray[indice] = auxiliar;//COPIA TODOS LOS DATOS ASIGNADOS.
		(*id)++;
	}
	return retorno;
}
