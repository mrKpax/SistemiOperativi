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
#include <unistd.h>

pid_t F1, F2;

void handle_sigint1(int sig)
{
    printf("PID di F1: %d\n", getpid());
}

void handle_sigint2(int sig)
{
    char res[2];
    printf("Vuoi che il processo F2 con PID %d continui? (Y/N):\n", getpid());
    scanf("%1s", res);
    if (res[0] == 'N')
    {
        printf("Processo F2 con PID %d terminato\n", getpid());
        exit(0);
    }
}

void fibonacci(int n)
{
    signal(SIGINT, handle_sigint1);
    int first = 0, second = 1, next;
    for (int i=0; i<n; i++)
    {
        printf("Fibonacci: %d\n", first);
        next = first + second;
        first = second;
        second = next;
        sleep(2); // Attesa SIGINT
    }
}

void fattoriale(int n)
{
    signal(SIGINT, handle_sigint2);
    long fact = 1;
    for (int i=1; i<=n; i++)
    {
        fact = fact * i;
        printf("Fattoriale: %ld\n", fact);
        sleep(3); // Attesa SIGINT
    }
}

int main(void)
{
    int F1, F2, status1, status2;
    
    F1 = fork();
    if (F1 < 0)
    {
        fprintf(stderr, "Errore\n");
        return -1;
    }
    else if (F1 == 0)
    {
        fibonacci(30);
        exit(0);
    }
    else if (F1 > 0)
    {
        F2 = fork();
        if (F2 < 0)
        {
            fprintf(stderr, "Errore\n");
            return -1;
        }
        else if (F2 == 0)
        {
            fattoriale(20);
            exit(0);
        }
    }
    
    waitpid(F1, &status1, 0);
    waitpid(F2, &status2, 0);
    printf("Figli con PID %d e %d terminati\n", F1, F2);
    return 0;
}
