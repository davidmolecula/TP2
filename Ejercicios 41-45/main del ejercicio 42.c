/*
EJERCICIO 42:
El proveedor de repuestos de CosmeFulanito informó que una partida de repuestos salió con falla y debe ser devuelta. Para identificar la partida, 
el proveedor indicó que la falla fue en el partNumber: 1234 que tiene números de serie con el bit 3 y 5 en 1.
Para estas tareas se solicita:
Hacer una cola con todos los registros fallados
Realizar la baja física a todos los repuestos fallados
Crear un archivo donde se vuelque el contenido de la cola en orden inverso.
*/

#include<stdio.h>


typedef struct{
   long partNumber;
   long serialNumber;
   char descripcion[40];       
   char ubicacion[100];        
}repuestos_t;

struct cola{
	repuestos_t repuestos;
	struct cola *enlace;
};

int main(){
	struct cola *aux,*puntero,*primero=NULL;
	FILE *fp,*fpi,*fpn;
	int c=0,i;
	
	if((fp=fopen("stock.dat","rb"))==NULL)
	{
		printf("\nError al abrir el archivo\n");
		return 0;
	}
	if((fpn=fopen("stock_nuevo.dat","wb"))==NULL)
	{
		printf("\nError al crear el archivo nuevo\n");
		return 0;
	}
	
	
	if((aux=(struct cola*)malloc(sizeof(struct cola)))==NULL)
	{
		printf("\Error de memoria\n");
		return 0;
	}
	
	
	fread(&aux->repuestos,sizeof(repuestos_t),1,fp);
	while(!feof(fp))
	{
		if(aux->repuestos.partNumber==1234)
		{
			if(aux->repuestos.serialNumber&(1<<3)==(1<<3) && aux->repuestos.serialNumber&(1<<5)==(1<<5))
			{			
				if(primero==NULL)
				{
					primero=puntero=aux;
					primero->enlace=NULL;
				}else
				{
				puntero->enlace=aux;
				puntero=aux;
				}
			}
			else
			{
			fwrite(&aux->repuestos,sizeof(repuestos_t),1,fpn);
			}
		}
		else
		{
			fwrite(&aux->repuestos,sizeof(repuestos_t),1,fpn);
		}	
		fread(&aux->repuestos,sizeof(repuestos_t),1,fp);
	}

	if((fpi=fopen("stock_fallados.dat","wb"))==NULL)
	{
		printf("\nError al crear el archivo nuevo\n");
		return 0;
	}
	c=0;
	aux=primero;
	while(aux!=NULL)
	{
		aux=aux->enlace;
		c++;
	}
	do{
		aux=primero;
		for(i=0;i<c-1;i++){
			aux=aux->enlace;
		}
		fwrite(&aux->repuestos,sizeof(repuestos_t),1,fpi);
		free(aux);
		c--;
	}while(c!=0);

	
	fclose(fpi);
	fclose(fpn);
	fclose(fp);
		
	remove("stock.dat");
	rename("stock_nuevo.dat","stock.dat");

	return 0;
}
