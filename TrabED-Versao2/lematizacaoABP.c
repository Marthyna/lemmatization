/* ============  BIBLIOTECAS E HEADERS =============*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lematizacaoABP.h"

/* ============  FUNÇÕES DO TAD =============*/

//INSERÇÃO: recebe a raiz da ABP, uma palavra e seu lema
nodo* InsereABP(nodo *a, char* palavra, char* lema)
{
    // Variráveis pra uso de transferência de caracteres entre
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
        a->dir = NULL;                      //sub-árvores nulas
        a->esq = NULL;
    }
    //Se a palavra fornecida vier antes no alafabeto do que a palavra da raiz
    else if (ComparaStrings(palavra,a->palavra) < 0)
        //insere ela na SA esquerda da raiz
        a->esq = InsereABP(a->esq,palavra,lema);
    else //se a palavra fornecida vier depois da palavra da raiz na ordem alfabética
        //insere na SA direita
        a->dir = InsereABP(a->dir,palavra,lema);
    return a; //retorna a raiz da árvore
}

//BUSCA: recebe a raiz da árvore e uma palavra
nodo *achaNodo(nodo *arvore, char* palavra)
{
    nodo *atual = arvore;   //atual é a raiz da árvore
    int i;                  //var auxiliar
    while(atual)            //enquanto o nodo não for nulo
    {
        comp++;             //incrementa numero de comparações

        //i recebe o resultado da comparação entre a palavra do nó atual e a palavra dada
        i=ComparaStrings(atual->palavra,palavra);

        if (i == 0)         //se i=0, as palavras são iguais
        {
            comp++;         //fez mais uma comparação
            return atual;   //achou o nodo, retorna esse nodo
        }
        else                //senão, as palavras são diferentes
        {
            comp++;         //vai fazer outra comparação
            i=ComparaStrings(palavra,atual->palavra);
            if (i > 0)      //se a palavra vem depois da palavra do nó atual
                atual = atual->dir; //procura na SA direita
            else
                atual = atual->esq; //senão, procura na SA esquerda
        }
    }
    return NULL; //se não achar, retorna nodo nulo
}

//LEMA CORRESPONDENTE: recebe a raiz da árvore e uma palavra
char* pegaLema (nodo* arvore, char* palavra)
{
    nodo* a;        //para guardar o nodo
    char* lema;     //pra guardar o lema
    a = achaNodo(arvore,palavra);   //procura nodo com a palavra dada
    if(a)           //se achou o nodo
        lema = a->lema; //o lema é o lema do nodo
    else
        lema = palavra; //se não, o lema é a palavra em si (palavra não estava no dicionário)
    return lema;    //retorna o lema
}

//COMPARAÇÃO DE STRINGS: recebe duas strings
int ComparaStrings(char *str1, char *str2)
{
    int i = 0;      //posição nas strings
    //enquanto os caracteres forem iguais e nenhuma das strings chegou ao fim
    while(str1[i] == str2[i] && str1[i] != '\0' && str2[i] != '\0')
        i++;        //incrementa posição
    //se parou por chegar ao fim das duas strings, elas são iguais, retorna 0
    if(str1[i] == '\0' && str2[i] == '\0')
        return 0;
    //se parou por caracteres diferentes, compara eles
    else if(str1[i] > str2[i])  //se o char atual da string 1 é maior que o da string 2
        return 1;               //o str1 vem primeiro na ordem alfabetica, retorna 1
    else
        return -1;              //se não, o str2 vem primeiro na ordem alfabetica, retorna -1
}
