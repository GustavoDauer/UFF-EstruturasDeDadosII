#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define INT_MIN -2147483648
#define INT_MAX 2147483647
//#define TAM_MP 6


typedef struct no{
  int chave; 
  char congelado;
} TNo;


void retorna_Menor(TNo *vet, int N, int *menor, int *ind_menor){
  (* ind_menor) = N;
  int i = 0;
  while(i < N){
    if(!vet[i].congelado){
      (* menor) = vet[i].chave;
      (* ind_menor) = i;
      break;
    }
    i++;
  }
  if(i == N) return;

  i = (* ind_menor) + 1;
  while(i < N){
    if((!vet[i].congelado) && (vet[i].chave < vet[(* ind_menor)].chave)){
      (* menor) = vet[i].chave;
      (* ind_menor) = i;
    }
    i++;
  }
}


int vet_Congelado(TNo *vet, int N){
  int i;
  for(i = 0; i < N; i++)
    if(!vet[i].congelado) return 0;
  return 1;
}


int existeUmCongDifInf(TNo *vet, int N){
  int i;
  for(i = 0; i < N; i++)
    if((vet[i].congelado) && (vet[i].chave != INT_MIN)) return 1;
  return 0;
}


void sel_subst(char *in, int TAM_MP){
  TNo vet[TAM_MP];
  int i;
  //inicializa a MP.
  for(i = 0; i < TAM_MP; i++){
    vet[i].congelado = 1;
    vet[i].chave = INT_MIN;
  }

  FILE *fp;
  fp = fopen(in, "rt");
  if(!fp) exit(1);

  int aux, r;
  r = fscanf(fp, "%d", &aux);
  i = 0;
  //leitura dos elementos para a MP.
  while((i < TAM_MP) && (r == 1)){
    vet[i].congelado = 0;
    vet[i++].chave = aux;
    r = fscanf(fp, "%d", &aux);
  }

  //criacao e abertura da primeira particao...
  FILE *fp_part;
  int ind = 1;
  char nome_part[51], buf[11];
  strcpy(nome_part, "part");
  sprintf(buf, "-%d-", ind);
  strcat(nome_part, buf);
  strcat(nome_part, in);
  ind++;
  fp_part = fopen(nome_part, "wt");
  if(!fp_part) exit(1);

  int menor, ind_menor;
  //se o arquivo e menor que a MP, entre no if a seguir 
  //para guardar as informacoes na particao.
  if(r != 1){
    int j = 0;
    while(j < i){
      j++;
      retorna_Menor(vet, TAM_MP, &menor, &ind_menor);
      fprintf(fp_part, "%d\n", menor);
      vet[ind_menor].chave = INT_MIN;
      vet[ind_menor].congelado = 1;
    }
    fclose(fp_part);
    fclose(fp);
    return;
  }

  while(r == 1){
    //se a MP esta congelada, fecha-se a particao atual,
    //descongela-se a MP, cria e abre uma nova particao.
    if(vet_Congelado(vet, TAM_MP)){
      fclose(fp_part);
      int k;
      for(k = 0; k < TAM_MP; k++) vet[k].congelado = 0;
      strcpy(nome_part, "\0");
      strcpy(nome_part, "part");
      sprintf(buf, "-%d-", ind);
      strcat(nome_part, buf);
      strcat(nome_part, in);
      ind++;
      fp_part = fopen(nome_part, "wt");
      if(!fp_part) exit(1);
    }
 
    //descobre-se o menor elemento da MP e grava-se na 
    //particao de saida.
    retorna_Menor(vet, TAM_MP, &menor, &ind_menor);
    fprintf(fp_part, "%d\n", menor);
    printf("%d %s\n", menor, nome_part);

    //substitui o menor. Se o novo registro e menor que o 
    //elemento gravado, congele-o. 
    vet[ind_menor].chave = aux;
    if(aux < menor) vet[ind_menor].congelado = 1;

    //leitura do proximo elemento a entrar na particao.
    r = fscanf(fp, "%d", &aux);
  }
  fclose(fp);

  printf("\n");
  for(i = 0; i < TAM_MP; i++){
    retorna_Menor(vet, TAM_MP, &menor, &ind_menor);
    if(ind_menor == TAM_MP) break;
    fprintf(fp_part, "%d\n", menor);
    vet[ind_menor].chave = INT_MIN;
    vet[ind_menor].congelado = 1;
    printf("FECHANDO PART: %d %s\n", menor, nome_part);
  }
  fclose(fp_part);

  if(existeUmCongDifInf(vet, TAM_MP)){
    int k;
    for(k = 0; k < TAM_MP; k++) 
      if(vet[k].chave != INT_MIN)
        vet[k].congelado = 0;

    strcpy(nome_part, "\0");
    strcpy(nome_part, "part");
    sprintf(buf, "-%d-", ind);
    strcat(nome_part, buf);
    strcat(nome_part, in);
    ind++;
    fp_part = fopen(nome_part, "wt");
    if(!fp_part) exit(1);

    printf("\n");
    for(k = 0; k < TAM_MP; k++){ 
      retorna_Menor(vet, TAM_MP, &menor, &ind_menor);
      if(ind_menor == TAM_MP) break;
      fprintf(fp_part, "%d\n", menor);
      vet[ind_menor].chave = INT_MIN;
      vet[ind_menor].congelado = 1;
      printf("ULTIMA PART: %d %s\n", menor, nome_part);
    }
    fclose(fp_part);
  }
}


int main(void){
  char entrada[31];
  printf("Digite o nome do arquivo de entrada... ");
  scanf("%s", entrada);
  printf("Digite o tamanho... ");
  int TAM_MP;
  scanf("%d", &TAM_MP); 
  sel_subst(entrada, TAM_MP);
}
