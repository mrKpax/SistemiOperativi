/*
    Un processo P crea due figli ed aspetta la terminazione di entrambi.
     
    Il primo figlio stampa sullo schermo un messaggio indicando il proprio pid e il pid di P, poi termina.
 
    Il secondo figlio stampa sullo schermo la somma del proprio pid + il pid del padre e poi termina.
    
    Dopo la terminazione dei due figli P stampa sullo schermo un messaggio indicando il pid dei due figli ed il fatto che sono terminati e poi termina.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    int F1, F2, stat;
    
    F1 = fork();
    if (F1 < 0)
    {
        fprintf(stderr, "Errore\n");
        exit(-1);
    }
    else if (F1 == 0)
    {
        printf("Sono F1 [PID %d], mio Padre ha PID [%d]\n", getpid(), getppid());
        exit(0);
    }
    else if (F1 > 0)
    {
        F2 = fork();
        if (F2 < 0)
        {
            fprintf(stderr, "Errore\n");
            exit(-1);
        }
        else if (F2 == 0)
        {
            int sum;
            sum = getpid() + getppid();
            printf("Sono F2 [PID %d], SOMMA = %d\n", getpid(), sum);
            exit(0);
        }
        else
        {
            wait(&stat);
            wait(&stat);
            printf("F1 [%d] ed F2 [%d] terminati\n", F1, F2);
            exit(0);
        }
    }
}
