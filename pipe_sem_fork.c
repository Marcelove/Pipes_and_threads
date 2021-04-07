// C program to illustrate
// pipe system call in C
#include <stdio.h>
#include <unistd.h>
#define MSGSIZE 16

char* msg1 = "hello, world #1";
char* msg2 = "hello, world #2";
char* msg3 = "hello, world #3";


/*Conceptually, a pipe is a connection between two processes, such that the 
standard output from one process becomes the standard input of the other process.
*/

//One process can write to the pipe, and the other process can read from the pipe.

//It opens a pipe, which is an area of main memory that is treated as a “virtual file”.
  
int main()
{
        char inbuf[MSGSIZE]; //buffer IN, com tamanho 16
        int p[2], i;         //array 'p' para futuro pipe e 'i'.
  
        if (pipe(p) < 0)    //se a criação do pipe em p deu errado, abortar
                return 1;
  
        /* continued */
        /* write pipe */
        
        //tente comentar algumas dessas abaixo pra ver o que acontece!
        write(p[1], msg1, MSGSIZE);      //escreva no pipe a mensagem 1
        //write(p[1], msg2, MSGSIZE);      //escreva no pipe a mensagem 2
        write(p[1], msg3, MSGSIZE);      //escreva no pipe a mensagem 3
  
        for (i = 0; i < 3; i++) {
                /* read pipe */
                read(p[0], inbuf, MSGSIZE);
                printf("%s\n", inbuf);
        }
        
        return 0;
}