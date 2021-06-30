#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

// 3  : cria um programa que imprime o que é passado , passa como executavel: imprime
/*
int main (int argc, char** argv){
    for(int i = 0; i < argc; i++){
        write(1,argv[i],strlen(argv[i]));
    }
 }
*/
// 4  : chama o programa anterior 
/*
int main (int argc, char** argv){
    char *exec_arg [] = {"ola", "tudooo", "bem?",NULL};
    int ret = execv(argv[1],exec_arg);
    perror("Algo de errado aconteceu\n");
    return 0;
}
*/
// Fork + exec
int main (int argc, char** argv){
    //char *exec_arg [] = {"/../bin/ls", "-l", NULL};
    if (fork()==0){
        execlp("cat","cat",">", "out.txt", NULL);
        //execv("/../bin/ls",exec_arg);
        perror("Algo de errado aconteceu\n");
        _exit(0);
    }else{
        int status;
        wait(&status);
        printf("fork e exec deu bom\n");
    }
    return 0;
}

