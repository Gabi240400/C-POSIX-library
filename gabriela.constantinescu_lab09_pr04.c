//Fie Pi procesul ce verifica dacă i este un divizor pentru N dat și determină
//ordinul de multiplicitate al acestui divizor.
//Lansând în execuție o structură adecvata de astfel de procese, să se
//descompună în factori primi numarul N dat.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    int N;
	printf("Scrie N: ");
    scanf("%d", &N);
	if(N <= 1){
		printf("Nu se poate realiza descompunerea in factori prim a numarului %d\n", N);
		return 0;
	}
    int i;
    int ord_mul;
    printf("Descompunerea numarului %d in factori primi este:\n", N);
    for(i=2; i<=N; i++){
        int pid = fork();
        if(pid == -1){
            perror("fork() a esuat");
            exit(EXIT_FAILURE);
        }
        if(pid == 0){
            ord_mul = 0;
            while (N%i == 0){
                N = N/i;
                ord_mul += 1;
            }
            exit(ord_mul);
        }
        int status;
        wait(&status);
        status = WEXITSTATUS(status);
        if(status)
            printf("%d ^ %d\n", i, status);
		while(status){
			N = N/i;
			status -= 1;
		}
    }
    return 0;
}
