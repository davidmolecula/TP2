#include<stdio.h>
#include<math.h>
#define pi 3.14159265
#define amplitud 128

typedef  struct {
	char seno;
	struct cola_t *enlace;
}cola_t;

int main(){
	cola_t *aux,*primero=NULL,*ultimo;
	int valores=0, i=0,recorrido=0;
	printf("\nIngrese la cantidad de valores muestreados de la señal \n");
	scanf("%d",&valores);
	fflush(stdin);


	for(i=0;i<valores;i++)
	{
		if((aux=(cola_t*)malloc(sizeof(cola_t)))==NULL)
		{
			printf("\nError en la memoria\n");
			return 0;
		}
		aux->seno=amplitud*(sin(((pi/2)*i)/(valores)));
		if(primero==NULL)
		{
			primero=ultimo=aux;
			aux->enlace=NULL;
		}else
		{
			ultimo->enlace=aux;
			aux->enlace=NULL;
			ultimo=aux;
		}
	}

	aux=primero;
	while(aux!=NULL){
		printf("%i \n", aux->seno);
		aux=aux->enlace;	
	}	
	aux=primero;
		for(recorrido=valores-1;recorrido>0;recorrido--)
		{
			for(i=0;i<recorrido;i++)
			{
			aux=aux->enlace;
			}
			if(aux->enlace!=NULL)
			printf("%d \n",aux->seno);
			aux=primero;
		}
		
	printf("0\n");

	aux=primero;
	
	while(aux!=NULL)
	{
		aux->seno=aux->seno^(1<<7); 
		aux=aux->enlace;	
	}	
	aux=primero;
		for(recorrido=valores-1;recorrido>0;recorrido--)
		{
			for(i=0;i<recorrido;i++){
			aux=aux->enlace;
			}
			if(aux->enlace!=NULL)
			printf("%d \n",aux->seno);
			aux=primero;
		}
		while(aux!=NULL)
		{
		printf("%d \n",aux->seno);
		aux=aux->enlace;	
		}
		printf("0\n");
			
	return 0;
}
