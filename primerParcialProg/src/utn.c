/*
 * utn.c
 *
 *  Created on: 8 may. 2020
 *      Author: VOPKEQUE
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int getDescription(char* cadena, int len);
static int getInt(int* pResultado);
static int getCuit(char* cadena, int len);
static int getNameOrSurname(char* cadena, int len);
static int getString(char* cadena, int len);
static int isNameOrSurname(char* cadena, int len);
static int isCuit(char* cadena,int len);
static int isNumeric(char* cadena, int len);
static int isDescription(char* cadena, int len);


/**
 * \brief Solicita un nombre o apellido al usuario, luego de su verificación devuelve el resultado.
 * \param pResultado Puntero al espacio de memoria, donde se alojará el resultado de la función.
 * \param len Es la longitud del array resultado.
 * \param mensaje Mensaje a mostrar al usuario para el ingreso del nombre o apellido.
 * \param mensajeError Mensaje de error, en caso de que el nombre o apellido ingresado por el usuario sea erróneo.
 * \param reintentos Cantidad de reintentos.
 * \return Retorna 0 si obtuvo el nombre o apellido y -1 si tuvo algún error.
 *
 */
int utn_getNameOrSurname(char* pResultado, int len, char* mensaje, char* mensajeError, int reintentos)
{
	int retorno = -1;
	char bufferString[4096];

	if(pResultado != NULL && len > 0 && mensaje != NULL && mensajeError != NULL && reintentos > -1)//Valida los datos de la funcion.
	{
		do{
			printf("%s", mensaje); //Mensaje a mostrar al usuario.
			if( !getNameOrSurname(bufferString,sizeof(bufferString))) //Si la funcion getNameorSurname obtiene un string valido como nombre, lo copia en buffer String
			{
				retorno = 0;
				strncpy(pResultado,bufferString,len);//Copia el resultado de la funcion getNameorSurname en el puntero de resultado.
				break;
			}
			else
			{
				printf("%s", mensajeError);//Mensaje a mostrar, si no obtiene un string valido como nombre o apellido.
				reintentos--; //Disminuye la cantidad de reintentos.
			}
		}while(reintentos>=0);
	}
	return retorno;
}

/**
 * \brief Obtiene una cadena válida como nombre o apellido.
 * \param pResultado Puntero al espacio de memoria, donde se alojará el resultado de la función.
 * \param len Define el tamaño de la cadena.
 * \return Retorna 0 si obtuvo el nombre o apellido y -1 si tuvo algun error.
 *
 */
static int getNameOrSurname(char* cadena, int len)
{
    int retorno=-1;
    char bufferString[4096];

    if( cadena != NULL && //Valida que el puntero sea valido.
    	len > 0 && //Valida que el tamañano de cadena sea razonable.
    	!getString(bufferString,sizeof(bufferString)) && //Obtiene una cadena de stdin valida como String.
		isNameOrSurname(bufferString,sizeof(bufferString)) && //valida que bufferString sea valido como nombre o apellido.
		strnlen(bufferString,sizeof(bufferString)) < len)//Valida que el tamaño de bufferString sea menor que la longitud de cadena.
    	{
    		strncpy(cadena,bufferString,len); //Si cumple las validaciones, copia la informacion de bufferString en cadena.
			retorno = 0;
		}
    return retorno;
}
/**
 * \brief 	Lee de stdin hasta que encuentra un '\n' o hasta que haya copiado en cadena
 * 			un máximo de 'len - 1' caracteres.
 * \param pResultado Puntero al espacio de memoria donde se copiara la cadena obtenida.
 * \param len Define el tamaño de la cadena.
 * \return Retorna 0 si se obtiene una cadena y -1 si tuvo algún error.
 *
 */
