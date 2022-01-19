#include <stdio.h>
#include <stdlib.h>

int prox_mult(int elem, int pot){
  int resp = 0;
  while(resp <= elem) resp += pot;
  return resp;
}

int bb(FILE *fp, int elem){
  int ini, fim, meio, n, elem_meio;

  rewind(fp);
  fread(&n, sizeof(int), 1, fp);
  ini = ftell(fp);
  rewind(fp);
  fseek(fp, (sizeof(int)*n), SEEK_SET);
  fim = ftell(fp);

  while(ini <= fim){
    rewind(fp);
    meio = (fim + ini) / 2;
    if((meio % (sizeof(int))) != 0) meio = prox_mult(meio, sizeof(int));
    fseek(fp, meio, SEEK_SET);    
    fread(&elem_meio, sizeof(int), 1, fp);
    printf("ini = %d\tfim = %d\tmeio = %d\telem = %d\n", ini, fim, meio, elem_meio);
    if(elem_meio == elem) return meio;
    if(elem_meio < elem) ini = meio + sizeof(int);
    if(elem_meio > elem) fim = meio - sizeof(int);
  }
  
  return -1;
}

int main(int argc, char** argv){
  int i, n = 100, vet[n], elem;
  FILE *fp = fopen(argv[1], "wb");
  if(!fp) exit(1); 
  for(i = 0; i < n; i++) vet[i] = i;
  fwrite(&n, sizeof(int), 1, fp);
  fwrite(vet, sizeof(int), n, fp);
  fclose(fp);

  fp = fopen(argv[1], "rb");
  if(!fp) exit(1);
  printf("Digite o elemento procurado...\n");
  scanf("%d", &elem);
  int pos = bb(fp, elem);
  if(pos > 0) printf("%d\n", pos / 4);
  else printf("Elemento inexistente...\n"); 
  fclose(fp);
  return 0;
}
