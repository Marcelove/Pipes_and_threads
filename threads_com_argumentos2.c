#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>

//SOURCE: GEEKS FOR GEEKS
  
// A normal C function that is executed as a thread 
// when its name is specified in pthread_create()

struct conteudo {

    int valor1;
    int valor2;

};

void *operacao1(void *vargp)
{

    int *valores_array = (int *)vargp; //castear o array na função
    printf("Printar o número [0] do array: %d\n", valores_array[0]); //printar o elemento [0]
	return NULL;
}

void *operacao2(void *vargp)
{
    struct conteudo * nossa_struct = (struct conteudo*)vargp; //castear a struct na função

	nossa_struct->valor2 = 3;
    printf("Printar contéudo 1: %d \n", nossa_struct->valor1);
    printf("Printar contéudo 2: %d \n", nossa_struct->valor2);
	return NULL;
}

   
int main()
{
        int *array = (int*)malloc(8 * sizeof(int)); 
        array[0] = 8; //declarar elemento [0]

        struct conteudo * nossa_struct = malloc(sizeof(struct conteudo));//criar a struct

    	pthread_t thread_id, thread_id2; //criar as IDS das threads
    	
        pthread_create(&thread_id, NULL, operacao1, (void*) array); //passar o ARRAY como ponteiro void
    	pthread_create(&thread_id2, NULL, operacao2, (void*) nossa_struct); //passar a struct que tem as matrizes para as operações

        free(array);

    	pthread_join(thread_id, NULL);
    	pthread_join(thread_id2, NULL);

    	return 0;
}