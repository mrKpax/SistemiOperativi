/*
    Un processo P crea un figlio F ed aspetta che termini.
    
    Il figlio F scriverà i primi 45 numeri di Fibonacci ed in presenza di un CTRL-C immesso da tastiera dovrà creare a sua volta un figlio F1 che chiederà all’utente se l’esecuzione di F deve continuare o se F deve terminare (e dovrà quindi regolarsi di conseguenza eventualmente uccidendo F e comunque terminando).
    
    Dopo la terminazione del figlio il padre P stampa sullo schermo un messaggio indicando il pid del figlio ed il fatto che è terminato e poi a sua volta termina.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

pid_t F;

void handle_sigint(int sig)
{
    int F1 = fork();
    char answer[2];
    
    if (F1 < 0)
    {
        fprintf(stderr, "Errore nella creazione di F1\n");
        exit(0);
    }
    else if (F1 == 0)
    {
        // Nipote F1
        printf("Vuoi che il processo F continui? (Y/N):");
        scanf("%1s", answer);
        if (answer[0] == 'Y')
        {
            signal(SIGINT,handle_sigint);
        }
        else
        {
            printf("Processo F terminato\n");
            kill(F, SIGKILL);
        }
    }
    else if (F1 > 0)
    {
        // Padre del nipote, F
        wait(NULL); // Attendi la terminazione di F1
    }
}

void fibonacci(int n) {
    int first = 0, second = 1, next;
    for (int i = 0; i < n; i++) {
        printf("%d\n", first);
        next = first + second;
        first = second;
        second = next;
        sleep(1); // Attendi eventuale segnale di interruzione
    }
    printf("\n");
}

int main(void)
{
    int F, status;

    // Creazione figlio F
    F = fork();

    if (F < 0)
    {
        fprintf(stderr, "Errore nella creazione del processo figlio F\n");
        return -1;
    }
    else if (F == 0)
    {
        // Figlio F
        signal(SIGINT, handle_sigint); // Gestione segnale SIGINT
        fibonacci(45);
    }
    else if (F > 0)
    {
        // Padre P
        wait(NULL); // Attende terminazione figlio
        printf("Figlio con pid %d terminato\n", getpid());
        printf("Padre terminato %d\n", wait(&status));
        return 1;
    }
}