static int getString(char* cadena, int len)
{
	int retorno = -1;
	char bufferString[4096];

	if(cadena != NULL && len > 0) //Valida que el puntero sea valido y que el tamañano de cadena sea razonable.
	{
		fflush(stdin);//"Limpia" de datos basura a stdin.
		if(fgets(bufferString,sizeof(bufferString),stdin) != NULL)//Obtiene la informacion de stdin.
		{
			if(bufferString[strnlen(bufferString,sizeof(bufferString))-1] == '\n')//Si la anteultima posicion de bufferString es '\n' entra al IF.
			{
				bufferString[strnlen(bufferString,sizeof(bufferString))-1] = '\0';//Cambia a \n por \0.
			}
			if(strnlen(bufferString,sizeof(bufferString)) <= len)//Si el tamaño de bufferString es menor o mayor a la longitud de cadena entra al IF.
			{
				strncpy(cadena,bufferString,len); //Si cumple las validaciones, copia la informacion de bufferString en cadena.
				retorno = 0;
			}
		}
	}
	return retorno;
}

/**
 * \brief Verifica si la cadena ingresada es un nombre o apellido válido.
 * \param cadena Cadena de caracteres a analizar.
 * \param \param len Define el tamaño de la cadena.
 * \return Retorna 1 si la cadena es válida y 0 si no lo es.
 *
 */
