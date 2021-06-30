#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>


//1
/*
int main(int argc, char const *argv[])
{
    int p[2];
    char line[] = "olaa\n";
    int res;
    char buffer[20];
    int status;

    if (pipe(p) == -1){
        perror("pipe nao deu bom\n");
        return -1;
    }

    switch(fork()){
        case -1:
            perror("Fork nao deu bom\n");
            return -1;

        case 0:
            //codigo do filho 
            //fechar extremidade de escrita pois irá fazer leitura
            close(p[1]);

            //ler do pipe
            res = read(p[0], &buffer, sizeof(buffer));
            printf("[FILHO]: read %s from pipe ; res = %d\n", buffer, res);

            //fechar a extremidade de leitura 
            close(p[0]);
            _exit(0);

        default:
            //codigo do pai
            //fechar extremidade de leitura pois irá fazer escrita

            close(p[0]);

            //escrever pipe

            res = write(p[1], line, strlen(line));
            printf("o pai já escreveu\n");
            
            // fechar a extremidade de escrita
            close(p[1]);

            wait(&status);


    }
*/

//2
/*
int main(int argc, char const *argv[])
{
    int p[2];
    char *line[] = {"olaa\n","oppa\n"};
    int res;
    char buffer;
    int status;

    if (pipe(p) == -1){
        perror("pipe nao deu bom\n");
        return -1;
    }

    switch(fork()){
        case -1:
            perror("Fork nao deu bom\n");
            return -1;

        case 0:
            //codigo do filho 
            //fechar extremidade de escrita pois irá fazer leitura
            close(p[1]);

            //ler do pipe
             while(read(p[0], &buffer, 1)){
                printf("[FILHO]: read %c from pipe ; res = %d\n", buffer, res);
             }
            //fechar a extremidade de leitura 
            close(p[0]);
            _exit(0);

        default:
            //codigo do pai
            //fechar extremidade de leitura pois irá fazer escrita

            close(p[0]);

            //escrever pipe

            for (int i = 0 ; i < 2; i++){
                res = write(p[1], line[i], strlen(line[i]));
            }
            // fechar a extremidade de escrita
            printf("o pai já escreveu\n");
            close(p[1]);

            wait(&status);


    }




    return 0;
}
*/

//4
/*
int main(int argc, char const *argv[])
{
    int p[2];
    int res;
    char buffer;
    int status;

    if (pipe(p) == -1){
        perror("pipe nao deu bom\n");
        return -1;
    }

    switch(fork()){
        case -1:
            perror("Fork nao deu bom\n");
            return -1;

        case 0:
            //codigo do filho 
            //fechar extremidade de leitura pois irá fazer escrita
            close(p[0]);

            dup2(p[1],1);
            close(p[1]);

            res = execlp("ls","ls","/etc",NULL);         
            //fechar a extremidade de leitura 
            _exit(0);

        default:
            //codigo do pai
            //fechar extremidade de escrita pois irá fazer leitura
            

            close(p[1]);

            //ler pipe
            dup2(p[0],0);
            close(p[0]);

            wait(&status);
            res = execlp("wc", "wc","-l",NULL);
            
            // fechar a extremidade de escrita
            //printf("o pai já leu\n");



    }




    return 0;
}
*/

//5

//parsing do comando + exec(vp)
int exec_command(char* arg){
    char* exec_args[10];
    char *string;
    int exec_ret = 0;
    int i = 0;

    //copy string
    char *comand = strdup(arg);

    //parse string
    string = strtok(comand, " ");

    while (string != NULL){
        exec_args[i] = string;
        string = strtok (NULL, " ");
        i++;
    }
    exec_args[i] = NULL;
    exec_ret = execvp(exec_args[0],exec_args);

    return exec_ret;
}


int main(int argc, char const *argv[])
{
    int p[2];
    int res;
    char buffer;
    int status;

    for(int c = 0; c < number_of_commands; c++){
        if(c==0){
            if (pipe(p[c]!=0))
        }
    }




    return 0;
}
