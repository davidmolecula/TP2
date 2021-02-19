/*
EJERCICIO 41:
El depósito de la empresa CosmeFulanito necesita cargar su stock de repuestos en forma ordenada. Para dicha tarea se solicitó categorizar a los respuestos
bajo la siguiente estructura de datos:
typedef struct{
   long partNumber;
   long serialNumber;
   char descripcion[40];       
   chat ubicacion[100];        
}repuestos_t;
Los repuestos no están ordenados, se solicita cargarlos en una lista, la cual ordene por descripción a los repuestos para luego guardarlos en un archivo 
de stock con organización secuencial.
Imprimir en pantalla la lista con cada inserción.
El archivo se generará cuando el usuario decide no cargar mas productos.
*/

#include <stdio.h>

typedef struct{
   long partNumber;
   long serialNumber;
   char descripcion[40];       
   char ubicacion[100];        
}repuestos_t;

struct lista 
{
	repuestos_t repuestos;
	struct lista *enlace;
};

int main ()
{

	struct lista *aux, *primero=NULL, *ultimo, *puntero;
	int opcion;
	FILE *fb;
			

				do{
					aux=(struct lista*)malloc(sizeof(struct lista));
					if(aux)
					{
					printf("\nIngrese numero de parte \n");
					scanf("%ld",&aux->repuestos.partNumber);
					fflush(stdin);
					printf("\nIngrese numero de serie \n");
					scanf("%ld",&aux->repuestos.serialNumber);
					fflush(stdin);
					printf("\nIngrese una descripcion para el producto \n");
					gets(aux->repuestos.descripcion);
					fflush(stdin);
					printf("\nIngrese la ubicacion del producto \n");
					gets(aux->repuestos.ubicacion);	
					fflush(stdin);	
					
					if(primero==NULL)
					{
						primero=ultimo=aux;
						ultimo->enlace=NULL;

					}
					else
					{
						puntero=primero;
						
							if(strcmp(puntero->repuestos.descripcion,aux->repuestos.descripcion)>0)
							{
								printf("\nPrimer lugar \n");
								getch();
								aux->enlace=primero;
								primero=aux;
							}else
							{
							while(puntero->enlace)
							{
							if(strcmp(puntero->repuestos.descripcion,aux->repuestos.descripcion)<0)
							{
							if(strcmp(puntero->enlace->repuestos.descripcion,aux->repuestos.descripcion)>0)
							{
							printf("\nOtro lugar\n");
							getch();
							aux->enlace=puntero->enlace;
							puntero->enlace=aux;
							break;
							}
							else
							puntero=puntero->enlace;
							}else
							break;
							}
							if(puntero==ultimo)
							{
							
							printf("\nUltimo lugar\n");
							getch();
							ultimo->enlace=aux;
							ultimo=aux;
							ultimo->enlace=NULL;
							
								
							}
						}
						}
					}
					puntero=primero;
					while(puntero!=NULL)
					{
					printf("\nNumero de parte: %ld \n",puntero->repuestos.partNumber);
					printf("\nNumero de serie: %ld \n",puntero->repuestos.serialNumber);
					printf("\nDescripcion: %s \n",puntero->repuestos.descripcion);
					printf("\nUbicacion: %s \n",puntero->repuestos.ubicacion);
					puntero=puntero->enlace;
					}
					
				printf("\nSi desea salir presione 4\n");
				fflush(stdin);
				scanf("%d", &opcion);
				fflush(stdin);
	
			}while(opcion!=4);	
						
				if((fb=fopen("stock.dat","wb"))==NULL)
				{
				printf("\nNo se pudo abrir el archivo\n");
				return 0;
				}	

				
 				puntero=primero;
				while(puntero)
				{
				aux=puntero;
				fwrite(&aux->repuestos,sizeof(repuestos_t),1,fb);
				puntero=puntero->enlace;
				free(aux);
			    }
			    fclose(fb);
	
	return 0;
}

