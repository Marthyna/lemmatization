#define MAX 50          //tamanho m�ximo das palavras e lemas
#define CHARMAX 1000    //n�mero m�ximo de chars lidos em cada linha
struct TNodoA
{
    char palavra[MAX];
    char lema[MAX];
    struct TNodoA *esq; // filho esq
    struct TNodoA *dir; // filho dir
};
typedef struct TNodoA nodo;

extern int comp;        // vari�vel global para guardar compara��es feitas

nodo* InsereABP(nodo *a, char* palavra, char* lema);
nodo *achaNodo(nodo *arvore, char* palavra) ;
char* pegaLema (nodo* arvore, char* palavra);
int ComparaStrings(char *str1, char *str2);
