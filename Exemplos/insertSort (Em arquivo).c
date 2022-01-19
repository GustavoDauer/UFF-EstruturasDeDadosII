#include <stdio.h>
#include <stdlib.h>

void selectSort(FILE *fp){
  int i, j, r, s, elem_menor, menor, elem, aux;

  i = ftell(fp);
  r = fread(&elem_menor, sizeof(int), 1, fp);
  while(r == 1){
    menor = i;
    aux = elem_menor;
    j = ftell(fp);
    s = fread(&elem, sizeof(int), 1, fp);
    while(s == 1){
      if(elem < elem_menor){
        menor = j;
        elem_menor = elem;
      }
      j = ftell(fp);
      s = fread(&elem, sizeof(int), 1, fp); 
    }
    if(menor != i){
      printf("Trocar %d(%d) por %d(%d)\n", aux, i, elem_menor, menor);
      rewind(fp);
      fseek(fp, menor, SEEK_SET);
      fwrite(&aux, sizeof(int), 1, fp);
      rewind(fp);
      fseek(fp, i, SEEK_SET);
      fwrite(&elem_menor, sizeof(int), 1, fp);
    }
    else{
      rewind(fp);
      fseek(fp, (i + sizeof(int)), SEEK_SET);
    }

    i = ftell(fp);
    r = fread(&elem_menor, sizeof(int), 1, fp);
  } 
}

int main(int argc, char** argv){
  int n = 10, vet[] = {0, 9, 8, 7, 6, 5, 4, 3, 2, 1}, resp[n];
  FILE *fp = fopen(argv[1], "wb");
  if(!fp) exit(1);
  fwrite(vet, sizeof(int), n, fp);
  fclose(fp);

  fp = fopen(argv[1], "rb+");
  if(!fp) exit(1);
  selectSort(fp);
  fclose(fp);

  fp = fopen(argv[1], "rb");
  if(!fp) exit(1);
  fread(resp, sizeof(int), n, fp);
  fclose(fp);

  int i; 
  for(i = 0; i < n; i++) printf("%d\n", resp[i]);
 
  return 0;
}
