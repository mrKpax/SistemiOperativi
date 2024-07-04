/*
    Un processo P crea due figli ed aspetta la terminazione di entrambi.
     
    I due figli saranno in esecuzione concorrente.
     
    Il primo figlio scrive i primi 30 numeri di Fibonacci e poi termina. In presenza di un CTRL-C immesso da tastiera dovrà scrivere a schermo il proprio pid e continuare la sua esecuzione.
     
    Il secondo figlio scriverà i primi 20 fattoriali ed in presenza di un CTRL-C immesso da tastiera dovrà chiedere all’utente se deve continuare la sua esecuzione o terminare (e regolarsi di conseguenza).
     
    Dopo la terminazione dei due figli il padre P stamperò sullo schermo un messaggio indicando il pid dei due figli ed il fatto che sono terminati, e poi terminerà.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/signal.h>
#include <sys/wait.h>
#include <unistd.h>

int fibonacci(int n)
{
    if(n<=1)
        return n;
    return fibonacci(n-1) + fibonacci(n-2);
}

long int fattoriale(int n)
{
    if (n==0)
        return 1;
    return n * fattoriale(n-1);
}

void handler1(int sig)
{
    printf("Figlio 1, PID %d\n", getpid());
}

void handler2(int sig)
{
    char res[100];
    printf("Figlio 2: Continuare esecuzione? (Y/N)\n");
    scanf("%s", res);
    if (*res == 'Y')
        printf("Figlio 2: Continuo\n");
    else
    {
        printf("Terminazione Figlio 2\n");
        exit(0);
    }
}

int main(void)
{
    int F1, F2;
    
    F1 = fork();
    if (F1 < 0)
    {
        printf("Errore\n");
        exit(-1);
    }
    else if (F1 == 0)
    {
        signal(SIGINT, handler1);
        
        for (int i = 0; i <= 30; ++i)
        {
            printf("Fibonacci %d: %d\n", i, fibonacci(i));
            sleep(1);
        }
        
        exit(0);
    }
    else if (F1 > 0)
    {
        F2 = fork();
        if (F2 < 0)
        {
            printf("Errore\n");
            exit(-1);
        }
        else if (F2 == 0)
        {
            signal(SIGINT, handler2);
            
            for (int i=0; i<=20; ++i)
            {
                printf("Fattoriale %d: %lu\n", i, fattoriale(i));
                sleep(1);
            }
            
            exit(0);
        }
        else //padre
        {
            signal(SIGINT, SIG_IGN);
            wait(NULL);
            wait(NULL);
            printf("\n");
            printf("Padre: PID Figlio 1: %d\n", F1);
            printf("Padre: PID Figlio 2: %d\n", F2);
            printf("Figli terminati\n");

        }
    }
}

