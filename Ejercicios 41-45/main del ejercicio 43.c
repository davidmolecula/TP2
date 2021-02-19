/*
EJERCICIO 43:
El servicio técnico de CosmeFulanito recibe órdenes de trabajo diarias. Las mismas son cargadas en un archivo secuencial por el personal de recepción bajo 
la siguiente estructura de datos:
typedef struct{
   long numeroDeOrden;
   char cliente[40];       
   char descripciondeFalla[200];        
   char modelo[65];
   char fecha[10];
   char hora[10];
}repuestos_t;
Se pide:
Hacer una pila con las órdenes de trabajo de forma tal que la más vieja sea la última en cargarse.
*/

#include<stdio.h>
#include<string.h>

typedef struct{
   long numeroDeOrden;
   char cliente[40];       
   char descripciondeFalla[200];        
   char modelo[65];
   char fecha[10];
   char hora[10];
}repuestos_t;

struct pila{
	repuestos_t repuestos;
	struct pila_t *enlace;
};


int main()
{
	struct pila *aux,*primero=NULL;
	FILE *fp, *fb;
	repuestos_t ordenes;
	char ultima[10];
	
	if((fp=fopen("ordenes.dat","rb"))==NULL)
	{
		printf("\nNo se pudo abrir el archivo \n");
		return 0;
	}
	
	if((fp=fopen("pila44.dat","wb"))==NULL)
	{
		printf("\nNo se pudo abrir el archivo \n");
		return 0;
	}
	
	if((aux=(struct pila_t*)malloc(sizeof(struct pila)))==NULL)
	{
		printf("\nNo se pudo reservar memoria dinamica \n");
		return 0;
	}
	ultima[0]='\0';
	fread(&ordenes,sizeof(repuestos_t),1,fp);
	do{
 
		if(strcmp(ultima,ordenes.hora)<0)
		{
			strcpy(ultima,ordenes.hora);
		}
		fread(&ordenes,sizeof(repuestos_t),1,fp);
	}while(!feof(fp));
	
		fseek(fp,0L,SEEK_SET);
		fread(&ordenes,sizeof(repuestos_t),1,fp);
			do
				{	
				if(strcmp(ordenes.hora,ultima)!=0)
				{
				aux->repuestos=ordenes;
				aux->enlace=primero;
				primero=aux;
				fwrite(&ordenes,sizeof(repuestos_t),1,fb);
				}
				fread(&ordenes,sizeof(repuestos_t),1,fp);
			}while(!feof(fp));
			
		fseek(fp,0L,SEEK_SET);
		fread(&ordenes,sizeof(repuestos_t),1,fp);
			do
				{	
				if(strcmp(ordenes.hora,ultima)==0)
				{
				aux->repuestos=ordenes;
				aux->enlace=primero;
				primero=aux;
				fwrite(&ordenes,sizeof(repuestos_t),1,fb);
				}
				fread(&ordenes,sizeof(repuestos_t),1,fp);
				}while(!feof(fp));
	
fclose(fp);
fclose(fb);
return 0;	
}
