#include <stdio.h>
#include <string.h>
#include "dicAbin.h"
#define TAMANHO 32
int main() {
    char pal[TAMANHO];
    Dicionario d;
    initDic(&d);
    printf("Insira uma palavras para inserir no dic:\n");
    scanf("%s",pal);
    while ((strncmp(pal, "Quit", 4))){
        acrescenta(&d,pal);
        scanf("%s",pal);
    }
    //printf("Ult palavra: %s\n", d.arvorePal->palavra);
    printf("Dic:\n");
    showPal(d.arvorePal);
    //putchar('\n');
    printf("Número de palavras: %d", d.nPal);
    putchar('\n');
    return 0;
}
