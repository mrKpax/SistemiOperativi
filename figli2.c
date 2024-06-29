/*
    Un processo P crea due figli e aspetta la terminazione di entrambi.
     
    Il primo figlio stampa sullo schermo un messaggio indicando il proprio pid e poi stampa sullo schermo i numeri da 1 a 50, poi termina.
     
    Il secondo figlio stampa sullo schermo il pid del padre e poi stampa sullo schermo i numeri da 101 a 150 e poi termina.
     
    Dopo la terminazione dei due figli P stampa sullo schermo un messaggio indicando il pid dei due figli ed il fatto che sono terminati e poi termina.
 
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/signal.h>
#include <unistd.h>

int main(void)
{
    int F1, F2, stat;
    
    F1 = fork();
    if (F1 < 0) {
        fprintf(stderr, "Errore\n");
        exit(-1);
    }
    else if(F1 == 0)
    {
        printf("Sono F1 [PID %d]\n", getpid());
        for (int i=1; i<=50; i++)
        {
            printf("%d\n", i);
        }
        exit(0);
    }
    else if(F1 > 0)
    {
        F2 = fork();
        if (F2 < 0) {
            fprintf(stderr, "Errore\n");
            exit(-1);
        }
        else if(F2 == 0)
        {
            printf("Sono F2 [PID padre %d]\n", getppid());
            for (int i=101; i<=150; i++)
            {
                printf("%d\n", i);
            }
            exit(0);
        }
        
        waitpid(F1, &stat, 0);
        waitpid(F1, &stat, 0);
        printf("F1 [PID %d] e F2 [PID %d] terminati\n", F1, F2);
        exit(0);
    }
}
