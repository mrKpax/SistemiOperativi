/*
    Questo programma agisce come una shell molto semplice.
    Riceve comandi dall'utente, crea un processo figlio per eseguire ciascun comando e
    attende che il processo figlio termini prima di permettere l'inserimento di un
    nuovo comando. Gestisce errori durante la creazione dei processi e
    l'esecuzione dei comandi, fornendo feedback appropriato all'utente.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/signal.h>
#include <unistd.h>
#include <string.h>

#define SIZE 100 // Dim. massima buffer

int main(void)
{
    char buf[SIZE];
    int pid, status;
    
    printf("%% ");
    while (fgets(buf, SIZE, stdin) != NULL)
    {
        buf[strlen(buf)-1] = 0; // Sostituisce ultimo carattere di newline con NULL
        pid = fork();
        
        
        if (pid < 0)
        {
            fprintf(stderr, "Errore nella fork\n");
            exit(1);
        }
        
        if (pid == 0)
        {
            if (execl(buf, buf, NULL) == -1)
            {
                fprintf(stderr, "Errore nel comando\n");
                exit(1);
            }
        }
        else
        {
            if (waitpid(pid, &status, 0) < 0)
            {
                fprintf(stderr, "Errore nella waitpid\n");
                exit(1);
            }
        }
        
        printf("%% ");
    }
    
    return 0;
    
}
