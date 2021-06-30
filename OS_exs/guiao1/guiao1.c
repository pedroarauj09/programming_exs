#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

/*
// 1 (copy content of a file to another)
int main(int argc, char*argv[]){
    int f1 = open(argv[1], O_RDONLY);
    int f2 = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, 0600);
    
    ssize_t readB = 0;
    ssize_t writeB = 0;
    char *buffer = malloc(sizeof (char) * BUFFER_SIZE);

    while((readB = read(f1, buffer, BUFFER_SIZE))>0){
     writeB += write(f2, buffer, readB);
    }


    close(f1);
    close(f2);
    free(buffer);

}
*/


// 2 (write in stdin and duplicate in stdout)
/*
int main(int argc, char*argv[]){
    ssize_t readB = 0;
    ssize_t writeB = 0;
    char *buffer = malloc(sizeof (char) * BUFFER_SIZE);

    while((readB = read(0, buffer, BUFFER_SIZE))>0){
     writeB += write(1, buffer, readB);
     
     
    }
    
    free(buffer);

    return 0;
}
*/

// 3 read some lines from file optimized
/*
int read_char(int fd, char *c){
    return read(fd, c,1);
}

ssize_t readln(int fd, char *buf, ssize_t sizeBuf){
    size_t res = 0;
    int i = 0;
    while(i< sizeBuf && (res = read_char(fd,&buf[i])) > 0 ){
        write(1, "+", 1);
        if (buf[i] == '\n'){
            i += res;
            return i;
        }
        i += res; 
    }
    return i;
}

int main(int argc, char*argv[]){
    int fd = open("file.txt", O_RDONLY);
    int res;
    char *buffer = malloc(sizeof(char)* BUFFER_SIZE);

    while((res = readln(fd,buffer,BUFFER_SIZE)) > 0 ){
        write(1,"\n",1);
        write(1,buffer, res);
    }
    write(1,"\n", 1);

    close(fd);
    return 0;

}
*/

