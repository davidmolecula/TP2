/* EJERCICIO 35:
Hacer un programa que tome los datos de contacto de una persona (Nombre, Apellido, edad, teléfono, mail) y los cargue, en forma directa, en una pila de memoria dinámica. 
Imprimir en pantalla y cargar en un archivo llamado "contactos.dat", de organización secuencial, los registros ingresados por el usuario si la persona tiene 
una edad mayor a 21 años. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

struct contacto {
	char nombre[30];
	char apellido[30];
	int edad;
	int telefono;
	char mail[40];
};

struct pila 
{
	int posicion;
	struct contacto persona;
	struct pila *siguiente;
};


int main() {
	int salida=0, i=0;
	FILE *fp;
	struct contacto persona1, persona2;
	char nombre[30];

	struct pila *nuevo, *ultimo=NULL;
	
	do{
		if((nuevo=(struct pila *)malloc(sizeof(struct pila)))==NULL)
		{
			printf("\nError\n");
			return 0;
		}
		printf("\nNombre:\n");
		fflush(stdin);
		gets(persona1.nombre);*/
		printf("\nApellido: \n");
		gets(persona1.apellido);
		fflush(stdin);
		printf("\nEdad: \n");
		fflush(stdin);
		scanf("%d", &persona1.edad);
		fflush(stdin);
		printf("\nTelefono: \n");
		fflush(stdin);
		scanf("%d", &persona1.telefono); 
		printf("\nMail: \n");
		fflush(stdin);
		gets(persona1.mail);*/
		nuevo->persona=persona1; 
		nuevo->posicion=i;
		i++;
		nuevo->siguiente=ultimo;
		ultimo=nuevo;
		printf("\nSi desea salir presione 7 \n");
		scanf("%d", &salida);
		fflush(stdin);
	}while(salida!=7);
	
	if((fp=fopen("contactos.dat","wb+"))==NULL)
	{
		printf("\nError\n");
		return 0;
	}
	
	if(!ultimo)
	{
		printf("\nLista vacia\n");
		return 0;
	}
	nuevo=ultimo;
	while(nuevo)
	{
	
		printf("\nNombre: %s\n",nuevo->persona.nombre );
		printf("\nApellido: %s \n",nuevo->persona.apellido);
		printf("\nEdad: %d\n", nuevo->persona.edad);
		printf("\nTelefono: %l\n", nuevo->persona.telefono);
		printf("\nMail: %s\n",nuevo->persona.mail);
		nuevo=nuevo->siguiente;
	}
	nuevo=ultimo;
	while(nuevo)
	{
		if(nuevo->persona.edad>21)
		{
		fwrite(&nuevo->persona,sizeof(struct contacto),1,fp);
		}
		nuevo=nuevo->siguiente;
	}
	fclose(fp);
	
	return 0;
}
