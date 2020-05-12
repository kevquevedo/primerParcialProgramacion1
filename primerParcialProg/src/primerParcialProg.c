/*
 ============================================================================
 Name        : primerParcialProg.c
 Author      : Kevin Quevedo
 Version     : 1.0
 Copyright   : Your copyright notice.
 Description : Primer Parcial de Programacion I - UTN
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "Cliente.h"
#include "Publicacion.h"
#include "Informe.h"

#define CLIENTES_LEN 100
#define PUBLIC_LEN 1000
#define RESP_LEN 2

int main(void) {

	setbuf(stdout, NULL);

	Cliente arrayClientes[CLIENTES_LEN];
	Publicacion arrayPublicaciones[PUBLIC_LEN];
	int opcion;
	char respuesta[RESP_LEN];
	int idCliente = 0;
	int auxIndiceCli;
	int auxIdCli;
	int idPublicacion = 0;
	int auxIndicePub;
	int auxIdPub;
	int auxNumRubro;

	if(!cli_initializeArray(arrayClientes,CLIENTES_LEN))//Inicializa el campo .isEmpty = 1 de los indices del array de clientes, indicando que estan "vacios".
	{
		printf("Array de clientes inicializado correctamente.\n");//Si los inicializa correctamente imprime mensaje.
	}
	if(!pub_initializeArray(arrayPublicaciones,PUBLIC_LEN))//Inicializa el campo .isEmpty = 1 de los indices del array de publicaciones, indicando que estan "vacios".
	{
		printf("Array de publicaciones inicializado correctamente.\n");//Si los inicializa correctamente imprime mensaje.
	}

	//Alta forzada de clientes.
	cli_altaForzadaArray(arrayClientes,CLIENTES_LEN,0,&idCliente,"Juan","Carlos","23-23232323-3");
	cli_altaForzadaArray(arrayClientes,CLIENTES_LEN,1,&idCliente,"Matias","Gonzales","34-34343434-4");
	cli_altaForzadaArray(arrayClientes,CLIENTES_LEN,2,&idCliente,"Adolfo","Justiniano","48-48484848-8");
	cli_altaForzadaArray(arrayClientes,CLIENTES_LEN,3,&idCliente,"Mauricio","Gil","56-56565656-6");

	//Alta forzada de publicaciones.
	pub_altaForzadaArray(arrayPublicaciones,PUBLIC_LEN,0,&idPublicacion,0,500,"VENDO BICICLETA");
	pub_altaForzadaArray(arrayPublicaciones,PUBLIC_LEN,1,&idPublicacion,0,500,"VENDO MOTO");
	pub_altaForzadaArray(arrayPublicaciones,PUBLIC_LEN,2,&idPublicacion,1,750,"COMPRO HELADERA");
	pub_altaForzadaArray(arrayPublicaciones,PUBLIC_LEN,3,&idPublicacion,1,750,"COMPRO LAVARROPA");
	pub_altaForzadaArray(arrayPublicaciones,PUBLIC_LEN,4,&idPublicacion,1,750,"COMPRO TELEVISOR");
	pub_altaForzadaArray(arrayPublicaciones,PUBLIC_LEN,5,&idPublicacion,2,900,"PERMUTO LAPICES");
	pub_altaForzadaArray(arrayPublicaciones,PUBLIC_LEN,6,&idPublicacion,2,900,"PERMUTO ROPA");
	pub_altaForzadaArray(arrayPublicaciones,PUBLIC_LEN,7,&idPublicacion,2,900,"PERMUTO VASOS");
	pub_altaForzadaArray(arrayPublicaciones,PUBLIC_LEN,8,&idPublicacion,2,900,"PERMUTO MESAS");

	do
	{
		if(!utn_getNumberInt(	&opcion, //Obtiene un numero, que se le asigna a "opcion" para que el pgm prosiga segun el numero indicado.
							"\n\n1. Cargar un Cliente."
							"\n2. Modificar un Cliente."
							"\n3. Dar de baja un Cliente."
							"\n4. Cargar un Publicacion."
							"\n5. Pausar una Publicacion."
							"\n6. Reanuda una Publicacion."
							"\n7. Imprimir lista de Clientes."
							"\n8. Imprimir lista de Publicaciones."
							"\n9. Informar clientes:\n"					//Menu de opciones desplegado al usuario.
							"\tA.- Cliente con más avisos activos.\n"
							"\tB.- Cliente con más avisos pausados.\n"
							"\tC.- Cliente con más avisos."
							"\n10. Informar publicaciones:\n"
							"\tA.- Cantidad de publicaciones de un rubro.\n"
							"\tB.- Rubro con más publicaciones activas.\n"
							"\tC.- Rubro con menos publicaciones activas."
							"\n11.Salir\n\n",
							"\nError, la opción ingresada es inválida",1,11,2))
		{
			switch(opcion)
			{
				case 1://Cargar un Cliente.

					auxIndiceCli = cli_getEmptyIndex(arrayClientes,CLIENTES_LEN);//Busca un indice vacio en el array de clientes y se lo asigna a auxIndiceCli.
					if( auxIndiceCli > -1 &&//Valida que el indice sea coherente.
						!cli_altaArray(arrayClientes,CLIENTES_LEN,auxIndiceCli,&idCliente))//Da de alta un cliente, en el indice que tiene cargado auxIndiceCli.
					{
						printf("Alta exitosa. El ID del cliente es: %d.",arrayClientes[auxIndiceCli].idCliente);//Mensaje a imprimir si cumple las validaciones del IF.
					}
					else
					{
						printf("No existe más lugar para nuevos clientes.\n");//Mensaje a imprimir si no encuentra un indice vacio.
					}
					break;

				case 2://Modificar un Cliente.

					if( !utn_getNumberInt(&auxIdCli,"Ingrese el ID del cliente a modificar:\n","ID invalido.\n",0,idCliente,0) &&//Obtiene un numero valido como ID y se lo asigna a auxIdCli.
						cli_buscarId(arrayClientes,CLIENTES_LEN,auxIdCli) != -1 &&//Valida que el ID obtenido, exista en el array de clientes.
						!cli_modificarArray(arrayClientes,CLIENTES_LEN,auxIdCli))//Si existe el ID obtenido, ingresa a modificar los valores del indice donde se encuentre dicho ID.
					{
						printf("Modificación exitosa.\n");//Mensaje a imprimir si cumple las validaciones del IF.
					}
					else
					{
						printf("No existe un cliente con el ID ingresado.\n");//Mensaje a imprimir si no existe el ID obtenido.
					}
					break;

				case 3://Dar de baja un Cliente y sus publicaciones.

					if( !utn_getNumberInt(&auxIdCli,"Ingrese el ID del cliente a dar de baja:\n","ID invalido.\n",0,idCliente,0) &&//Obtiene un numero valido como ID y se lo asigna a auxIdCli.
						cli_buscarId(arrayClientes,CLIENTES_LEN,auxIdCli) != -1 &&//Valida que el ID obtenido, exista en el array de clientes.
						!pub_imprimirPublicByCliente(arrayPublicaciones,PUBLIC_LEN,auxIdCli))//Si existe el ID obtenido, ingresa a modificar los valores del indice donde se encuentre dicho ID.
					{
							while(1)
							{
								if( !utn_getNameOrSurname(respuesta,RESP_LEN,"Desea eliminarlo? (Ingrese S/N):\n","No valido.\n",2) &&//Confirma si desea eliminar los datos del cliente con el ID obtenido.
									!strncmp(respuesta,"S",RESP_LEN) &&//Compara si el string obtenido es igual a S.
									!cli_bajaArray(arrayClientes,CLIENTES_LEN,auxIdCli,arrayPublicaciones,PUBLIC_LEN))//Si la respueta es si, procede a borrar los datos del cliente y sus publicaciones.
								{
									printf("Baja exitosa.\n");//Mensaje a imprimir si cumple las validaciones del IF.
									break;
								}
								else if(!strncmp(respuesta,"N",RESP_LEN))//Compara si el string obtenido es igual a N.
								{
									printf("No se realizó la baja.\n");//No se realiza la baja del usuario ya que la respuesta fue negativa.
									break;
								}
							}
					}
					else
					{
						printf("No existe un cliente con el ID ingresado.\n");//Mensaje a imprimir si no existe el ID obtenido.
					}
					break;

				case 4://Cargar un Publicacion.

					cli_imprimirArray(arrayClientes,CLIENTES_LEN);//Imprime los clientes, que se encuentran "cargados".
					if( !utn_getNumberInt(&auxIdCli,"\nIngrese el ID del cliente:\n","ID invalido.\n",0,idCliente,0) &&//Obtiene un numero valido como ID y se lo asigna a auxIdCli.
						cli_buscarId(arrayClientes,CLIENTES_LEN,auxIdCli) != -1)//Valida que el ID obtenido, exista en el array de clientes.
					{
						auxIndicePub = pub_getEmptyIndex(arrayPublicaciones,PUBLIC_LEN);//Si pasa las validaciones del IF, obtiene un indice en el array de publicaciones "vacio" y se lo asigna a auxIndicePub.
						if( auxIndicePub > -1 &&//Valida que el indice sea coherente.
							!pub_altaArray(arrayPublicaciones,PUBLIC_LEN,auxIndicePub,&idPublicacion,auxIdCli))//Da de alta una publicacion, en el indice asignado a auxIdPub.
						{
							printf("Alta exitosa. El ID de la publicacion es: %d.",arrayPublicaciones[auxIndicePub].idPublicacion);//Mensaje a imprimir si cumple las validaciones del IF.
						}
						else
						{
							printf("No existe más lugar para nuevas publicaciones.\n");//Mensaje a imprimir si no encuentra un indice vacio.
						}
					}
					else
					{
						printf("No existe un cliente con el ID ingresado.\n");//Mensaje a imprimir si no encuentra el ID del cliente obtenido.
					}
					break;

				case 5://Pausar una Publicacion.

					if( !utn_getNumberInt(&auxIdPub,"Ingrese el ID de la publicación a pausar:\n","ID invalido.\n",0,idPublicacion,0) &&//Obtiene un numero valido como ID y se lo asigna a auxIdCli.
						pub_buscarId(arrayPublicaciones,PUBLIC_LEN,auxIdPub) > -1 &&//Valida que el ID obtenido, exista en el array de publicaciones.
						!cli_imprimirClienteByIdPub(arrayClientes,CLIENTES_LEN,auxIdPub,arrayPublicaciones,PUBLIC_LEN))//Si escuentra el ID de la publicación, imprime la informacion del Cliente al que pertenece.
					{
						while(1)
						{
							if( !utn_getNameOrSurname(respuesta,RESP_LEN,"\nDesea cambiar el estado a PAUSADA? (Ingrese S/N):\n","No valido.\n",2) &&//Le solicita confirmacion al usuario si desea pausar la publicacion.
								!strncmp(respuesta,"S",RESP_LEN) &&//Compara si el string obtenido es igual a S.
								!pub_pausarArray(arrayPublicaciones,PUBLIC_LEN,auxIdPub) )//Cambia a estado PAUSADA una publicacion, en el indice asignado a auxIdPub.
							{
								printf("Cambio de estado a PAUSADA exitoso!.\n");//Mensaje a imprimir si cumple las validaciones del IF.
								break;
							}
							else if(!strncmp(respuesta,"N",RESP_LEN))//Compara si el string obtenido es igual a N.
							{
								printf("No se realizó cambio de estado.\n");//No se realiza el cambio de estado ya que la respuesta fue negativa.
								break;
							}
							else
							{
								printf("La publicacion ya se encuentra pausada!.\n");//Mensaje a imprimir si la publicacion ya se encuentra pausada.
								break;
							}
						}
					}
					else
					{
						printf("No existe una publicacion con el ID ingresado.\n");//Mensaje a imprimir si no encuentra el ID del cliente obtenido.
					}
					break;

				case 6://Reanuda una Publicacion.

					if( !utn_getNumberInt(&auxIdPub,"Ingrese el ID de la publicación a reanudar:\n","ID invalido.\n",0,idPublicacion,0) &&
						pub_buscarId(arrayPublicaciones,PUBLIC_LEN,auxIdPub) != -1 &&
						!cli_imprimirClienteByIdPub(arrayClientes,CLIENTES_LEN,auxIdPub,arrayPublicaciones,PUBLIC_LEN))
					{
						while(1)
						{
							if( !utn_getNameOrSurname(respuesta,RESP_LEN,"\nDesea cambiar el estado a ACTIVA? (Ingrese S/N):\n","No valido.\n",2) &&//Le solicita confirmacion al usuario si desea reanudar/volver a activar la publicacion.
								!strncmp(respuesta,"S",RESP_LEN) &&//Compara si el string obtenido es igual a S.
								!pub_reanudarArray(arrayPublicaciones,PUBLIC_LEN,auxIdPub) )//Reanuda/cambia a estado ACTIVA una publicacion, en el indice asignado a auxIdPub.
							{
								printf("Cambio de estado a ACTIVA exitoso!.\n");//Mensaje a imprimir si cumple las validaciones del IF.
								break;
							}
							else if(!strncmp(respuesta,"N",RESP_LEN))//Compara si el string obtenido es igual a N.
							{
								printf("No se realizó cambio de estado.\n");//No se realiza el cambio de estado ya que la respuesta fue negativa.
								break;
							}
							else
							{
								printf("La publicacion ya se encuentra activa!.\n");//Mensaje a imprimir si la publicacion ya se encuentra activa.
								break;
							}
						}
					}
					else
					{
						printf("No existe una publicacion con el ID ingresado.\n");//Mensaje a imprimir si no encuentra el ID del cliente obtenido.
					}
					break;

				case 7://Imprimir lista de Clientes.

					if(!info_imprimirArrayCantPubAct(arrayClientes,CLIENTES_LEN,arrayPublicaciones,PUBLIC_LEN))
					{//Imprime la lista de clientes con la cantidad de publicaciones activas de cada uno.
						printf("\nLista impresa exitosamente.\n");//Mensaje a imprimir si cumple las validaciones del IF.
					}
					break;

				case 8://Imprimir lista de Publicaciones.

					if(!info_imprimirArrayByEstado(arrayPublicaciones,PUBLIC_LEN,arrayClientes,CLIENTES_LEN))
					{//Imprime la lista de publicaciones junto con el Cuit de cliente, mas el estado "ACTIVA" o "PAUSADA".
						printf("\nLista impresa correctamente.\n");//Mensaje a imprimir si cumple las validaciones del IF.
					}
					break;

				case 9://Informar clientes.

					do
					{
						if( !utn_getNameOrSurname(respuesta,RESP_LEN,"Por favor, ingrese una opcion:\n"//Le solicita al usuario una letra para seleccionar la opcion deseable.
																	 "\tA.- Cliente con más avisos activos.\n"
																	 "\tB.- Cliente con más avisos pausados.\n"//Menu de opciones a ingresar por el usuario.
																	 "\tC.- Cliente con más avisos.\n"
																	 "\tD.- Volver al menú principal.\n","No valido.\n",2) &&
							!strncmp(respuesta,"A",RESP_LEN) )//Compara si el string obtenido es igual a A.
						{
							if(!info_calcularEImprmirAvisosCliente(arrayClientes,CLIENTES_LEN,arrayPublicaciones,PUBLIC_LEN,3))//Busca e imprime los datos del cliente con mas publicaciones sin distinguir A o P(3).
							{
								printf("\nProcesado correctamente.\n");//Mensaje a imprimir si cumple las validaciones del IF.
							}
							break;
						}
						else if(!strncmp(respuesta,"B",RESP_LEN))//Compara si el string obtenido es igual a B.
						{
							if(!info_calcularEImprmirAvisosCliente(arrayClientes,CLIENTES_LEN,arrayPublicaciones,PUBLIC_LEN,2))//Busca e imprime los datos del cliente con mas publicaciones Pausadas (2).
							{
								printf("\nProcesado correctamente.\n");//Mensaje a imprimir si cumple las validaciones del IF.
							}
							break;
						}
						else if(!strncmp(respuesta,"C",RESP_LEN))//Compara si el string obtenido es igual a C.
						{
							if(!info_calcularEImprmirAvisosCliente(arrayClientes,CLIENTES_LEN,arrayPublicaciones,PUBLIC_LEN,1))//Busca e imprime los datos del cliente con mas publicaciones Activas (1).
							{
								printf("\nProcesado correctamente.\n");//Mensaje a imprimir si cumple las validaciones del IF.
							}
							break;
						}
						else
						{
							printf("La opcion ingresada no es valida.\n");//Mensaje a imprimir, si la opcion no es valida.
						}
					}while(strncmp(respuesta,"D",RESP_LEN));////Compara si el string obtenido es igual a D. Si la respuesta es afirmativa, sale del bucle, y vuelve al menu principal.
					break;

				case 10://Informar publicaciones.

					do
					{
						if( !utn_getNameOrSurname(respuesta,RESP_LEN,"Por favor, ingrese una opcion:\n"//Le solicita al usuario una letra para seleccionar la opcion deseable.
																	 "\tA.- Cantidad de publicaciones de un rubro.\n"
																	 "\tB.- Rubro con más publicaciones activas.\n"
																	 "\tC.- Rubro con menos publicaciones activas.\n"//Menu de opciones a ingresar por el usuario.
																	 "\tD.- Volver al menú principal.\n","No valido.\n",2) &&
							!strncmp(respuesta,"A",RESP_LEN) )//Compara si el string obtenido es igual a A.
						{
							if( !utn_getNumberInt(&auxNumRubro,"Ingrese el numero de Rubro:\n","Rubro invalido.\n",0,1000,0) &&//Le solicita al usuario un numero y se lo asigna a auxNumRubro.
								info_buscarRubro(arrayPublicaciones,PUBLIC_LEN,auxNumRubro) != -1 &&//Busca el numero de rubro asignado a auxNumRubro y lo busca en el array de publicaciones.
								!info_imprimirPubActivasByRubro(arrayPublicaciones,PUBLIC_LEN,auxNumRubro) )//Imprime la cantidad de publicaciones activas del rubro asignado auxNumRubro.
							{
								printf("\nBusqueda exitosa!.\n");//Mensaje a imprimir si cumple las validaciones del IF.
							}
							else
							{
								printf("El rubro ingresado no existe.\n");//Mensaje a imprimir si el rubro ingresado no existe.
								break;
							}
						}
						else if( !strncmp(respuesta,"B",RESP_LEN) &&//Compara si el string obtenido es igual a B.
								 !info_imprimirMaximosMinimosPubByRubros(arrayPublicaciones,PUBLIC_LEN,1))//Imprime el rubro que posee mayor (1) cantidad de publicaciones activas.
						{
							printf("\nBusqueda exitosa!.\n");//Mensaje a imprimir si cumple las validaciones del IF.
							break;
						}
						else if(!strncmp(respuesta,"C",RESP_LEN) &&//Compara si el string obtenido es igual a C.
								!info_imprimirMaximosMinimosPubByRubros(arrayPublicaciones,PUBLIC_LEN,0))//Imprime el rubro que posee menor (0) cantidad de publicaciones activas.
						{
							printf("\nBusqueda exitosa!.\n");//Mensaje a imprimir si cumple las validaciones del IF.
							break;
						}
						else
						{
							printf("La opcion ingresada no es valida.\n");//Mensaje a imprimir, si la opcion no es valida.
						}
					} while(!strncmp(respuesta,"D",RESP_LEN));//Si la respuesta es D, sale del bucle, y vuelve al menu principal.
					break;
			}
		}
	}while(opcion!=11);////Si el numero es 11, sale del bucle, y finaliza el pgm.


	return EXIT_SUCCESS;
}
