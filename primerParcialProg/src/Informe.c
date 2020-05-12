/*
 * Informe.c
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

static const char ESTADO_TIPOS[2][8]={"PAUSADA","ACTIVA"};

static int info_imprimirAvisosActivosCliente(Cliente* pArray, int len, int idCliBuscado, int cantAvisos);
static int info_imprimirAvisosPausadosCliente(Cliente* pArray, int len, int idCliBuscado, int cantAvisos);
static int info_imprimirAvisosCliente(Cliente* pArray, int len, int idCliBuscado, int cantAvisos);
static int info_contPubliByRubro(Publicacion* pArrayPub, int lenPub, int rubro);

/**
 * \brief Imprime los clientes dados de alta, con la cantidad de publicaciones activas.
 * \param pArrayCli Puntero al array de clientes.
 * \param lenCli Es la longitud del array de clientes.
 * \param pArrayPub Puntero al array de publicaciones.
 * \param lenPub Es la longitud del array de publicaciones.
 * \return \return Retorna 0 si imprimió correctamente y -1 si tuvo algún error.
 *
 */
int info_imprimirArrayCantPubAct(Cliente* pArrayCli ,int lenCli, Publicacion* pArrayPub, int lenPub)
{
	int retorno = -1;
	int i;
	int contadorAvi;

	if(pArrayCli != NULL && lenCli > 0 && pArrayPub != NULL && lenPub > 0)//Valida que los datos de la funcion sean correctos.
	{
		retorno=0;
		for(i=0;i<lenCli;i++)
		{
			if( pArrayCli[i].isEmpty == 0 )//Valida que el indice este "cargado".
			{
					contadorAvi = pub_contAviAct(pArrayPub,lenPub,pArrayCli[i].idCliente > -1);//Contador de avisos activos.
				{
					printf("\nID Cliente: %d - Nombre: %s - Apellido: %s - Cuit: %s - Cantidad Avisos Activos: %d.",pArrayCli[i].idCliente,pArrayCli[i].nombre,pArrayCli[i].apellido,pArrayCli[i].cuit,contadorAvi);
				}
			}
		}
	}
	return retorno;
}

/**
 * \brief Imprime las publicaciones "cargadas" con el CUIT del cliente.
 * \param pArrayCli Puntero al array de clientes.
 * \param lenCli Es la longitud del array de clientes.
 * \param pArrayPub Puntero al array de publicaciones.
 * \param lenPub Es la longitud del array de publicaciones.
 * \return \return Retorna 0 si imprimió correctamente y -1 si tuvo algún error.
 *
 */
int info_imprimirArrayByEstado(Publicacion* pArrayPub, int lenPub, Cliente* pArrayCli, int lenCli)
{
	int retorno = -1;
	int i;
	int j;
	char cuitCliente[CUIT_LEN];

	if(pArrayPub != NULL && lenPub > 0 && pArrayCli != NULL && lenCli > 0)//Valida que los datos de la funcion sean correctos.
	{
		for(i=0;i<lenPub;i++)//Recorre el array de publicaciones.
		{
			if(pArrayPub[i].isEmpty == 0)//Entra en IF se encuentra un indice "cargado".
			{
				for(j=0;j<lenCli;j++)//Recorre el array de clientes.
				{
					if(pArrayPub[i].idCliente == pArrayCli[j].idCliente)//Si el ID del cliente del indice "cargado" es igual al del array de la publicacion, entra al IF.
					{
						retorno = 0;
						strncpy(cuitCliente,pArrayCli[j].cuit,CUIT_LEN);//Copia el cuit del ID de cliente buscado en cuitCliente.
						printf("\nID Cliente: %d - CUIT: %s - ID Publicacion: %d - Rubro: %d - Texto del aviso: %s - Estado: %s.",pArrayPub[i].idCliente,pArrayCli[j].cuit,pArrayPub[i].idPublicacion,pArrayPub[i].numRubro,pArrayPub[i].textAviso,ESTADO_TIPOS[pArrayPub[i].estado]);
						break;
					}
				}
			}
		}
	}
	return retorno;
}

/**
 * \brief Calcula la cantidad e imprime publicaciones, segun un criterio de estado.
 * \param pArrayCli Puntero al array de clientes.
 * \param lenCli Es la longitud del array de clientes.
 * \param pArrayPub Puntero al array de publicaciones.
 * \param lenPub Es la longitud del array de publicaciones.
 * \param estado Es el estado de los avisos que se desean imrprimir. 1 = SOLO ACTIVOS; 2 = SOLO PAUSADOS; 3 = GENERAL.
 * \return Retorna 0 si la funcion se ejecutó correctamente y -1 si tuvo algún error.
 *
 */
