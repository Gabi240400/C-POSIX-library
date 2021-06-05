#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	FILE* fp;
	FILE* fpw;

	//deschid fisierul pentru citire
    fp = fopen(argv[1], "r");

    //verific daca exista erori
    if (fp == NULL) {
        printf("Au aparut erori la deschiderea fisierului %s la citire\n", argv[1]);
        return 0;
    }

    //parcurg fisierul si calculez cate caractere are
    int nrCarac=0;
	char c;
    for (c = fgetc(fp); c != EOF; c = fgetc(fp))
        nrCarac = nrCarac + 1;

    //parcurg fisierul si pun in array-ul carac octetii fisierului
    char carac[nrCarac+1];
    int i=0;
    fseek(fp, 0, SEEK_SET);
    for (c = fgetc(fp); c != EOF; c = fgetc(fp)){
        carac[i]=c;
        i++;
    }
	carac[nrCarac]='\0';

    //inchid fisierul
	fclose(fp);

    //deschid fisierul pentru scriere
	fpw = fopen(argv[1], "w");

	//verific daca exista erori 
    if (fpw == NULL) {
        printf("Au aparut erori la deschiderea fisierului %s la scriere\n", argv[1]);
        return 0;
    }

    //parcurg array-ul carac invers si scriu caracterele acestuia in fisier
    for (i=nrCarac-2; i>=0; i--)
    	fputc(carac[i], fpw);
	fputc('\n',fpw);

    //inchid fisierul
    fclose(fpw);

	return 0;
}
