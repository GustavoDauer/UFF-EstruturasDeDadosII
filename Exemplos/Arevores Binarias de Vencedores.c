#include <stdio.h>
#include <stdlib.h>

#define INT_MAX 2147483647

typedef struct no{
  int chave;
  char *nome;
  FILE *fp;
} TNo;


int pot(int n, int base){
  int resp = 1;
  while(resp < n) resp *= base;
  if (resp == n) return 1;
  return 0;
}


int prox_pot(int n, int base){
  int resp = 1;
  while(resp < n) resp *= base;
  return resp;
}


void intercala(TNo *heap, int n_heap, int n, int n_lido, char *saida){
  int i, j = 1;

  //abertura de arquivos e preenchimento de chaves
  for(i = n; i < n_heap; i++){
    if(j <= n_lido){
      heap[i].fp = fopen(heap[i].nome, "r");
      if(!heap[i].fp) exit(1);
      fscanf(heap[i].fp, "%d", &heap[i].chave);
      j++;
    }
  }

  //preenchimento inicial das chaves dos nos intermediarios
  for(i = n_heap - 1; i > 1; i = i - 2){
    int menor;
    if(heap[i].chave < heap[i - 1].chave) menor = heap[i].chave;
    else menor = heap[i - 1].chave;
    heap[i/2].chave = menor;
  }

  //abertura do arquivo de saida
  FILE *fp_saida = fopen(saida, "w");
  if(!fp_saida) exit(1);

  while(heap[1].chave != INT_MAX){
    //escrita do menor atual
    fprintf(fp_saida, "%d\n", heap[1].chave);

    //encontro do caminho do menor atual: O(log n)
    i = 1;
    while((2 * i) < n_heap){
      int esq = 2 * i;
      int dir = 2 * i + 1;
      if(heap[i].chave == heap[esq].chave) i = esq;
      else i = dir;
    }

    //leitura da nova chave para substituicao do menor atual
    int r = fscanf(heap[i].fp, "%d", &heap[i].chave);
    if (r != 1) heap[i].chave = INT_MAX;

    //atualizacao da arvore: O(log n)
    while(i > 1){
      int pai = i / 2;
      int esq = 2 * pai;
      int dir = 2 * pai + 1;

      if(heap[esq].chave < heap[dir].chave) heap[pai].chave = heap[esq].chave;
      else heap[pai].chave = heap[dir].chave;

      i = pai;
    }
  }

  //fechamento de arquivos
  fclose(fp_saida);
  j = 1;
  for(i = n; i < n_heap; i++)
    if(j <= n_lido){ 
      fclose(heap[i].fp);
      j++;
    }  
}

int main(void){
  while(1){
    printf("Digite n... ");
    int n;
    scanf("%d", &n);
    if(n <= 0) return 0;

    int n_heap, n_lido = n;
    if(!pot(n,2)) n = prox_pot(n, 2);
    n_heap = n * 2;

    TNo heap[n_heap];
    int i;
    for(i = 0; i < n_heap; i++){
      heap[i].fp = NULL;
      heap[i].nome = NULL;
      heap[i].chave = INT_MAX; 
    }

    int j = 1;
    for(i = n; i < n_heap; i++){
      if(j <= n_lido){
        printf("Digite o nome do arquivo %d a ser intercalado... ", j++);
        heap[i].nome = (char *) malloc(sizeof(char) * 31);
        scanf("%s", heap[i].nome);
      }
    }

    char saida[31];
    printf("Digite o nome do arquivo de saida... ");
    scanf("%s", saida);
    intercala(heap, n_heap, n, n_lido, saida);

    j = 1;
    for(i = n; i < n_heap; i++){
      if(j <= n_lido) free(heap[i].nome);
    }

  }
}
