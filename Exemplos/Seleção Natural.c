#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define INT_MIN -2147483648
#define INT_MAX 2147483647


void retorna_Menor(int *vet, int N, int *menor, int *ind_menor){
  (* ind_menor) = N;
  (* menor) = INT_MIN;
  int i = 0;
  while((i < N) && (vet[i] == INT_MIN)) i++;
  if(i == N) return;

  (* ind_menor) = i;
  (* menor) = vet[i];
  i++;
  while(i < N){
    if((vet[i] != INT_MIN) && (vet[i] < (* menor))){
      (* menor) = vet[i];
      (* ind_menor) = i;
    }
    i++;
  }
}


int existeElemsDifInf(int *vet, int N){
  int i;
  for(i = 0; i < N; i++)
    if(vet[i] != INT_MIN) return 1;
  return 0;
}


void sel_natural(char *in, int TAM_MP, int TAM_R){
  int vmp[TAM_MP], vr[TAM_R];
  int i;

  //inicializa as memorias.
  for(i = 0; i < TAM_MP; i++) vmp[i] = INT_MIN;
  for(i = 0; i < TAM_R; i++) vr[i] = INT_MIN;

  FILE *fp;
  fp = fopen(in, "rt");
  if(!fp) exit(1);

  int aux, r;
  r = fscanf(fp, "%d", &aux);
  i = 0;
  //leitura dos elementos para a MP.
  while((i < TAM_MP) && (r == 1)){
    vmp[i++] = aux;
    r = fscanf(fp, "%d", &aux);
  }

  //criacao e abertura da primeira particao...
  FILE *fp_part;
  int ind = 1;
  char nome_part[51], buf[11];
  strcpy(nome_part, "part-sn");
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
      retorna_Menor(vmp, TAM_MP, &menor, &ind_menor);
      fprintf(fp_part, "%d\n", menor);
      vmp[ind_menor] = INT_MIN;
    }
    fclose(fp_part);
    fclose(fp);
    return;
  }

  int pos_livre_r = 0;
  while(r == 1){
    //se R está cheia, copia a MP, fecha a particao atual, cria e abre uma nova particao.
    if(pos_livre_r == TAM_R){
      pos_livre_r = 0;
      retorna_Menor(vmp, TAM_MP, &menor, &ind_menor);
      while(ind_menor != TAM_MP){
        fprintf(fp_part, "%d\n", menor);
        vmp[ind_menor] = INT_MIN;
        retorna_Menor(vmp, TAM_MP, &menor, &ind_menor);
      }
      fclose(fp_part);

      //copia de R para MP...
      if(TAM_R <= TAM_MP){
        int k;
        for(k = 0; k < TAM_R; k++){
           vmp[k] = vr[k];
           vr[k] = INT_MIN;
        }
        strcpy(nome_part, "\0");
        strcpy(nome_part, "part-sn");
        sprintf(buf, "-%d-", ind);
        strcat(nome_part, buf);
        strcat(nome_part, in);
        ind++;
        fp_part = fopen(nome_part, "wt");
        if(!fp_part) exit(1);

        //se MP > R, faça a copia do arquivo para a MP nas posicoes nao ocupadas por R...
        if(TAM_MP != TAM_R){
          int k = TAM_R;
          while(k < TAM_MP){
            vmp[k++] = aux;
            r = fscanf(fp, "%d", &aux);
            if(r != 1) break;
          }
          if(r != 1){
            while(k < TAM_MP) vmp[k++] = INT_MIN;
            //continue;
          }
        }
      }
    }
    //descobre-se o menor elemento da MP e grava-se na 
    //particao de saida.
    retorna_Menor(vmp, TAM_MP, &menor, &ind_menor);
    fprintf(fp_part, "%d\n", menor);

    //substitui o menor. Se o novo registro e menor que o 
    //elemento gravado, guarde-o em R. 
    if(aux < menor){
      while(aux < menor){
        vr[pos_livre_r++] = aux;
        r = fscanf(fp, "%d", &aux);
        if((r != 1) || (pos_livre_r == TAM_R)){
          vmp[ind_menor] = INT_MIN;
          break;
        }
      }
      if((r == 1) && (pos_livre_r != TAM_R)){
        vmp[ind_menor] = aux;
        //leitura do proximo elemento a entrar na particao.
        r = fscanf(fp, "%d", &aux);
      }
    } 
    else{
      vmp[ind_menor] = aux;
      //leitura do proximo elemento a entrar na particao.
      r = fscanf(fp, "%d", &aux);
    }
  }
  fclose(fp);

  for(i = 0; i < TAM_MP; i++){
    retorna_Menor(vmp, TAM_MP, &menor, &ind_menor);
    if(ind_menor == TAM_MP) break;
    fprintf(fp_part, "%d\n", menor);
    vmp[ind_menor] = INT_MIN;
  }
  fclose(fp_part);

  if(existeElemsDifInf(vr, TAM_R)){
    strcpy(nome_part, "\0");
    strcpy(nome_part, "part-sn");
    sprintf(buf, "-%d-", ind);
    strcat(nome_part, buf);
    strcat(nome_part, in);
    ind++;
    fp_part = fopen(nome_part, "wt");
    if(!fp_part) exit(1);

    int k;
    for(k = 0; k < TAM_R; k++){ 
      retorna_Menor(vr, TAM_R, &menor, &ind_menor);
      if(ind_menor == TAM_R) break;
      fprintf(fp_part, "%d\n", menor);
      vr[ind_menor] = INT_MIN;
    }
    fclose(fp_part);
  }
}


int main(void){
  int TAM_MP, TAM_R;
  char entrada[31];
  printf("Digite o nome do arquivo de entrada... ");
  scanf("%s", entrada);
  printf("Digite o tamanho de MP e de R... ");
  scanf("%d %d", &TAM_MP, &TAM_R);
  if((TAM_MP > 0) && (TAM_R > 0) && (TAM_MP >= TAM_R)) sel_natural(entrada, TAM_MP, TAM_R);
}
