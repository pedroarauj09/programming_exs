#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>


//cliente

int main(){
    int fd;
    if(fd=open("log.txt",O_WRONLY)== -1){
            perror("open");
    }
    int bytes_read;
    char buf[2048];
    int i = 0;
    setbuf(stdout,NULL);
    while((bytes_read = read(0,buf,2048))>0  && i < 5){
        write(fd, buf, bytes_read);
        i++;
    }

    close(fd);
    return 0;
}



// servidor
/*
int main(){
    int bytes_read;
    char buf[2048];
    if(mkfifo("log.txt", 0666)==-1){
        perror("mkfifo");
    }

    int fd, fd2, fich;
    if(fd=open("log.txt",O_RDONLY)== -1){
        perror("open");
    }
    if(fd2=open("log.txt",O_WRONLY)== -1){
        perror("open");
    }
    if(fich=open("fich.txt",O_WRONLY | O_CREAT | O_TRUNC, 0666)== -1){
        perror("open");
        return -1;
    }

    bzero(buf,2048);
    setbuf(stdout,NULL);
    while((bytes_read = read(fd,buf,2048))>0){
        write(fich, buf, bytes_read);
    }

    close(fd);
    close(fd2);
    close(fich);
}
*/
