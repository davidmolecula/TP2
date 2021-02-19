/*
El servicio técnico utiliza la pila generada en el ejercicio 43 en su labor diaria. Cada técnico toma una tarea de la pila
 y genera un orden de extracción de repuestos al depósito.
 Para optimizar los viajes al depósito se arma una lista con los repuestos que cada orden necesita utilizando la siguiente estructura:
typedef struct{
    repuestos_t repuesto;        
    int cantidad;
}extraccionRepuestos_t;
Se pide cargar la lista de repuestos solicitados por los técnicos.
 Tener en cuenta que varios técnicos pueden necesitar la misma parte,
  y en esos casos se debe incrementar la cantidad pedida en la lista.
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

struct repuestos{
        long partNumber;
        char descripcion[40];               
    };
    
struct extraccionRepuestos{
    struct repuestos repuesto;        
    int cantidad;
};

struct lista{
	struct extraccionRepuestos extraccion;
	struct lista *enlace;
};

struct pila* abrepila ();



int main(){
	struct pila *primero_pila;
	struct lista *primero=NULL,*aux,*puntero;
	int opcion;
	FILE* fp;
		
		
	primero_pila=abrepila();


	while(1)
	{
		printf("\n1.Retirar tarea de la pila \n2.Generar lista de extraccion de repuestos \n");
		scanf("%d",&opcion);
		fflush(stdin);
		if(opcion==2)
		{
			break;
		}
		if(opcion==1){
	
				
			if((aux=(struct lista *)malloc(sizeof(struct lista)))==NULL)
			{
				printf("\nError de memoria \n");
				return 0;
			}
			
			printf("\nNumero de orden: %ld \nDescripcion de falla: %s \nModelo: %s\n",primero_pila->repuestos.numeroDeOrden,primero_pila->repuestos.descripciondeFalla,primero_pila->repuestos.modelo);
			printf("\nIngrese el numero de parte del repuesto a solicitar \n");
			scanf("%ld",&aux->extraccion.repuesto.partNumber);
			fflush(stdin);
			printf("\nIngrese una descripcion del repuesto \n");
			gets(aux->extraccion.repuesto.descripcion);
			printf("\nIngrese la cantidad del repuesto a solicitar\n");
			scanf("%d",&aux->extraccion.cantidad);
			fflush(stdin);
			
				if(primero==NULL)
				{
					primero=aux;
					primero->enlace=NULL;
				}else{
				puntero=primero;
					while(1){
						if(puntero->extraccion.repuesto.partNumber<=aux->extraccion.repuesto.partNumber)
						{
							if(puntero->extraccion.repuesto.partNumber==aux->extraccion.repuesto.partNumber)
							{
								puntero->extraccion.cantidad+=aux->extraccion.cantidad;
								break;
							}else{
								aux->enlace=primero;
								primero=aux;
								break;
							}
						}
						while(puntero->enlace!=NULL)
						{
							if(puntero->enlace->extraccion.repuesto.partNumber<=aux->extraccion.repuesto.partNumber){
								puntero=puntero->enlace;
							}else break;
						}
						if(puntero->enlace==NULL)
						{
							puntero->enlace=aux;
							aux->enlace=NULL;
							break;
						}
						aux->enlace=puntero->enlace;
						puntero->enlace=aux;
						break;
					}
				}
		}		
	}
	
	if((fp=fopen("extraccion.dat","wb"))==NULL)
	{
		printf("\nError en la apertura del archivo\n");
		return 0;
	}	


	while(primero!=NULL){
		aux=primero;
		fwrite(&primero->extraccion,sizeof(struct extraccionRepuestos),1,fp);
		primero=primero->enlace;
		free(aux);
	}

fclose(fp);	
return 0;
}


struct pila *abrepila ()
{
	struct pila *aux,*primero=NULL;
	FILE *fp;
	repuestos_t ordenes;

	
	if((fp=fopen("pila44.dat","rb"))==NULL)
	{
		printf("\nError no se pudo abrir el archivo \n");
		return 0;
	}
	
	if((aux=(struct pila*)malloc(sizeof(struct pila)))==NULL)
	{
		printf("\nError en memoria dinamica \n");
		return 0;
	}
	fread(&ordenes,sizeof(repuestos_t),1,fp);
	do
	{	
		aux->repuestos=ordenes;
		aux->enlace=primero;
		primero=aux;
		fread(&ordenes,sizeof(repuestos_t),1,fp);		
	}while(!feof(fp));	
	
	
fclose(fp);
return primero;	
}
