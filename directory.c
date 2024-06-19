/*
    Apri la current directory e verifica l’esistenza di una entry con il nome che corrisponde all’argomento inserito da riga di comando.
 
    Se trovata, stampa a video se la entry è una dir o link simbolico e, nel caso fosse una dir, aprila e conta quanti file hanno come letter finale ‘a’.
*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
        exit(0);
    
    DIR *directory;
    directory = opendir("."); //Apre directory corrente
    struct dirent *entry; //Puntatore a singole entry
    int found = 0;
    
    while((entry = readdir(directory)) != NULL)
    {
        if(strcmp(entry->d_name, argv[1]) == 0)
        {
            if(entry->d_type == DT_DIR)
                printf("Direcotry\n");
            else if(entry->d_type == DT_LNK)
                printf("Link simbolico\n");
            
            found++;
            break;
        }
    }
    
    if (found == 0)
        exit(0);
    
    if(entry->d_type == DT_DIR)
    {
        directory = opendir(entry->d_name);
        
        int len, count = 0;
        while((entry = readdir(directory)) != NULL)
        {
            len = strlen(entry->d_name);
            
            if(entry->d_type == DT_REG && entry->d_name[len-1] == 'a')
                count++;
        }
        
        printf("Num. elementi: %d\n", count);
    }
    return 0;
}
