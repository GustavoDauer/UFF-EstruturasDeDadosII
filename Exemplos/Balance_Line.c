#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct aluno{
  int mat;
  float cr;
} TAluno;

 
void balance_line(char* mestre, char *trans){
  FILE *fp_mestre = fopen(mestre, "r");
  if(!fp_mestre) exit(1);

  FILE *fp_trans = fopen(trans, "r");
  if(!fp_trans) exit(1);

  char erro[31], novo_mestre[31];
  strcpy(erro, "erro-");
  strcat(erro, mestre);  
  FILE *fp_erro = fopen(erro, "w");
  if(!fp_erro) exit(1);

  strcpy(novo_mestre, "novo-");
  strcat(novo_mestre, mestre);
  FILE *fp_novo_mestre = fopen(novo_mestre, "w");
  if(!fp_mestre) exit(1);

  int r, s;
  TAluno elem;
  int mat;
  char acao[2], campo[5], aux[5];

  r = fscanf(fp_mestre, "%d %f", &elem.mat, &elem.cr);
  s = fscanf(fp_trans, "%d %s", &mat, acao);
  while((r == 2) && (s == 2)){
    if(elem.mat == mat){
      if(strcmp(acao, "I") == 0){       //erro
        fscanf(fp_trans, "%s", campo);
        fprintf(fp_novo_mestre, "%d %.1f\n", elem.mat, elem.cr); 
        fprintf(fp_erro, "%d %s %s\n", mat, acao, campo);  
      }
      else if(strcmp(acao, "M") == 0){
        fscanf(fp_trans, "%s %s", campo, aux);
        fprintf(fp_novo_mestre, "%d %s\n", mat, aux); 
      }
      r = fscanf(fp_mestre, "%d %f", &elem.mat, &elem.cr);
      s = fscanf(fp_trans, "%d %s", &mat, acao);
    }
    else if (elem.mat < mat){           //copia para o novo mestre
      fprintf(fp_novo_mestre, "%d %.1f\n", elem.mat, elem.cr);
      r = fscanf(fp_mestre, "%d %f", &elem.mat, &elem.cr);
    }
    else{                               //trans e menor que mestre
      if(strcmp(acao, "I") == 0){       //inclusao de elemento
        fscanf(fp_trans, "%s", campo);
        fprintf(fp_novo_mestre, "%d %s\n", mat, campo); 
      }
      else if(strcmp(acao, "M") == 0){  //erro
        fscanf(fp_trans, "%s %s", campo, aux);
        fprintf(fp_erro, "%d %s %s %s\n", mat, acao, campo, aux); 
      }
      else fprintf(fp_erro, "%d %s\n", mat, acao); 
      s = fscanf(fp_trans, "%d %s", &mat, acao);
    }
  }  

  if(s == 2){       //acabou o mestre. Resto do trans para erro.
    while(s == 2){
      if(strcmp(acao, "I") == 0){       //inclusao de elemento
        fscanf(fp_trans, "%s", campo);
        fprintf(fp_novo_mestre, "%d %s\n", mat, campo); 
      }
      else if(strcmp(acao, "M") == 0){  //erro
        fscanf(fp_trans, "%s %s", campo, aux);
        fprintf(fp_erro, "%d %s %s %s\n", mat, acao, campo, aux); 
      }
      else fprintf(fp_erro, "%d %s\n", mat, acao); 
      s = fscanf(fp_trans, "%d %s", &mat, acao);
    }
  }

  if(r == 2){  //acabou o trans. Resto do mestre para novo_mestre
    fprintf(fp_novo_mestre, "%d %.1f\n", elem.mat, elem.cr);
    char lixo = fgetc(fp_mestre);
    while(1){
      char c = fgetc(fp_mestre);
      if(c == EOF) break;
      fputc(c, fp_novo_mestre);
    }
  }

  fclose(fp_mestre);
  fclose(fp_trans);
  fclose(fp_erro);
  fclose(fp_novo_mestre);
}


int main(int argc, char** argv){
  if(argc != 3) exit(1);
  balance_line(argv[1], argv[2]);
  return 0;
}
