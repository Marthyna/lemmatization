#define MAX 64      //tamanho máximo das palavras e lemas
#define CHARMAX 1000   //número máximo de chars lidos em cada linha
struct TNodoA
{
    char palavra[MAX];
    char lema[MAX];
    struct TNodoA *esq; // filho esq
    struct TNodoA *dir; // filho dir
    int FB;             // fator de balanceamento
};
typedef struct TNodoA nodo;

extern int comp;        // variável global para guardar comparações feitas

nodo* rotacao_direita(nodo* p);
nodo* rotacao_esquerda(nodo *p);
nodo* rotacao_dupla_direita (nodo* p);
nodo* rotacao_dupla_esquerda (nodo *p);
nodo* Caso1 (nodo *a, int *ok);
nodo* Caso2 (nodo *a, int *ok);
nodo* InsereAVL(nodo *a, char* palavra, char* lema, int *ok);
nodo *achaNodo(nodo *arvore, char* palavra) ;
char* pegaLema (nodo* arvore, char* palavra);
int ComparaStrings(char *str1, char *str2);
