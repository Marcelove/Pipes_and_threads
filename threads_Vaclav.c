/**
 * Hello thread program.
 * Vaclav Bohac (c) 2011

 chamada: https://forms.gle/ZVWntbKh2E9aEKBN9

 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void *hello(void* par)
{
	int *ppar = (int *) par;     //"desemcapisular"        
	int thrid = ppar[0];
	printf("Hello, from thread! Argument is %d\n", thrid);
}


int main(void)
{

	int i, ret, numthreads = 2;
	int thread_param[numthreads][1];    //Parâmetros das threads, iremos diferenciar em uma matriz
	pthread_t thread[numthreads];       //teremos X threads 

	/*
	Pthread Handle (pthread_t) In many threads implementations, the pthread_t abstract type is implemented as 
	an integer (4 byte) thread ID. In the IBM® i implementation of Pthreads, the thread ID is a 64-bit integral 
	value and the pthread_t is an abstraction (structure) that contains that value and others.
	*/

	// Set thread ids.
	for (i = 0; i < numthreads; i++) {
		thread_param[i][0] = i + 1;   //adicionar os parametros na matriz
	}

	printf("Hello, from main!\n"); //printar da main()

	// Create threads.
	for (i = 0; i < numthreads; i++) {

		ret = pthread_create(&thread[i], NULL, hello, (void*) thread_param[i]); //chamar as threads

		// se pthread_create retornar algum valor diferente de 0, ou seja, falhou
		if (ret) {
			printf("Error while creating thread\n");
			return 1;
		}
	}

	// Wait for all threads.
	for (i = 0; i < numthreads; i++) {

		pthread_join(thread[i], NULL);  //finalizar as threads
		/*
		You don't need any calls to pthread_exit(3) in your particular code. In general,
		the main thread should not call pthread_exit , but should often call pthread_join(3) 
		to wait for some other thread to finish.
		https://stackoverflow.com/questions/20824229/when-to-use-pthread-exit-and-when-to-use-pthread-join-in-linux#:~:text=You%20don't%20need%20any,implicit%20after%20returning%20from%20it.
		*/

	}

	return 0;
}