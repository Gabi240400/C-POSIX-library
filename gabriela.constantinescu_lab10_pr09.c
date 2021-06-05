//Clientul ii transmite serverului un nume de director si primeste de la acesta lista tuturor fisierelor text din directorul respectiv,
//respectiv un mesaj de eroare daca directorul respectiv nu exista. 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    FILE *fp;
    char nume_dir[20];
    char nume_dir_copil[20];

    //fd[0] pt citire si fd[1] pt scriere
    int fd[2];
    int res = pipe(fd);

    //eroare pipe()
    if (res == -1) {
        perror("eroare pipe(): ");
        exit(EXIT_FAILURE);
    }

    int pid = fork();

    //eroare fork()
    if (pid == -1) {
        perror("eroare fork(): ");
        exit(EXIT_FAILURE);
    }

    //proces copil
    if (pid == 0) {
        close(fd[1]);
        read(fd[0], nume_dir_copil, sizeof(nume_dir_copil));
        char comanda[100];
        sprintf(comanda, "find %s -type f -exec file {} + | grep ASCII | cut -d ':' -f 1", nume_dir_copil);
        fp = popen(comanda, "r");
        char linie[50];
        while(fscanf(fp, "%s", linie) != EOF)
            printf("%s\n", linie);
        close(fd[0]);
        fclose(fp);
	exit(EXIT_SUCCESS);
    }
    close(fd[0]);

    printf("Scrie un nume de director: ");
    scanf("%s", nume_dir);
    write(fd[1], nume_dir, sizeof(nume_dir));

    int status;
    wait(&status);

    close(fd[1]);
    return 0;
}
