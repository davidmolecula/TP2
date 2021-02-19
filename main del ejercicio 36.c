/*EJERCICIO 36:
Hacer un programa que lea al archivo "contactos.dat" creado en el Ejercicio 35 y crear una lista, en memoria dinámica, 
ordenada alfabéticamente. Una vez creada la lista guardarla en un archivo de organización directa llamado "contactos_ordenados.dat" imprimiendola en pantalla.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int menu ();

struct contacto {
	char nombre[30];
	char apellido[30];
	int edad;
	int telefono;
	char mail[40];
};

struct lista 
{
	struct contacto contacto1;
	struct lista *enlace;
};





int main ()
{

	struct lista *aux, *primero=NULL, *ultimo, *puntero;
	struct contacto contacto1;
	FILE *fb;
				if((fb=fopen("contactos.dat","rb"))==NULL)
				{
				printf("\nNo se pudo abrir el archivo\n");
				return 0;
				}

				fread(&contacto1, sizeof(struct contacto),1,fb);
				while(!feof(fb))
				{
					aux= (struct lista *) malloc(sizeof(struct lista));
					if(aux)
					{
						aux->contacto1=contacto1;
					if(primero==NULL)
					{
						primero=ultimo=aux;
						ultimo->enlace=NULL;

					}
					else
					{
						puntero=primero;
						
							if(strcmp(puntero->contacto1.apellido,aux->contacto1.apellido)>0)
							{
								printf("\nPrimer lugar \n");
								getch();
								aux->enlace=primero;
								primero=aux;
							}
					
						while(puntero->enlace)
						{
							if(strcmp(puntero->contacto1.apellido,aux->contacto1.apellido)<0)
							{
							if(strcmp(puntero->enlace->contacto1.apellido,aux->contacto1.apellido)>0)
							{
							printf("\notro lugar\n");
							getch();
							aux->enlace=puntero->enlace;
							puntero->enlace=aux;
							break;
							
							}
							else
							puntero=puntero->enlace;
							}
					
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
					fread(&contacto1,sizeof(struct contacto),1,fb);
			
				}
			fclose(fb);
		
	
					
						
				if((fb=fopen("contactos_ordenados.dat","wb+"))==NULL)
				{
				printf("\nNo se pudo abrir el archivo\n");
				return 0;
				}	

				
 				puntero=primero;
				while(puntero)
				{
				aux=puntero;
				fwrite(&aux->contacto1,sizeof(struct contacto),1,fb);
				printf("\n%s \n", puntero->contacto1.apellido);
				puntero=puntero->enlace;
				free(aux);
			    }
			    fclose(fb);

	
	
	
	
	return 0;
}


