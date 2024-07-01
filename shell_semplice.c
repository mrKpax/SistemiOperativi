/*
    Questo programma agisce come una shell molto semplice.
    Ciclicamente stampa un prompt %, legge un comando inserito dall'utente dopo il prompt e crea un nuovo figlio che esegue tale comando. Poi ne aspetta la terminazione.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/signal.h>
#include <unistd.h>
#include <string.h>


int main(void)
{
    char buf[512];
    int pid, status;
    
    printf("%% "); //prompt
    
    while (fgets(buf, 512, stdin) != NULL)
    {
        buf[strlen(buf) -1] = 0; //sostituisce newline con NULL
        if ((pid = fork()) < 0)
        {
            fprintf(stderr, "Errore\n");
            exit(-1);
        }
        else if (pid == 0) //figlio
        {
            if (execlp(buf, buf, (char *) 0) == -1)
            {
                printf("Errore, impossibile eseguire %s\n", buf);
                exit(-1);
            }
            exit(0);
        }
        if ((pid = waitpid(pid, &status, 0)) < 0) //padre
        {
            printf("Errore di sistema: waitpid\n");
            exit(1);
        }
        printf("%% ");
    }
    exit(0);
}
