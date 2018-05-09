#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>
#include <string.h>
#include <unistd.h>



void imprime(char *cadena)
{
	int i;
	for(i=0;i<strlen(cadena);i++)
	{
		printf("%c\n", cadena[i]);
		sleep(1);
	}
	pthread_exit(NULL);
}

int main()
{
	char cad1[]="hola";
	char cad2[]="mundo";
	pthread_t t1, t2;
	
	pthread_create(&t1, NULL, (void *) imprime, &cad1); 
	pthread_create(&t2, NULL, (void *) imprime, &cad2);
	
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	
	printf("\nHan finalizado los thread.\n");
}
