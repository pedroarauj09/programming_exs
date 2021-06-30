#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>

typedef void (*sighandler_t)(int);


// exemplo 
/*
void signal_handler(int sig){
    printf("received %d\n", sig);
    sleep(5);
    printf("handled %d\n",sig);
}


int main(){
    printf("pid: %d\n", getpid());
    signal(SIGUSR2,signal_handler);
    signal(SIGUSR1,signal_handler);
    pause();
    printf("Continua a execução...\n");

    return 0; 
}
*/


// 1
/*
int time = 0;
int nCtrlC = 0;


void signal_getCtrlC(int sig){
    printf("Fez %d ctrlC\n", nCtrlC);
    exit(0);
}

void signal_inc_time(int sig){
    time++;
    printf("tempo atual: %d\n",time);
    alarm(1);

}

void signal_printTime(int sig){
    printf("Passou %d segundos\n",time);
    nCtrlC++;
}

int main(){
    signal(SIGINT,signal_printTime);
    signal(SIGQUIT,signal_getCtrlC);
    signal(SIGALRM,signal_inc_time);
    
    alarm(1);
    while(1){
        // alarm(1) -> isso fazia com que resetasse o tempo e incrementa ele, de formar que o sigAlarm demore mais para ser ativado
        pause();
    };

    return 0; 
}
*/


//2
int main(int argc, char const *argv[]){
    char*palavra = strdup(argv[1]);
    pid_t pid[argc-2];
    int status;
    int i;
    for (i= 2; i < argc; i++)
    {
        if ((pid[i-2] = fork())==0){
            if(execlp("grep","grep",palavra,argv[i],NULL)<0){
                perror("grep");
            }
            exit(-1);
        }
    }
    int found = 0;
    int pid2;
    while(!found && (pid2=wait(&status))>0){
        if (WEXITSTATUS(status)>=0){
            switch(WEXITSTATUS(status)){
                case 0: 
                    printf("process %d found\n",pid2);
                    found++;
                    break;
                case 1: 
                    printf("process %d not found\n",pid2);    
                    break;

                default:
                    break;    
            }
        }
        else{
            printf("process %d was interrupted\n",pid2);
            
        }
    }
    if(found){
        for(i=2; i< argc; i++){
            if (pid[i-2]!=pid2){
                printf("matando o processo %d pois já achou\n", pid[i-2]);
                kill(pid[i-2], SIGKILL);
            }

        }
    }


    return 0;
}