static int isNameOrSurname(char* cadena, int len)
{
	int i=0;
	int retorno = 1;

	if(cadena != NULL && len > 0)//Valida que el puntero sea valido y que el tamañano de cadena sea razonable.
	{
		for(i=0 ; cadena[i] != '\0' && i < len; i++)//Itera 'i' hasta mientras sea distinta de '\0' y respetando el tamaño del array.
		{
			if((cadena[i] < 'A' || cadena[i] > 'Z' ) && (cadena[i] < 'a' || cadena[i] > 'z' ))//Valida que cadena sea solo letras(Mayus y Minus).
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/**
 * \brief Solicita un CUIT al usuario, luego de su verificación devuelve el resultado.
 * \param pResultado Puntero al espacio de memoria, donde se alojará el resultado de la función.
 * \param len Es la longitud del array resultado.
 * \param mensaje mensaje Mensaje a mostrar al usuario para el ingreso del CUIT.
 * \param mensajeError Mensaje de error, en caso de que el CUIT ingresado por el usuario sea erróneo.
 * \param reintentos Cantidad de reintentos.
 * \return Retorna 0 si obtuvo el nombre o apellido y -1 si tuvo algún error.
 *
 */
int utn_getCuit(char* pResultado, int len, char* mensaje, char* mensajeError, int reintentos)
{
	int retorno = -1;
	char bufferString[4096];

	if(pResultado != NULL && len > 0 && mensaje != NULL && mensajeError != NULL && reintentos > -1)//Valida los datos de la funcion.
	{
		do
		{
			printf("%s",mensaje);
			if( !getCuit(bufferString,sizeof(bufferString)) && //Obtiene una cadena de stdin valida como Cuit.
				strnlen(bufferString,sizeof(bufferString)) < len )//Valida que el tamaño de bufferString sea menor que la longitud de cadena.
			{
				strncpy(pResultado,bufferString,len);//Si cumple las validaciones, copia la informacion de bufferString en el puntero de resultado.
				retorno = 0;
				break;
			}
			else
			{
				printf("%s",mensajeError);//Mensaje a mostrar, si no obtiene un string valido como cuit.
				reintentos--;//Disminuye la cantidad de reintentos.
			}
		}while(reintentos>=0);
	}
	return retorno;
}

/**
 * \brief Obtiene una cadena válida como CUIT.
 * \param pResultado Puntero al espacio de memoria, donde se alojará el resultado de la función.
 * \param len Define el tamaño de la cadena.
 * \return Retorna 0 si obtuvo el CUIT y -1 si tuvo algun error.
 *
 */
static int getCuit(char* cadena, int len)
{
    int retorno = -1;
    char bufferString[4096];

    if(cadena != NULL && len > 0)//Valida que el puntero sea valido y que el tamañano de cadena sea razonable.
    {
    	if(	!getString(bufferString,sizeof(bufferString)) &&//Obtiene una cadena de stdin.
    		isCuit(bufferString,sizeof(bufferString)) &&//Valida que el String sea un cuit.
			strnlen(bufferString,sizeof(bufferString))<len)//Valida que el tamaño de bufferString sea menor que la longitud de cadena.
    	{
    		strncpy(cadena,bufferString,len);//Si cumple las validaciones, copia la informacion de bufferString en cadena.
			retorno = 0;
		}
    }
    return retorno;
}

/**
 * \brief Verifica si la cadena ingresada es un CUIT válido.
 * \param cadena Cadena de caracteres a analizar.
 * \param len Define el tamaño de la cadena.
 * \return Retorna 1 si la cadena es válida y 0 si no lo es.
 *
 */
static int isCuit(char* cadena,int len)
{
	int i=0;
	int retorno = 1;

	if(cadena != NULL && len > 0)//Valida que el puntero sea valido y que el tamañano de cadena sea razonable.
	{
		for(i=0 ; cadena[i] != '\0' && i < len; i++)
		{
			if( (i==2 || i==11) && (cadena[i] == '-') )//Acepta los guiones del cuit en el indice 2 y 11
			{
				continue;
			}
			if(cadena[i] < '0' || cadena[i] > '9')//Valida que los datos de cadena sean numericos
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/**
 * \brief Solicita un numero al usuario, luego de su verificación devuelve el resultado.
 * \param pResultado Puntero al espacio de memoria, donde se alojará el resultado de la función.
 * \param mensaje Mensaje a mostrar al usuario para el ingreso del numero.
 * \param mensajeError Mensaje de error, en caso de que el número ingresado por el usuario sea erróneo.
 * \param minimo Es el numero maximo a ser aceptado.
 * \param maximo Es el minimo minimo a ser aceptado.
 * \return Retorna 0 si obtuvo el nombre o apellido y -1 si tuvo algún error.
 *
 */
int utn_getNumberInt(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos)
{
	int retorno = -1;
	int bufferInt;
	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo < maximo && reintentos > -1)//Valida los datos de la funcion.
	{
		do
		{
			printf("%s",mensaje);
			if(	!getInt(&bufferInt) && //Obtiene un numero entero.
				bufferInt >= minimo && //Valida que el buffer sea mayor o igual al minimo.
				bufferInt <= maximo) //Valida que el buffer sea menor o igual al maximo.
			{
				retorno = 0;
				*pResultado = bufferInt;//Si cumple las validaciones, copia la informacion de bufferInt al puntero de resultado.
				break;
			}
			else
			{
				printf("%s",mensajeError);//Mensaje a mostrar, si no obtiene un string valido como numero entero.
				reintentos--;//Disminuye la cantidad de reintentos.
			}
		}while(reintentos>=0);
	}
	return retorno;
}

/**
 * \brief Obtiene una cadena válida como un numero entero.
 * \param pResultado Puntero al espacio de memoria, donde se alojará el resultado de la función.
 * \return Retorna 0 si obtuvo el numero entero y -1 si tuvo algún error.
 *
 */
static int getInt(int* pResultado)
{
    int retorno=-1;
    char bufferString[50];//*************************************

    if(	pResultado != NULL &&
    	!getString(bufferString,sizeof(bufferString)) &&//Obtiene una cadena de stdin valida como String.
    	isNumeric(bufferString,sizeof(bufferString)))//valida que bufferString sea valido como numerico.
	{
		retorno=0;
		*pResultado = atoi(bufferString);//Transforma a tipo de variable entero a bufferString y se lo asigna al puntero de resultado.
	}
    return retorno;
}


/**
 * \brief Verifica si la cadena ingresada es un numero entero válido.
 * \param cadena Cadena de caracteres a analizar.
 * \param \param len Define el tamaño de la cadena.
 * \return Retorna 1 si la cadena es un numero entero y 0 si no lo es.
 *
 */
static int isNumeric(char* cadena, int len)
{
	int retorno = 0;
	int i;
	if(cadena != NULL && len > 0)//Valida que el puntero sea valido y que el tamañano de cadena sea razonable.
	{
		retorno = 1;
		for(i=0;i<len && cadena[i] != '\0';i++)
		{
			if(i==0 && (cadena[i] == '+' || cadena[i] == '-'))//Valida que la primer posicion de la cadena pueda ser - o +
			{
				continue;//Itera una vez mas.
			}
			if(cadena[i] < '0'||cadena[i] > '9')//Valida que el contenido sea numerico.
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/**
 * \brief Solicita una descripción al usuario, luego de su verificación devuelve el resultado.
 * \param pResultado Puntero al espacio de memoria, donde se alojará el resultado de la función.
 * \param len Es la longitud del array resultado.
 * \param mensaje Mensaje a mostrar al usuario para el ingreso de la descripción.
 * \param mensajeError Mensaje de error, en caso de que la descripción ingresada por el usuario sea errónea.
 * \param reintentos Cantidad de reintentos.
 * \return Retorna 0 si obtuvo la descripción y -1 si tuvo algún error.
 *
 */
int utn_getDescription(char* pResultado, int len, char* mensaje, char* mensajeError, int reintentos)
{
	int retorno = -1;
	char bufferString[4096];

	if(pResultado != NULL && len > 0 && mensaje != NULL && mensajeError != NULL && reintentos > -1)//Valida los datos de la funcion.
	{
		do{
			printf("%s", mensaje);
			if( !getDescription(bufferString,sizeof(bufferString)) )//Obtiene una descripcion en bufferString.
			{
				retorno = 0;
				strncpy(pResultado,bufferString,len);//Si cumple las validaciones, copia la informacion de bufferString al puntero de resultado.
				break;
			}
			else
			{
				printf("%s", mensajeError);//Mensaje a mostrar, si no obtiene un string valido descripcion.
				reintentos--;//Disminuye la cantidad de reintentos.
			}
		}while(reintentos>=0);
	}
	return retorno;
}

/**
 * \brief Obtiene una cadena válida como una descripción.
 * \param pResultado Puntero al espacio de memoria, donde se alojará el resultado de la función.
 * \param len Define el tamaño de la cadena.
 * \return Retorna 0 si obtuvo la descripción y -1 si tuvo algun error.
 *
 */
static int getDescription(char* cadena, int len)
{
    int retorno=-1;
    char bufferString[4096];

    if( cadena != NULL &&//Valida que el puntero sea valido.
    	len > 0 &&//Valida que el tamañano de cadena sea razonable.
    	!getString(bufferString,sizeof(bufferString)) &&//Obtiene una cadena de stdin valida como String.
		isDescription(bufferString,sizeof(bufferString)) &&//valida que bufferString sea valido como descripcion.
		strnlen(bufferString,sizeof(bufferString)) < len)//Valida que el tamaño de bufferString sea menor que la longitud de cadena.
    	{
    		strncpy(cadena,bufferString,len);//Si cumple las validaciones, copia la informacion de bufferString en cadena.
			retorno = 0;
		}
    return retorno;
}

/**
 * \brief Verifica si la cadena ingresada es una descripción.
 * \param cadena Cadena de caracteres a analizar.
 * \param \param len Define el tamaño de la cadena.
 * \return Retorna 1 si la cadena es válida y 0 si no lo es.
 *
 */
static int isDescription(char* cadena, int len)
{
	int i=0;
	int retorno = 1;

	if(cadena != NULL && len > 0)//Valida que el puntero sea valido y que el tamañano de cadena sea razonable.
	{
		for(i=0 ; cadena[i] != '\0' && i < len; i++)
		{
			if( cadena[i] != '.' &&
				cadena[i] != ',' &&
				cadena[i] != ' ' &&
				(cadena[i] < 'A' || cadena[i] > 'Z' ) &&
				(cadena[i] < 'a' || cadena[i] > 'z' ) &&
				(cadena[i] < '0' || cadena[i] > '9' ) )//Valida que lo recibido en cadena, sean '.', ',', ' ', letras o numeros.
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
