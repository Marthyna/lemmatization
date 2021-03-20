/* ============  BIBLIOTECAS E HEADERS =============*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lematizacaoABP.h"

/* ============  FUN��ES DO TAD =============*/

//INSER��O: recebe a raiz da ABP, uma palavra e seu lema
nodo* InsereABP(nodo *a, char* palavra, char* lema)
{
    // Varir�veis pra uso de transfer�ncia de caracteres entre
    // ponteiros de string e vetores de char
    int n = strlen(lema);
    int m = strlen(palavra);
    int i;
    int j;

    if(a == NULL)                           //se arvore nula
    {
        a = (nodo*)malloc(sizeof(nodo));    //aloca a raiz
        for(j=0; j<=m; j++)                 //preenche o vetor palavra
            a->palavra[j] = palavra[j];
        for(i=0; i<=n; i++)                 //preenche o vetor lema
            a->lema[i] = lema[i];
        a->dir = NULL;                      //sub-�rvores nulas
        a->esq = NULL;
    }
    //Se a palavra fornecida vier antes no alafabeto do que a palavra da raiz
    else if (ComparaStrings(palavra,a->palavra) < 0)
        //insere ela na SA esquerda da raiz
        a->esq = InsereABP(a->esq,palavra,lema);
    else //se a palavra fornecida vier depois da palavra da raiz na ordem alfab�tica
        //insere na SA direita
        a->dir = InsereABP(a->dir,palavra,lema);
    return a; //retorna a raiz da �rvore
}

//BUSCA: recebe a raiz da �rvore e uma palavra
nodo *achaNodo(nodo *arvore, char* palavra)
{
    nodo *atual = arvore;   //atual � a raiz da �rvore
    int i;                  //var auxiliar
    while(atual)            //enquanto o nodo n�o for nulo
    {
        comp++;             //incrementa numero de compara��es

        //i recebe o resultado da compara��o entre a palavra do n� atual e a palavra dada
        i=ComparaStrings(atual->palavra,palavra);

        if (i == 0)         //se i=0, as palavras s�o iguais
        {
            comp++;         //fez mais uma compara��o
            return atual;   //achou o nodo, retorna esse nodo
        }
        else                //sen�o, as palavras s�o diferentes
        {
            comp++;         //vai fazer outra compara��o
            i=ComparaStrings(palavra,atual->palavra);
            if (i > 0)      //se a palavra vem depois da palavra do n� atual
                atual = atual->dir; //procura na SA direita
            else
                atual = atual->esq; //sen�o, procura na SA esquerda
        }
    }
    return NULL; //se n�o achar, retorna nodo nulo
}

//LEMA CORRESPONDENTE: recebe a raiz da �rvore e uma palavra
char* pegaLema (nodo* arvore, char* palavra)
{
    nodo* a;        //para guardar o nodo
    char* lema;     //pra guardar o lema
    a = achaNodo(arvore,palavra);   //procura nodo com a palavra dada
    if(a)           //se achou o nodo
        lema = a->lema; //o lema � o lema do nodo
    else
        lema = palavra; //se n�o, o lema � a palavra em si (palavra n�o estava no dicion�rio)
    return lema;    //retorna o lema
}

//COMPARA��O DE STRINGS: recebe duas strings
int ComparaStrings(char *str1, char *str2)
{
    int i = 0;      //posi��o nas strings
    //enquanto os caracteres forem iguais e nenhuma das strings chegou ao fim
    while(str1[i] == str2[i] && str1[i] != '\0' && str2[i] != '\0')
        i++;        //incrementa posi��o
    //se parou por chegar ao fim das duas strings, elas s�o iguais, retorna 0
    if(str1[i] == '\0' && str2[i] == '\0')
        return 0;
    //se parou por caracteres diferentes, compara eles
    else if(str1[i] > str2[i])  //se o char atual da string 1 � maior que o da string 2
        return 1;               //o str1 vem primeiro na ordem alfabetica, retorna 1
    else
        return -1;              //se n�o, o str2 vem primeiro na ordem alfabetica, retorna -1
}