int info_calcularEImprmirAvisosCliente(Cliente* pArrayCli, int lenCli, Publicacion* pArrayPub, int lenPub, int estado)
{
	int retorno = -1;
	int i;
	int cantAvisosByCli;
	int idCliAvisos;
	int cantidadAvisos;
	int flag=0;

	if(pArrayCli != NULL && lenCli > 0 && pArrayPub != NULL && lenPub )//Valida que los datos de la funcion sean correctos.
	{
		switch(estado)//Valida lo que se desea calcular e imprimir. 1 = SOLO ACTIVOS; 2 = SOLO PAUSADOS; 3 = GENERAL.
		{
			case 1:

				for(i=0;i<lenCli;i++)//Recorre el array de clientes.
				{
					if( pArrayCli[i].isEmpty == 0 )//Valida que el indice este "cargado".
					{
						cantAvisosByCli = pub_contAviAct(pArrayPub,lenPub,pArrayCli[i].idCliente);//Contador de avisos activos.
						if( flag == 0 || cantAvisosByCli > cantidadAvisos)//Busca el Cliente con mas avisos activos.
						{
							flag = 1;
							idCliAvisos = pArrayCli[i].idCliente;
							cantidadAvisos = cantAvisosByCli;
						}
						retorno=0;
					}
				}
				if( cantidadAvisos >0 &&
					!info_imprimirAvisosActivosCliente(pArrayCli,lenCli,idCliAvisos,cantidadAvisos))//Imprime el cliente con mas avisos activos.
				{
					printf("\nBusqueda exitosa!.");
				}
				else
				{
					printf("\nNo existen usuarios con publicaciones en estado Activo.");
				}
				break;

			case 2:

				for(i=0;i<lenCli;i++)//Recorre el array de clientes.
				{
					if( pArrayCli[i].isEmpty == 0 )//Valida que el indice este "cargado".
					{
						cantAvisosByCli = pub_contAviPau(pArrayPub,lenPub,pArrayCli[i].idCliente);//Contador de avisos pausados.
						if( flag == 0 || cantAvisosByCli > cantidadAvisos)//Busca el Cliente con mas avisos pausados.
						{
							flag = 1;
							idCliAvisos = pArrayCli[i].idCliente;
							cantidadAvisos = cantAvisosByCli;
						}
						retorno=0;
					}
				}
				if( cantidadAvisos >0 &&
					!info_imprimirAvisosPausadosCliente(pArrayCli,lenCli,idCliAvisos,cantidadAvisos))//Imprime el cliente con mas avisos pausados.
				{
					printf("\nBusqueda exitosa!.");
				}
				else
				{
					printf("\nNo existen usuarios con publicaciones en estado Pausada.");
				}
				break;

			case 3:

				for(i=0;i<lenCli;i++)//Recorre el array de clientes.
				{
					if( pArrayCli[i].isEmpty == 0 )//Valida que el indice este "cargado".
					{
						cantAvisosByCli = pub_contAvisos(pArrayPub,lenPub,pArrayCli[i].idCliente);//Contador de avisos generales.
						if( flag == 0 || cantAvisosByCli > cantidadAvisos)//Busca el Cliente con mas avisos generales.
						{
							flag = 1;
							idCliAvisos = pArrayCli[i].idCliente;
							cantidadAvisos = cantAvisosByCli;
						}
						retorno=0;
					}
				}
				if( cantidadAvisos >0 &&
					!info_imprimirAvisosCliente(pArrayCli,lenCli,idCliAvisos,cantidadAvisos))//Imprime el cliente con mas avisos generales.
				{
					printf("\nBusqueda exitosa!.");
				}
				else
				{
					printf("\nNo existen usuarios con publicaciones.");
				}
				break;
		}
	}
	return retorno;
}


/**
 * \brief Imprime los datos del Cliente con mas avisos activos.
 * \param pArray Puntero al array de clientes.
 * \param len Es la longitud del array.
 * \param idCliBuscado Es el ID del cliente a imprimir publicaciones.
 * \param cantAvisos Numero de avisos a imprimir.
 * \return \return Retorna 0 si imprimió correctamente y -1 si tuvo algún error.
 *
 */
