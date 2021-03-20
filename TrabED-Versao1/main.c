/* ============  BIBLIOTECAS E HEADERS =============*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "lematizacaoAVL.h"

/* ============  VARIÁVEIS GLOBAIS =============*/
int comp = 0;

/* ============  MAIN =============*/
/* A main tem 2 parâmetros:
 argc: conta o nº de parâmetros
 argv[]: armazena as strings correspondentes aos parâmentros digitados*/
int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");   //para imprimir corretamente na tela os caracteres acentuados
    clock_t start, end;     //para contar o tempo decorrido

    FILE * dicionario;      //arquivos usados no programa
    FILE * entrada;
    FILE * saida;

    nodo *AVL = NULL;       //estrutura para armazenar dicionario
    int ok;                 //para balanceamento da AVL

    char *palavra, *lema;   //para armazenar as palavras/lemas lidos
    char linha[CHARMAX];    //linhas a serem lidas do arquivo
    char separador[] = {" ,.&*%\?!;/'@\"$#=><()][}{:\n\t"}; //símbolos considerados separadores

    //caso não seja passado o número esperado de parâmetros, erro
    if (argc != 4)
    {
        printf ("Numero incorreto de parametros.\n Para chamar o programa digite: exemplo <dicionario.txt> <arq_entrada> <arq_saida>\n");
        return 1;
    }
    else
    {
        dicionario = fopen(argv[1],"r");    //abre arquivo do dicionario
        if(dicionario == NULL)              //caso erro na abertura
        {
            printf("Erro ao abrir o arquivo dicionario");
            return 1;
        }
        else
        {
            saida = fopen (argv[3], "w");   //abre arquivo de saida
            start = clock();                //inicia a contagem do tempo

            //carrega dicionario pra estrutura
            while (fgets(linha,CHARMAX,dicionario)) //enquanto há linhas pra ler
            {
                palavra = strtok (linha, separador);    //pega o primeiro token da frase e armazena em palavra
                while (palavra != NULL)                 //enquanto não chegou no fim da linha
                {
                    lema = strtok(NULL,separador);      //pega o proximo token e armazena em lema
                    palavra = strlwr(palavra);          //passa ambos pra minúsculo
                    lema = strlwr(lema);
                    AVL = InsereAVL(AVL,palavra,lema,&ok); //insere o nodo com palavra e lema na AVL
                    palavra = strtok (NULL, separador); //pega próximo token
                }
            }

            entrada = fopen (argv[2], "r"); //abre arquivo de entrada

            if (entrada == NULL)            //erro na abertura
            {
                printf ("Erro ao abrir o arquivo de entrada");
                return 1;
            }
            else
            {
                //Gera arquivo de saída
                while (fgets(linha,CHARMAX,entrada))
                {
                    palavra = strtok (linha, separador); //lê um token pra palavra
                    while (palavra != NULL)              //enquanto não chegou ao fim da linha
                    {
                        lema = pegaLema(AVL,palavra);    //procura o lema correspondente na árvore
                        fprintf(saida,"%s ",lema);       //e o escreve no arquivo de saída
                        palavra = strtok (NULL, separador); //pega próximo token
                    }
                }
                printf("\nArquivo de saida gerado com sucesso.\n");

                end = clock();                           // finaliza contagem do tempo
                float miliseconds = (float)(end - start) / CLOCKS_PER_SEC * 1000; //calcula o tempo decorrido
                printf("Tempo: %.5f ms\n",miliseconds);
                printf("Comparacoes realizadas: %d", comp);
            }

            fclose (entrada); //fecha os arquivos
            fclose (saida);
            fclose (dicionario);
            return 0;
        }
    }
}


