
#ifndef DICABIN_DICABIN_H
#define DICABIN_DICABIN_H

typedef struct aBin{
    char* palavra;
    int ocorr;
    struct aBin *esq,*dir;}
*Palavras, Palavra;

typedef struct dic{
    Palavras arvorePal;
    int nPal;
}
Dicionario;

void initDic(Dicionario *d);
int existePal(Palavras *d, char *pal);
Palavras inserePal(Palavras d, char *pal);
void acrescenta(Dicionario *d, char *pal);
void showOcor(Palavras d);
void showPal(Palavras d);

#endif //DICABIN_DICABIN_H