static int info_imprimirAvisosActivosCliente(Cliente* pArray, int len, int idCliBuscado, int cantAvisos)
{
	int retorno = -1;
	int i;
	if(pArray != NULL && len > 0 && idCliBuscado > -1)//Valida que los datos de la funcion sean correctos.
	{
		for(i=0;i<len;i++)
		{
			if( pArray[i].isEmpty == 0 &&
				pArray[i].idCliente == idCliBuscado )//Valida que el indice este "cargado" y que encuentra el id buscado.
			{
				retorno = 0;
				printf("\nEl cliente con mas cantidad de avisos activos (%d) es: %s, %s - Cuit: %s.",cantAvisos,pArray[i].apellido,pArray[i].nombre,pArray[i].cuit);
			}
		}
	}
	return retorno;
}

/**
 * \brief Imprime los datos del Cliente con mas avisos pausados.
 * \param pArray Puntero al array de clientes.
 * \param len Es la longitud del array.
 * \param idCliBuscado Es el ID del cliente a imprimir publicaciones.
 * \param cantAvisos Numero de avisos a imprimir.
 * \return \return Retorna 0 si imprimió correctamente y -1 si tuvo algún error.
 *
 */
static int info_imprimirAvisosPausadosCliente(Cliente* pArray, int len, int idCliBuscado, int cantAvisos)
{
	int retorno = -1;
	int i;
	if(pArray != NULL && len > 0 && idCliBuscado > -1)//Valida que los datos de la funcion sean correctos.
	{
		for(i=0;i<len;i++)
		{
			if( pArray[i].isEmpty == 0 &&
				pArray[i].idCliente == idCliBuscado )//Valida que el indice este "cargado" y que encuentra el id buscado.
			{
				retorno = 0;
				printf("\nEl cliente con mas cantidad de avisos pausados (%d) es: %s, %s - Cuit: %s.",cantAvisos,pArray[i].apellido,pArray[i].nombre,pArray[i].cuit);
			}
		}
	}
	return retorno;
}

/**
 * \brief Imprime los datos del Cliente con mas avisos generales.
 * \param pArray Puntero al array de clientes.
 * \param len Es la longitud del array.
 * \param idCliBuscado Es el ID del cliente a imprimir publicaciones.
 * \param cantAvisos Numero de avisos a imprimir.
 * \return \return Retorna 0 si imprimió correctamente y -1 si tuvo algún error.
 *
 */
static int info_imprimirAvisosCliente(Cliente* pArray, int len, int idCliBuscado, int cantAvisos)
{
	int retorno = -1;
	int i;
	if(pArray != NULL && len > 0 && idCliBuscado > -1)//Valida que los datos de la funcion sean correctos.
	{
		for(i=0;i<len;i++)
		{
			if( pArray[i].isEmpty == 0 &&
				pArray[i].idCliente == idCliBuscado )//Valida que el indice este "cargado" y que encuentra el id buscado.
			{
				retorno = 0;
				printf("\nEl cliente con mas cantidad de avisos (%d) es: %s, %s - Cuit: %s.",cantAvisos,pArray[i].apellido,pArray[i].nombre,pArray[i].cuit);
			}
		}
	}
	return retorno;
}


/**
 * \brief Imprime la cantidad de publicaciones maximas o minimas de un rubro.
 * \param pArray Puntero al array de publicaciones.
 * \param len Es la longitud del array.
 * \param MaxiOrMin Es el sentido de la busqueda. Si = 1 se busca el maximo, si = 0 se busca el minimo.
 * \return \return Retorna 0 si imprimió correctamente y -1 si tuvo algún error.
 *
 */
