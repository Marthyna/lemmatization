#define MAX 50          //tamanho máximo das palavras e lemas
#define CHARMAX 1000    //número máximo de chars lidos em cada linha
struct TNodoA
{
    char palavra[MAX];
    char lema[MAX];
    struct TNodoA *esq; // filho esq
    struct TNodoA *dir; // filho dir
};
typedef struct TNodoA nodo;

extern int comp;        // variável global para guardar comparações feitas

nodo* InsereABP(nodo *a, char* palavra, char* lema);
nodo *achaNodo(nodo *arvore, char* palavra) ;
char* pegaLema (nodo* arvore, char* palavra);
int ComparaStrings(char *str1, char *str2);
