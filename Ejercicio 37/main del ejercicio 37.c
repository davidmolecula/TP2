/*
EJERCICIO 37: Ver Codigo Resuelto
Existe un archivo llamado "datos.dat", de tipo binario, cuya organización es secuencial. Los datos están organizados según la siguiente estructura:
struct d{                                                                                            
long clave; //Clave o Id del registro

char d[30]; // Descripcion                                                                                          
unsigned char tipo; //Tipo de datos como entero sin signo                                                                                                                                            
char b; //'A':Alta 'B':Baja                                                                                                                                                                          
}
Se Pide: Realizar una función que pase como parámetro la clave, entre otros parámetros, y apile dos valores, la Clave y su posición física respecto al 
archivo (registro 1, 2, etc), si es que el campo tipo tiene el bit 4 con valor 1. En caso de no encontrarlo mostrar por pantalla "Registro no encontrado". 
La función debe devolver el puntero de pila. Realizar el main con varias llamadas a dicha función y proceder a mostrar las descripciones del archivo, mediante 
la pila como acceso directo, NO USAR VARIABLES GLOBALES.
*/
#include <stdio.h>
#include <stdlib.h>

struct d
{
	int cl;
	char d[30];
	unsigned int tipo;
	unsigned int valor;
	char m;
};

struct pila{
	int clave;
	int posicion;
	struct pila *siguiente;
};

struct pila* apilador(int clave,int *contador, struct pila* principio);

int main() {
	
	FILE *fp;
	struct d dato;
	struct pila *principio=NULL, *nuevo;
	int clave;
	int contador;
	int esta;
	int salida=0;
	
	if((fp=fopen("datos.dat","rb"))==NULL)
	{
		printf("\nNo se pudo abrir el archivo\n");
		return 0;
	}
	
	do
	{
	printf("\nIngrese la clave del registro a buscar\n");
	fflush(stdin);
	scanf("%d", &clave);
	fseek(fp,0L,SEEK_SET);
	fread(&dato, sizeof(struct d),1,fp);
	contador=0;
	esta=0;
	while(!feof(fp))
	{
		if(dato.cl==clave)
		{
			if(dato.tipo &(1<<4))
			{
				principio=apilador(clave, &contador, principio);
				esta=1;
			}
		}
		contador++;
		fread(&dato,sizeof(struct d),1,fp);
	}
	if(esta==0 || principio==NULL)
	{
	printf("\nRegistro no encontrado\n");
	}
	printf("\Si desea salir presione 1\n");
	fflush(stdin);
	scanf("%d", &salida);
	
	}while(salida!=1);
	fclose(fp);
	return 0;
}



struct pila* apilador(int clave, int *contador, struct pila *principio)
{
	struct pila *nuevo;
	nuevo=(struct pila*)malloc(sizeof(struct d));
	if(nuevo)
	{
		nuevo->clave=clave;
		nuevo->posicion=contador;
		*contador=0;
		nuevo->siguiente=principio;
		principio=nuevo;
	}else
	printf("\nError\n");
	return principio;
}