int info_imprimirMaximosMinimosPubByRubros(Publicacion* pArray, int len, int MaxiOrMin)
{
	int retorno = -1;
	int i;
	int j;
	int listaRubros[len];
	int flagRubro;
	int flagMaximoRubro = 0;
	int cantiPub;
	int maxCantPubByRubro;
	int numeroRubro;
	int indiceRubroLibre = 0;

	for(i=0;i<len;i++)
	{
		flagRubro = 0;
		if(pArray[i].isEmpty == 0)//Valida que el indice este "cargado".
		{
			for(j=0;j<indiceRubroLibre;j++)
			{
				if(pArray[i].numRubro == listaRubros[j])//Busca el indice encontrado "cargado" en la listaRubros. Si lo encuentra, entra al IF.
				{
					flagRubro = 1;
					break;
				}
			}

			if( flagRubro == 0 &&
				MaxiOrMin == 1)//Si no encuentra el rubro cargado y el objetivo es buscar el maximo, entra al IF.
			{
				listaRubros[indiceRubroLibre] = pArray[i].numRubro;//copia el rubro del array publicaciones a la listaRubros.
				cantiPub = info_contPubliByRubro(pArray,len,listaRubros[indiceRubroLibre]);//Calcula la cantidad de publicaciones activas de un rubro.
				if(flagMaximoRubro == 0 || cantiPub > maxCantPubByRubro)//Determina la maxima cantidad de rubros con publicaciones activas.
				{
					flagMaximoRubro = 1;
					numeroRubro = listaRubros[indiceRubroLibre];
					maxCantPubByRubro = cantiPub;
				}
				indiceRubroLibre++;//Incrementa el rubro.
			}
			if( flagRubro == 0 &&
				MaxiOrMin == 0)//Si no encuentra el rubro cargado y el objetivo es buscar el minimo, entra al IF.
			{
				listaRubros[indiceRubroLibre] = pArray[i].numRubro;//copia el rubro del array publicaciones a la listaRubros.
				cantiPub = info_contPubliByRubro(pArray,len,listaRubros[indiceRubroLibre]);//Calcula la cantidad de publicaciones activas de un rubro.
				if(flagMaximoRubro == 0 || cantiPub < maxCantPubByRubro)//Determina la minima cantidad de rubros con publicaciones activas.
				{
					flagMaximoRubro = 1;
					numeroRubro = listaRubros[indiceRubroLibre];
					maxCantPubByRubro = cantiPub;
				}
				indiceRubroLibre++;//Incrementa el rubro.
			}
		}
	}
	printf("\n\nEl rubro '%d' posee %d publicaciones activas.\n\n",numeroRubro,maxCantPubByRubro);
	return retorno;
}

/**
 * \brief Imprime la cantidad de publicaciones activas de rubro especifico.
 * \param pArray Puntero al array de publicaciones.
 * \param len Es la longitud del array.
 * \param rubro Es el rubro a calcular la cantidad de publicaciones.
 * \return \return Retorna 0 si imprimió correctamente y -1 si tuvo algún error.
 *
 */
int info_imprimirPubActivasByRubro(Publicacion* pArray, int len, int rubro)
{
	int retorno = -1;
	int cantiPub;

	if(pArray != NULL && len >0 && rubro >-1)//Valida que los datos de la funcion sean correctos.
	{
		cantiPub = info_contPubliByRubro(pArray,len,rubro);//Calcula las publicaciones.
		retorno = 0;
		printf("El rubro '%d', posee %d publicaciones activas.",rubro,cantiPub);
	}
	return retorno;
}

/**
 * \brief Busca si el rubro existe en el array publicaciones.
 * \param pArray Puntero al array de publicaciones.
 * \param len Es la longitud del array.
 * \param rubro Es el rubro a buscar.
 * \return \return Retorna 0 si lo encontró correctamente y -1 si tuvo algún error o si no lo encontró.
 *
 */
int info_buscarRubro(Publicacion* pArray, int len, int rubro)
{
	int retorno = -1;
	int i;

	if(pArray != NULL && len > 0 && rubro > -1 )//Valida que los datos de la funcion sean correctos.
	{
		for(i=0;i<len;i++)
		{
			if( pArray[i].isEmpty == 0 &&
				pArray[i].numRubro == rubro	)//Valida que el indice este "cargado" y encontrar el numero de rubro.
			{
				retorno = rubro;//Retorna el numero de rubro.
				break;
			}
		}
	}
	return retorno;
}

/**
 * \brief Cuenta la cantidad de publicaciones activas que tiene un rubro.
 * \param pArrayPub Puntero al array de publicaciones.
 * \param lenPub Es la longitud del array de publicaciones.
 * \param rubro Es el rubro a buscar.
 * \return Retorna la cantidad de publicaciones activas encontradas.
 *
 */
static int info_contPubliByRubro(Publicacion* pArrayPub, int lenPub, int rubro)
{
	int retorno = -1;
	int i;
	int contRubro=0;

	if(pArrayPub != NULL && lenPub > 0 && rubro > -1 )//Valida que los datos de la funcion sean correctos.
	{
		for(i=0;i<lenPub;i++)//Recorre el array de publicaciones.
		{
			if( pArrayPub[i].isEmpty == 0 &&
				pArrayPub[i].estado == 1 &&
				pArrayPub[i].numRubro == rubro)//Valida si el indice esta "cargado", si esta "activo" y si pertenece al rubro buscado.
			{
				contRubro++;//Incrementa la cantidad de publicaciones activas.
			}
		}
		retorno = contRubro;//Devuelve el numero de publicaciones activas.
	}
	return retorno;
}
