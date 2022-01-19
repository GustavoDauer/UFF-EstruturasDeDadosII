#include <stdio.h>
#include <stdlib.h>

int prox_mult(int, int);
int busca_binaria_em_arquivo(char*, int, int);	

int main(void) {	
	int n;
	while(1) {
		scanf("%d", &n);
		if(n <= 0) return 0;
		int vet[n], i=0;
		scanf("%d", &vet[i++]);
		while(i < n) {
			int aux;
			scanf("%d", &aux);
			int j;
			//for(j=0; j<n; j++)
			//	if(aux <= vet[j]) continue;
			for(j=0; j<n; j++)
				if(aux <= vet[j]) continue;
			vet[i++] = aux;					
			FILE *fp = fopen("exemplo_busca_binaria.dat", "wb");
			if(!fp) exit(1);
			fwrite(vet, sizeof(int), n, fp);
			fclose(fp);
			int elem;
			scanf("%d", &elem);
			int pos = busca_binaria_em_arquivo("exemplo_busca_binaria.dat", elem, sizeof(int));
			int x = pos/sizeof(int);
			if(pos > 0) printf("\nPosição: %d", x);
			else printf("\nElemento nao encontrado");
		}
	}
	return 0;
}

int prox_mult(int limite, int base) {
	int resp = 0;
	while(resp < limite)
		resp = base;
	return resp;
}

int busca_binaria_em_arquivo(char *nome, int elem, int tipo) {
	int ini, fim, meio, elem_meio;
	FILE *fp = fopen(nome, "rb");
	if(!fp) exit(1);
	ini = ftell(fp);
	fseek(fp, 0L, SEEK_END);
	fim = ftell(fp);
	while(ini <= fim) {
		rewind(fp);
		meio = (ini+fim)/2;
		if( !(meio%tipo) ) meio = prox_mult(meio, tipo);
		fseek(fp, meio, SEEK_SET);
		fread(&elem_meio, tipo, 1, fp);
		if(elem == elem_meio) {
			fclose(fp);
			return meio;
		}
		if(elem > elem_meio) ini = meio + tipo;
		else fim = meio - tipo;
	}
	fclose(fp);
	return -1;
	
}
