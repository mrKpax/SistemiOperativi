/*
    Un processo P crea due figli ed aspetta la terminazione di entrambi.
     
    Il primo figlio stampa sullo schermo un messaggio indicando il proprio pid e il pid di P, poi termina.
 
    Il secondo figlio stampa sullo schermo la somma del proprio pid + il pid del padre e poi termina.
    
    Dopo la terminazione dei due figli P stampa sullo schermo un messaggio indicando il pid dei due figli ed il fatto che sono terminati e poi termina.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/signal.h>
#include <signal.h>
#include <unistd.h>

pid_t F1, F2;

void figlio1(void)
{
    printf("PID F1: %d\n", getpid());
    printf("PID padre di F1: %d\n", getppid());
}

void figlio2(void)
{
    int sum = getpid() + getppid();
    printf("Somma PID di F2 (%d) + PID padre (%d) = %d\n", getpid(), getppid(), sum);
}

int main(void)
{
    int F1, F2, status1, status2;
    
    F1 = fork();
    if (F1 < 0)
    {
        fprintf(stderr, "Errore nella creazione di un figlio\n");
        return -1;
    }
    else if (F1 == 0)
    {
        figlio1();
        exit(0);
    }
    
    F2 = fork();
    if (F2 < 0)
    {
        fprintf(stderr, "Errore nella creazione di un figlio\n");
        return -1;
    }
    
    else if (F2 == 0)
    {
        figlio2();
        exit(0);
    }
    
    waitpid(F1, &status1, 0);
    waitpid(F2, &status2, 0);
    printf("F1 con PID %d e F2 con PID %d terminati.\n", F1, F2);
    return 0;
}
