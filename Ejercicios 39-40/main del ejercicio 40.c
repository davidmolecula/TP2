/*
EJERCICIO 40:
Utilizando el archivo “potencia.dat” creado en el Ejercicio 39, realizar una función que pase como parámetro, entre otros datos, la clave del registro (id).
La función ubicará el registro correspondiente al id pasado como parámetro, y utilizando punteros imprimirá la primera palabra del campo "desc" en forma inversa, 
además cambiará el estado del bit 3 para luego actualizar el archivo. Además, se agregará a una pila 
la potencia cuando los bits 0 y 2, del campo estado, estén encendidos, en caso contrario se agregará el registro al archivo “salida.dat” de organización secuencial.
*/

#include <stdio.h>

struct datos{

	char desc[60];
    unsigned char potencia;
    unsigned int estado;
			};
			
			
struct pila {
	int dato;
	struct pila *siguiente;
			};

struct directo {
	int id;
	struct datos dato1;
	
};

void funcion(int id);


int main()
{
	int id;

	
	

		printf("\nIngrese el id\n");
		fflush(stdin);
		scanf("%d", &id);
		fflush(stdin);

		funcion(id);
	
	return 0;
}



void funcion(int id)
{
	FILE *fp, *fb;
	int i=0, j;
	char c;
	struct pila *aux, *primero=NULL;
	struct directo dato;
	

		if((fp=fopen("potencia.dat","rb+"))==NULL)
		
		{
			printf("\nError\n");
			return 0;	
		}
		fseek(fp, (1L)*id*(sizeof(struct directo)),SEEK_SET);
		fread(&dato, sizeof(struct directo),1,fp);
		
		while(c!=32)
		{
		c=dato.dato1.desc[i];
		i++;			
		}
		for(j=i-2;j>=0;j--)
		{
			printf("%c",dato.dato1.desc[j]);
		}
		
		dato.dato1.estado=dato.dato1.estado^(1<<3);
		fwrite(&dato,sizeof(struct directo),1,fp);
		fclose(fp);
		
		if(dato.dato1.estado&(1<<0) && dato.dato1.estado&(1<<2))
		{
		
			aux=(struct pila *)malloc(sizeof(struct pila));
				if(aux)
				{	
				aux->dato=dato.dato1.potencia;
				aux->siguiente=primero;
				primero=aux;
				}
		}else
		{
			if((fb=fopen("salida.dat","wb+"))==NULL)
			{
				printf("\nError\n");
				return 0;
			}
			fwrite(&dato, sizeof(struct directo),1,fb);
			fclose(fb);
		}
	
}
