#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no{
  int chave, prox;
  char status;        //1 - ocupado e 0 - liberado
}TNo;


int hash(int ch, int m){
  return (ch % m);
}


void inicializa(char *nome, int m){
  FILE *fp = fopen(nome, "wb");
  if(!fp) exit(1);

  int elem = -1, i;
  for(i = 0; i < m; i++) fwrite(&elem, sizeof(int), 1, fp);

  fclose(fp);
}


void insere(char *nome, int ch, int m){
  FILE *fp = fopen(nome, "rb+");
  if(!fp) exit(1);

  int h = hash(ch, m), p;
  TNo elem;
  elem.chave = ch;
  elem.status = 1; 
  fseek(fp, (h * sizeof(int)), SEEK_SET);
  fread(&p, sizeof(int), 1, fp);

  int ant, q;
  ant = q = -1;
  TNo aux;
  while(p != -1){
    fseek(fp, p, SEEK_SET);
    fread(&aux, sizeof(TNo), 1, fp);

    if(aux.chave == ch){
      if(!aux.status){ 
        aux.status = 1;
        fseek(fp, p, SEEK_SET);
        fwrite(&aux, sizeof(TNo), 1, fp);
      }
      fclose(fp);      
      return;
    }

    if((!aux.status) && (q == -1)) q = p;

    ant = p;
    p = aux.prox;
  }

  if(q == -1){ //se nao tem nenhum elemento liberado no caminho...
    elem.prox = p;
    fseek(fp, 0L, SEEK_END);
    p = ftell(fp);
    fwrite(&elem, sizeof(TNo), 1, fp);

    if(ant == -1){ //se nao tem ninguem no caminho. Este e o primeiro no...
      fseek(fp, (h * sizeof(int)), SEEK_SET);
      fwrite(&p, sizeof(int), 1, fp);
    }else{
      aux.prox = p;
      fseek(fp, ant, SEEK_SET);
      fwrite(&aux, sizeof(TNo), 1, fp);
    }
    fclose(fp);
    return;
  }

  //tem um no liberado. Esta marcado por q!
  fseek(fp, q, SEEK_SET);
  fread(&aux, sizeof(TNo), 1, fp);
  aux.chave = ch;
  aux.status = 1;
  fseek(fp, q, SEEK_SET);
  fwrite(&aux, sizeof(TNo), 1, fp);
  fclose(fp);
}


void retira(char *nome, int ch, int m){
  FILE *fp = fopen(nome, "rb+");
  if(!fp) exit(1);

  int h = hash(ch, m), p;
  fseek(fp, (h * sizeof(int)), SEEK_SET);
  fread(&p, sizeof(int), 1, fp);

  TNo aux;
  while(p != -1){
    fseek(fp, p, SEEK_SET);
    fread(&aux, sizeof(TNo), 1, fp);
    if(aux.chave == ch){
      if(aux.status){
        aux.status = 0;
        fseek(fp, p, SEEK_SET);
        fwrite(&aux, sizeof(TNo), 1, fp);
      }
      fclose(fp);
      return; 
    }

    p = aux.prox;
  }
  fclose(fp);
}


TNo *busca(char* nome, int ch, int m){
  FILE *fp = fopen(nome, "rb");
  if(!fp) exit(1);

  int h = hash(ch, m), p;
  fseek(fp, (h * sizeof(int)), SEEK_SET);
  fread(&p, sizeof(int), 1, fp);

  TNo aux, *resp = NULL;
  while(p != -1){
    fseek(fp, p, SEEK_SET);
    fread(&aux, sizeof(TNo), 1, fp);
    if(aux.chave == ch){
      if(aux.status){
        resp = (TNo *) malloc(sizeof(TNo));
        resp->chave = ch;
        resp->status = 1;
        resp->prox = aux.prox;
      }
      fclose(fp);
      return resp; 
    }
    p = aux.prox;
  }

  fclose(fp);
  return NULL;
}

char* limpa(char *nome, int m) {
	int i, p;
	char *nome_novo = "novo"; //strcat(nome, "_novo");
	inicializa(nome_novo, m);
	
	// CONTEUDO DE RETIRA
	FILE *fp = fopen(nome, "rb+");
	FILE *fp_novo = fopen(nome_novo, "wb");
	if(!fp || !fp_novo) exit(1);
	
	//int h = hash(ch, m), p;
	//fseek(fp, (h * sizeof(int)), SEEK_SET);
		
	TNo aux;
	for(i=0; i<m && p!=-1; i++) {		
		printf("\nIndo para posicao do vetor %d", i);
		fseek(fp, i5, SEEK_SET); // setar posicao para proximo int do vetor		
		fread(&p, sizeof(int), 1, fp);	
		//while(p != -1) {
			fseek(fp, p, SEEK_SET);
			fread(&aux, sizeof(TNo), 1, fp);
			if(aux.status){
				printf("\nInserindo a chave %d no arquivo %s", aux.chave, nome_novo);
				insere(nome_novo, aux.chave, m);
			}
		//}
		p = aux.prox;
	}		
	fclose(fp);
	fclose(fp_novo);
	return nome_novo;
}	

int main(void){
  int n, m;
  printf("Digite m... ");
  scanf("%d", &m);
  printf("Digite n... ");
  scanf("%d", &n);

  if((n <= 1) || (m <= 1)) return 0;

  char nome[31];
  printf("Digite nome... ");
  scanf("%s", nome);

  inicializa(nome, m);
  int i, ch;
  for(i = 0; i < n; i++){
    printf("Digite a chave %d... ", (i + 1));
    scanf("%d", &ch);
    insere(nome, ch, m);
  }

  char resp;
  do{
    printf("Digite a chave a ser removida... ");
    scanf("%d", &ch);
    retira(nome, ch, m);
    printf("Quer continuar? ");
    scanf(" %c", &resp);
  }while((resp != 'N') && (resp != 'n'));

  printf("Digite a chave a ser procurada... ");
  scanf("%d", &ch);
  TNo *r = busca(nome, ch, m);
  if(!r)
    printf("Elemento nao encontrado!\n");
  else{
    printf("chave: %d\tstatus: %d\tprox_end: %d\n", r->chave, r->status, r->prox);
    free(r);
  }
  
  do{
    printf("Digite a chave a ser inserida... ");
    scanf("%d", &ch);
    insere(nome, ch, m);
    printf("Quer continuar? ");
    scanf(" %c", &resp);
  }while((resp != 'N') && (resp != 'n'));

  FILE *fp = fopen(nome, "rb");
  if(!fp) exit(1);
  int vet[m];
  fread(&vet, sizeof(int), m, fp);

  for(i = 0; i < m; i++){
    int p = vet[i];
    if(p != -1) printf("%d:\n", i);
    TNo x;
    while(p != -1){
      fseek(fp, p, SEEK_SET);
      fread(&x, sizeof(TNo), 1, fp);
      printf("chave: %d\tstatus: %d\tprox_end: %d\n", x.chave, x.status, x.prox);
      p = x.prox;
    }
  }
  fclose(fp);  
  limpa(nome, m);
  return 0;
}
