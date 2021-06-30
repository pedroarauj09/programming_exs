#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

/* chamadas ao sistema: defs e decls essenciais */
/* chamadas wait*() e macros relacionadas */
/*
pid_t getpid(void);
pid_t getppid(void);
pid_t fork(void);
void _exit(int status);
pid_t wait(int *status);
pid_t waitPID(pid_t pid, int *status, int options);
int WIFEXITED(int status); / macro /
int WEXITSTATUS(int status);
*/


// 3  SEQUENCIAL 
/*
int main(){
    pid_t pid;
    int num = 10;
    int status;

    for (int i = 0; i < num; i++)
    {
        if ((pid = fork())==0){
            printf("processo (%d) --> %d\n", i , getpid());
            sleep(3);
            exit(i);
        }
        else{
            pid_t espera = wait(&status);
            printf("o processo %d terminou, exit code(%d)\n", espera, WEXITSTATUS(status));
        }
    }
    return 0;
}
*/

// 4 PARALELO
/*
int main(){
    pid_t pid;
    int num = 10;
    int status;
    int i;
    for (i= 0; i < num; i++)
    {
        if ((pid = fork())==0){
            printf("processo (%d) --> %d\n", i , getpid());
            sleep(3);
            exit(i);
        }
    }
    for(i = 0; i < num; i++){    
        pid_t espera = wait(&status);
        printf("o processo %d terminou, exit code(%d)\n", espera, WEXITSTATUS(status));
    }
    return 0;
}
*/


// /*
int main(){
    pid_t pid;
    int num = 10;
    int status;

    for (int i = 0; i < num; i++)
    {
        if ((pid = fork())==0){
            printf("processo (%d) --> %d\n", i , getpid());
            
        }
        else{
            pid_t espera = wait(&status);
            printf("o processo %d terminou, exit code(%d)\n", espera, WEXITSTATUS(status));
            exit(i);
        }
    }
    
    return 0;
}
*/

//6
/*
int procura(int x , int i , int **matriz, int cols){
    int flag = 0;
    int j;
    for(j = 0; j < cols; j++){
        if (matriz[i][j] == x){
            printf("Processo %d : Achei o número %d na linha %d e coluna %d\n" ,getpid(),x,i,j);
            flag++;
        } 
    }
    return (flag > 0)? 1 : 0;
} 

int main(int argc, char * argv[]){
    if (argc < 2 ){
        printf("put some number");
        return -1;
    }
    pid_t pid;
    int find = atoi(argv[1]);
    int rows = 10;
    int cols = 10;
    int rand_max = 10;
    int status;
    int achou = 0;
    int **matriz;
    int i, j;

    matriz = (int **) malloc(sizeof(int*)*rows);
    
    for(i = 0; i < rows; i++)
    {
        matriz[i] = (int*) malloc(sizeof(int*)*cols);
        for(j= 0 ; j < cols; j++){
            matriz[i][j] = rand() % rand_max;
        }
    }

    
    
    
    for (i= 0; i < rows; i++)
    {
        if ((pid = fork())==0){
            exit(procura(find,i,matriz, cols));
        }
    }
    for(i = 0; i < rows; i++){    
        pid_t espera = waitpid(&status);
        if (status) achou ++; 
    }
    if (!(achou)) printf("Não há esse número na matriz\n");
    return 0;
}
*/


//7 , fazer o mesmo que o anterior mas aguardando os filhos ordenamente


int main(int argc, char * argv[]){
    if (argc < 2 ){
        printf("put some number");
        return -1;
    }
    pid_t pid;
    int find = atoi(argv[1]);
    int rows = 10;
    int cols = 10;
    int rand_max = 10;
    int status;
    int achou = 0;
    int **matriz;
    int i, j;
    int pids[rows];

    matriz = (int **) malloc(sizeof(int*)*rows);
    
    for(i = 0; i < rows; i++)
    {
        matriz[i] = (int*) malloc(sizeof(int*)*cols);
        for(j= 0 ; j < cols; j++){
            matriz[i][j] = rand() % rand_max;
        }
    }

    
    
    
    for (i= 0; i < rows; i++)
    {
        if ((pid = fork())==0){
            printf("[pid: %d] row: %d\n", getpid(), i);
            for (j=0 ; j < cols; j++){
                if(matriz[i][j]==find) _exit(i);
            }
            _exit(-1);
        }
        else{

            pids[i] = pid; // o fork no conteudo do pai retorna o pid do filho que acabou de criar
        }
    }
    for(i = 0; i < rows; i++){    
        pid_t espera = waitpid(pids[i],&status, 0);
        if (WIFEXITED(status)){
            if (WEXITSTATUS(status)<255)
            {
                printf("[pai]: processo %d acabou, achou o valor %d na linha %d\n", espera, find ,WEXITSTATUS(status));

            }
            else{
                printf("[pai]: processo %d acabou, achou nada\n", espera);

            }
        }
        else{
            printf("[pai:] processo %d acabou,  Alguma coisa deu errado\n", espera);
        }
    }
    
    return 0;
}