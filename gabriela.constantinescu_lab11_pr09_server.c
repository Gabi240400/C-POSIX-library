//Clientul ii transmite serverului un nume de director si primeste de la acesta lista tuturor fisierelor text din directorul respectiv,
//respectiv un mesaj de eroare daca directorul respectiv nu exista.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

//server
int main(int argc, char* argv[]) {
    FILE *fp;
    char nume_dir_copil[20];

	char* fifo = "./fifo1";

    int fd = open(fifo, O_RDWR);
    if(fd == -1){
        perror("eroare open(): ");
        exit(EXIT_FAILURE);
    }

    read(fd, nume_dir_copil, sizeof(nume_dir_copil));
    char comanda[100];
    sprintf(comanda, "find %s -type f -exec file {} + | grep ASCII | cut -d ':' -f 1", nume_dir_copil);
    fp = popen(comanda, "r");
    char linie[50];
    while(fscanf(fp, "%s", linie) != EOF)
        printf("%s\n", linie);

    pclose(fp);
	close(fd);
    //unlink(fifo);
    return 0;
}
