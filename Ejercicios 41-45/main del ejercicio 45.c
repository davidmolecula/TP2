/*
EJERCICIO 45:
La lista creada en el ejercicio 44 es procesada por el depósito. Para dicha tarea se pide hacer un programa que:
Descuente las cantidades solicitadas del archivo de stock, creado en el Ejercicio 41.
Hacer una cola con los repuestos en los que no se encontró stock suficiente para poder notificar a los clientes la demora de la reparación.
*/

#include<stdio.h>

 typedef struct
    {
        long partNumber;
        char descripcion[40];               
    }repuestos_t;
    
struct extraccionRepuestos
{
    repuestos_t repuesto;        
    int cantidad;
};

struct repuestosdeposito{
   long partNumber;
   long serialNumber;
   char descripcion[40];       
   char ubicacion[100];        
};

struct cola{
	struct extraccionRepuestos extraccion;
	struct cola *enlace;
};





int main(){
	FILE *fp,*fb,*fpn;
	struct extraccionRepuestos dato;
	struct repuestosdeposito repuestos;
	int i;
	struct cola *aux,*primero=NULL,*puntero;
		
	if((fb=fopen("stock.dat","rb+"))==NULL)
	{
		printf("\nError al abrir el archivo\n");
		return 0;
	}
	if((fp=fopen("extraccion.dat","rb"))==NULL){
		printf("no se pudo abrir el archivo\n");
		return 0;
	}
	
	fread(&dato,sizeof(struct extraccionRepuestos),1,fp);
	while(!feof(fp)){
		fseek(fb,0L,0);
		fread(&repuestos,sizeof(struct repuestosdeposito),1,fb);
		while(dato.cantidad!=0){
		
			if(dato.repuesto.partNumber==repuestos.partNumber){
				dato.cantidad--;
				printf("\nDatos del repuesto a retirar \n");
				printf("\nNumero de parte: %ld \n",repuestos.partNumber);
				printf("\nNumero de serie: %ld \n",repuestos.serialNumber);
				printf("\nDescripcion:	 %s \n",repuestos.descripcion);
				printf("\nUbicacion:		 %s \n",repuestos.ubicacion);
				repuestos.partNumber=-1;
				repuestos.partNumber=-1;
				repuestos.descripcion[0]='\0';
				repuestos.ubicacion[0]='\0';
				fseek(fb,(-1L)*sizeof(struct repuestosdeposito),1);
				fwrite(&repuestos,sizeof(struct repuestosdeposito),1,fb);
			}
			fread(&repuestos,sizeof(struct repuestosdeposito),1,fb);
			if(!feof(fb)){
				if((aux=(struct cola*)malloc(sizeof(struct cola)))==NULL)
				{
					printf("\nError al reservar memoria dinamica \n");
					return 0;
				}
				aux->extraccion=dato;
				if(primero==NULL){
					primero=puntero=aux;
					aux->enlace=NULL;
				}else{
				puntero->enlace=aux;
				aux->enlace=NULL;
				puntero=aux;
				}
				break;
			}
		}
		fread(&dato,sizeof(struct extraccionRepuestos),1,fp);
	}
	if((fpn=fopen("stock_nuevo2.txt","wb"))==NULL)
	{
		printf("\nError no se pudo crear el achivo \n");
		return 0;
	}
	fseek(fb,0,0);
	fread(&repuestos,sizeof(struct repuestosdeposito),1,fb);
	while(!feof(fb)){
		if(repuestos.partNumber!=-1){
			fwrite(&repuestos,sizeof(struct repuestosdeposito),1,fpn);
		}
	}
	remove("stock.dat");
	rename("stock_nuevo2.dat","stock.txt");
	
	fclose(fpn);
	fclose(fb);
	fclose(fp);
	return 0;
}
