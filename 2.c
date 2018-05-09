#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

void *sum(int *suma1)
{
	int s, r;
	srand(time(NULL));
	s=rand()%50;
	usleep(1000);
	r=rand()%50;
	*suma1=s+r;
	printf("El numero 1 es: %d\nEl numero 2 es: %d\nLa suma de los dos numeros es: %d\n", s, r, *suma1);
}

int main()
{
	int n, i, suma1, suma=0;
	printf("Introduzca el numero de hebras que deseea crear: ");
	scanf("%d", &n);
	for(i=0;i<n;i++)
	{
		pthread_t t;
		pthread_create(&t, NULL, (void *) sum, &suma1);	
		sleep(1);
		suma=suma1+suma;	
		printf("\nLa suma total en la %dº iteracion es: %d\n\n", i, suma);
		pthread_join(t, (void **) &suma1);		
	}
	printf("\nHan finalizado los thread.\n\n");
}
