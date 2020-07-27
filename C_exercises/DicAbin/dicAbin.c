#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "dicAbin.h"



void showPal(Palavras d){
    if (d){
        showPal(d->esq);
        printf("%s || %d\n",d->palavra,d->ocorr);
        showPal(d->dir);
    }
}



void initDic(Dicionario *d){
    d->arvorePal = NULL;
    d->nPal = 0;
}

int existePal(Palavras *d, char *pal){
    if ((*d) == NULL) return 0;
    else if (strcmp(pal,(*d)->palavra) == 0){
        (*d)->ocorr++;
        return 1;
    }
    else {
        if(strcmp(pal,(*d)->palavra) < 0){
            return existePal(&((*d)->esq), pal);
        }
        else return existePal(&((*d)->dir), pal);
    }
}

Palavras inserePal(Palavras d, char *pal){
    Palavras aux;
    if (!d){
        aux = malloc(sizeof(Palavra));
        aux->palavra = strdup(pal);
        aux->ocorr = 1;
        aux->esq = NULL;
        aux->dir = NULL;
        return aux;
    }
    else {
        if (strcmp(pal, d->palavra) > 0) d->dir = inserePal(d->dir,pal);
        else d->esq = inserePal(d->esq,pal);
    }
    return d;
}

void acrescenta(Dicionario *d, char *pal){
    if (existePal(&(d->arvorePal),pal) == 0){
        d->arvorePal = inserePal(d->arvorePal,pal);
        d->nPal++;
    }
}


