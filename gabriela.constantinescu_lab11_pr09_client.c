//Clientul ii transmite serverului un nume de director si primeste de la acesta lista tuturor fisierelor text din directorul respectiv,
//respectiv un mesaj de eroare daca directorul respectiv nu exista.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

//client
int main(int argc, char* argv[]) {
    char nume_dir[20];

    char* fifo = "./fifo1";
    //int res = mkfifo(fifo, 0666);
    //if (res == -1){
    //    perror("eroare mkfifo(): ");
    //    exit(EXIT_FAILURE);
    //}

    int fd = open(fifo, O_RDWR);
    if(fd == -1){
        perror("eroare open(): ");
        exit(EXIT_FAILURE);
    }

    printf("Scrie un nume de director: ");
    scanf("%s", nume_dir);
    write(fd, nume_dir, sizeof(nume_dir));
	//unlink(fifo);
	close(fd);
    return 0;
}
