/* ============  BIBLIOTECAS E HEADERS =============*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lematizacaoAVL.h"

/* ============  FUN��ES DO TAD =============*/

// ROTA��ES: recebem a raiz da �rvore e retornam a raiz da �rvore rotacionada
nodo* rotacao_direita(nodo* p)
{
    nodo *u;
    u = p->esq;         //u guarda a SA esq da raiz
    p->esq = u->dir;    //a nova SA esq da raiz � a SA dir da antiga SA esq
    u->dir = p;         //a nova SA dir da antiga SA esq � a propria raiz
    p->FB = 0;          //fator de balanceamento da raiz vira 0
    p = u;              //a nova raiz � a antiga SA esq
    return p;
}

nodo* rotacao_esquerda(nodo *p)
{
    nodo *z;
    z = p->dir;         //z guarda a SA dir da raiz
    p->dir = z->esq;    //a nova SA dir da raiz � a SA esq da antiga SA dir
    z->esq = p;         //a nova SA esq da antiga SA dir � a pr�pria raiz
    p->FB = 0;          //fator de balanceamento da raiz vira 0
    p = z;              //nova raiz � a antiga SA dir
    return p;
}

nodo* rotacao_dupla_direita (nodo* p)
{
    nodo *u, *v;
    u = p->esq;                 //u � a SA esq da raiz
    v = u->dir;                 //v � a SA dir de u
    u->dir = v->esq;            //nova SA dir de u � a SA esq de v
    v->esq = u;                 //nova SA esq de v � u
    p->esq = v->dir;            //nova SA esq da raiz � a SA dir de v
    v->dir = p;                 //nova SA dir de v � a raiz
    if (v->FB == 1) p->FB = -1; //se o fator de balanceamento de v era 1, o da raiz vira -1
    else p->FB = 0;             //sen�o, o da raiz vira 0
    if (v->FB == -1) u->FB = 1; //se era -1, o de u vira 1
    else u->FB = 0;             //senao, vira 0
    p = v;                      //nova raiz � v
    return p;
}

nodo* rotacao_dupla_esquerda (nodo *p)
{
    nodo *z, *y;
    z = p->dir;                 //z recebe a SA dir da raiz
    y = z->esq;                 //y recebe a SA esq de z
    z->esq = y->dir;            //nova SA esq de z � a SA dir de y
    y->dir = z;                 //nova SA dir de y � z
    p->dir = y->esq;            //nova SA dir da raiz � a SA esq de y
    y->esq = p;                 //nova SA esq de y � a raiz
    if (y->FB == -1) p->FB = 1; //se o FB de y for -1, o da raiz vira 1
    else p->FB = 0;             //sen�o vira 0
    if (y->FB == 1) z->FB = -1; //se for 1, o de z vira -1
    else z->FB = 0;             //sen�o vira 0
    p = y;                      //y � a nova raiz
    return p;
}

//BALANCEAMENTO: recebe a raiz e a flag de balanceamento
//Caso 1: inser��o � esquerda desbalanceou a AVL
nodo* Caso1 (nodo *a, int *ok)
{
    nodo *z;
    z = a->esq;                 //z recebe a SA esquerda da raiz
    if (z->FB == 1)             //se a SA tinha FB 1
        a = rotacao_direita(a); //faz uma rota��o pra direita
    else
        a = rotacao_dupla_direita(a); //se tinha FB maior, faz uma rota��o dupla direita
    a->FB = 0;                  //zera o FB da raiz
    *ok = 0;                    //zera flag de balanceamento
    return a;
}

//Caso 2: inser��o � direita desbalanceou a AVL
nodo* Caso2 (nodo *a, int *ok)
{
    nodo *z;
    z = a->dir;                 //z recebe a SA direita da raiz
    if (z->FB == -1)            //se FB da SA direita era -1
        a = rotacao_esquerda(a);//faz uma rota��o pra esquerda
    else
        a = rotacao_dupla_esquerda(a);//se era menor q -1, faz uma rota��o dupla esquerda
    a->FB = 0;                  //zera o FB da raiz
    *ok = 0;                    //zera flag de balanceamento
    return a;
}

//INSER��O: recebe a raiz da AVL, uma palavra, seu lema e a flag de balanceamento
nodo* InsereAVL(nodo *a, char* palavra, char* lema, int *ok)
{
    // Varir�veis pra uso de transfer�ncia de caracteres entre
    // ponteiros de string e vetores de char
    int n = strlen(lema);
    int m = strlen(palavra);
    int i;
    int j;

    if(a == NULL)    //se arvore nula
    {
        a = (nodo*)malloc(sizeof(nodo));    //aloca a raiz
        for(j=0; j<=m; j++)                 //preenche o vetor palavra
            a->palavra[j] = palavra[j];
        for(i=0; i<=n; i++)                 //preenche o vetor lema
            a->lema[i] = lema[i];
        a->dir = NULL;                      //sub-�rvores nulas
        a->esq = NULL;
        a->FB = 0;                          //zera o FB
        *ok = 1;                            //flag de balanceamento ligada
    }
    //Se a palavra fornecida vier antes no alafabeto do que a palavra da raiz
    else if (ComparaStrings(palavra,a->palavra) < 0)
    {
        //insere ela na SA esquerda da raiz
        a->esq = InsereAVL(a->esq,palavra,lema,ok);
        if (*ok)            //se a flag de balanceamento est� ligada, realiza o balanceamento
        {
            switch (a->FB)
            {
            case -1:        //se o FB da raiz era -1, SA esquerda tinha um filho a menos que a direita
                a->FB = 0;  //agora as SA's est�o iguais
                *ok = 0;    //balanceou, desliga a flag
                break;
            case 0:         //se o FB era 0, as SA's estavam iguais
                a->FB = 1;  //agora a SA esquerda tem um filho a mais
                break;
            case 1:         //se o FB era 1, SA esquerda j� tinha um filho a mais que a direita
                a=Caso1(a,ok); //desbalanceou, analizar qual rota��o fazer
                break;
            }
        }
    }
    else //se a palavra fornecida vier depois da palavra da raiz na ordem alfab�tica
    {
        //insere na SA direita
        a->dir = InsereAVL(a->dir,palavra,lema,ok);
        if (*ok) //realiza procedimento de balanceamento an�logo ao de inser��o � esquerda
        {
            switch (a->FB)
            {
            case 1:
                a->FB = 0;
                *ok = 0;
                break;
            case 0:
                a->FB = -1;
                break;
            case -1:
                a = Caso2(a,ok);
                break;
            }
        }
    }
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
