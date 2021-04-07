#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>

//SOURCE: GEEKS FOR GEEKS
  
// A normal C function that is executed as a thread 
// when its name is specified in pthread_create()
void *myThreadFun(void *vargp)
{
	sleep(1);
	printf("Printing GeeksQuiz from Thread \n");
	return NULL;
}

void *myThreadFun2(void *vargp)
{
	sleep(2);
	printf("Thread 2 here we go!\n");
	return NULL;
}

   
int main()
{
    	pthread_t thread_id, thread_id2; //criação dos IDs das threads

    	printf("Before Thread\n");

    	pthread_create(&thread_id, NULL, myThreadFun, NULL);      //criação da thread1
    	pthread_create(&thread_id2, NULL, myThreadFun2, NULL);    //criação da thread2

    	pthread_join(thread_id, NULL);                            //só passa daqui depois de "finalizar" a thread1
    	pthread_join(thread_id2, NULL);                           //só passa daqui depois de "finalizar" a thread2

        /*
        The pthread_join() function provides a simple mechanism allowing an application to wait for a thread to terminate.
        */

    	printf("After Thread\n");
    	return 0;;
}

//testar com array