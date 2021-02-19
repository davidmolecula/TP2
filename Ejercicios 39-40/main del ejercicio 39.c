/*
EJERCICIO 39:
Hacer un programa que tome los datos de medición de potencia, cargados por el usuario, de un sistema de medición a distancia.
Los datos que cargará el usuario tienen la siguiente estructura:
    char desc[60];
    unsigned char potencia;
    unsigned int estado;
Donde estado es la multiplicación del valor ASCII de la primer letra de la descripción por la potencia. Los datos cargados se deberán guardar en una lista 
ordenada, de mayor a menor, del valor de potencia. Una vez finalizada la carga guardar los datos en un archivo de organización directa llamado "potencia.dat"
imprimiendo en pantalla los datos.
*/

struct datos{

	char desc[60];
    unsigned char potencia;
    unsigned int estado;
			};

#include <stdio.h>


int menu ();

struct lista 
{
	struct datos dato;
	struct lista *enlace;
};

struct directo {
	int id;
	struct datos dato1;
	
};


int main ()
{
	int opcion;
	int i;
	struct lista *aux, *primero=NULL, *ultimo, *puntero;
	struct directo dato;
	FILE *fp;
	do
	{
	 	
					aux=(struct lista *) malloc(sizeof(struct lista));
					if(aux)
					{
						printf("\nIngrese la descripcion\n");
						fflush(stdin);
						gets(aux->dato.desc);
						fflush(stdin);
						printf("\nPotencia:\n");
						scanf("%c", &aux->dato.potencia);
						fflush(stdin);
						aux->dato.estado=aux->dato.desc[0]*aux->dato.potencia;
						
					if(primero==NULL)
					{
						primero=ultimo=aux;
						ultimo->enlace=NULL;
					}
					else
					{
						puntero=primero;
							if(puntero->dato.potencia < aux->dato.potencia)
							{
								printf("\nPrimer lugar \n");
								getch();
								aux->enlace=primero;
								primero=aux;
								
							}
					
						while(puntero->enlace)
						{
							if(puntero->dato.potencia > aux->dato.potencia)
							{
							if(puntero->enlace->dato.potencia < aux->dato.potencia)
							{
							printf("\notro lugar\n");
							getch();
							aux->enlace=puntero->enlace;
							puntero->enlace=aux;
							break;
							}
							puntero=puntero->enlace;
							}
							else
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
							
						
						

			printf("\nSi desea salir presione 4\n");
			scanf("%d", &opcion);
			fflush(stdin);
			
	
	
	}while(opcion!=4);
	
	if((fp=fopen("potencia.dat","wb"))==NULL)
	{
		printf("\nError\n");
		return 0;
	}
	 	i=0;
		puntero=primero;
				while(puntero)
				{
				aux=puntero;
				dato.dato1=aux->dato;
				dato.id=i;
				printf("\n%d\n", puntero->dato.potencia);
				fwrite(&dato,sizeof(struct directo),1,fp);
				puntero=puntero->enlace;
				free(aux);
				i++;
			    }
	fclose(fp);
	return 0;
}


