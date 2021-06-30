#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>


// 1
/*
int main (int argc, char** argv){
    int res = 0;
    int input_fd = open("etc/passwd",O_RDONLY);
    int output_fd = open("out.txt",O_CREAT | O_TRUNC | O_WRONLY, 0666);
    int error_fd = open("erro.txt",O_CREAT | O_TRUNC | O_WRONLY, 0666);

    res = dup2(input_fd,0);
    close(input_fd);
    res = dup2(output_fd,1);
    close(output_fd);
    res = dup2(error_fd,2);
    close(error_fd);

    int read_res;
    char buffer;
    char line[1024];
    int i = 0;

    setbuf(stdout,NULL); // desativa o buffer de memória( aquele que o guarda os printfs para serem escritos depois)
    while((read_res = read(0, &buffer,1)) != 0){
        line[i] = buffer;
        i++;

        if(buffer == '\n'){
            write(1,line,i); // escreve a linha que leu do file etc/passwd no arquivo out.txt
            write(2, line, i); // escreve tbm no arquivo erro.txt
        
            printf("hello..\n"); // como foi desativado no setbuf ele vai imprimir junto com o write da linha 34
            // fflush(stdout) (opção para forçar o buffer de memória escrever oq têm nele)
        }
    }

    return 0;
}
*/


//2

int main (int argc, char** argv){
    int res = 0;
    int input_fd = open("file.txt",O_RDONLY);
    int output_fd = open("out.txt",O_CREAT | O_TRUNC | O_WRONLY, 0666);
    int error_fd = open("erro.txt",O_CREAT | O_TRUNC | O_WRONLY, 0666);

    res = dup2(input_fd,0);
    close(input_fd);
    res = dup2(output_fd,1);
    close(output_fd);
    res = dup2(error_fd,2);
    close(error_fd);

    pid_t pid;
    int status;
    if ((pid =fork())==0){
        //codigo processo filho (mantem os files descriptors)
        int read_res;
        char buffer;
        char line[1024];
        int i = 0;

        setbuf(stdout,NULL); // desativa o buffer de memória( aquele que o guarda os printfs para serem escritos depois)
        while((read_res = read(0, &buffer,1)) != 0){
            line[i] = buffer;
            i++;

            if(buffer == '\n'){
                write(1,line,i); // escreve a linha que leu do file etc/passwd no arquivo out.txt
                write(2, line, i); // escreve tbm no arquivo erro.txt

                printf("hello..\n"); // como foi desativado no setbuf ele vai imprimir junto com o write da linha 34
                // fflush(stdout) (opção para forçar o buffer de memória escrever oq têm nele)
            }
        }
    }
    else{
        //codigo processo pai
        pid_t terminou = wait(&status);
        if(WIFEXITED(status)){
            printf("o filho retornou legal %d\n", WEXITSTATUS(status));
        }
        else{
            perror("deu algum pau\n");
        }
    }

    return 0;
}


//3
/*
int main (int argc, char** argv){
    int res = 0;
    int input_fd = open("file.txt",O_RDONLY);
    int output_fd = open("out.txt",O_CREAT | O_TRUNC | O_WRONLY, 0666);
    int error_fd = open("erro.txt",O_CREAT | O_TRUNC | O_WRONLY, 0666);

    res = dup2(input_fd,0);
    close(input_fd);
    res = dup2(output_fd,1);
    close(output_fd);
    res = dup2(error_fd,2);
    close(error_fd);

    setbuf(stdout,NULL);
    res = execlp("wc", "wc", NULL); // mantem os fds ao executar este prog, e vai escrever no arquivo out.txt
    return 0;

}
*/

//4
/*
int main (int argc, char** argv){

    int res = 0;
    int commandindex = 1;
    char command[1024];

    bzero(command,1024); // limpa o array
    setbuf(stdout,NULL);
     
    if (!strcmp(argv[commandindex],"-i")){
        int input_fd = open(argv[commandindex+1],O_RDONLY);
        res = dup2(input_fd,0);
        close(input_fd);

        commandindex+=2;
    }
    if (!strcmp(argv[commandindex],"-o")){ 
        int output_fd = open(argv[commandindex+1],O_CREAT | O_TRUNC | O_WRONLY, 0666);
        res = dup2(output_fd,1);
        close(output_fd);

        commandindex+=2;
    }
    while (commandindex<argc){
        strcat(command, argv[commandindex]);
        strcat(command," ");
        commandindex++;
    }
    
    system(command);
    return 0;

}
*/
