#include <stdio.h>
#include <stdlib.h>

void criaArquivo(char *nome_arq) {
	int i, n, qtd_num;
	FILE *fp;
	
	fp = fopen(nome_arq, "wb");	
	printf("Cria Arquivo\n--------------------------------------\n");
	printf("Quantos numeros? ");
	scanf("%d", &qtd_num);
	printf("\nEntre com os numeros\n");
	for(i=0; i<qtd_num; i++) {
		scanf("%d", &n);
		fwrite(&n, sizeof(int), 1, fp);		
	}
	printf("--------------------------------------\n");
	fclose(fp);
}

void mostraArquivo(char *nome_arq) {
	int n;
	FILE *fp;
	
	fp = fopen(nome_arq, "rb");
	printf("\n\nMostra Arquivo\n--------------------------------------\n");
	printf("Numeros lidos: ");
	while(fread(&n, sizeof(int), 1, fp) == 1) {
		printf("%d ", n);		
	}
	printf("\n--------------------------------------\n");
	fclose(fp);
}
/* BUBBLE SORT VERSÃO EM VETORES
void bubbleSort(int v[], int tam_v) {
	int i, j, aux;
		
	for(i=0	; i<tam_v; i++) {
		j = 0;
		while(j<tam_v) {
			if(v[j] > v[j+1]) {
				printf("Trocar %d(%d) por %d(%d)\n", v[j], j, v[j+1], j+1);
				aux = v[j];
				v[j] = v[j+1];
				v[j+1] = aux;				
			}
			j++;
		}
	}
}
*/

void bubbleSort_emArquivo(char *nome_arq) {
	int i, j, num1, num2, tam_f;
	FILE *fp;
	
	fp = fopen(nome_arq, "rb+");			
	fseek(fp, 0, SEEK_END);
	tam_f = ftell(fp); // Tamanho do arquivo em bytes (Numero de iterações = tam_f / sizeof(int)
	for(i=0	; i<tam_f; i+=sizeof(int)) { // Itera até o último elemento
		for(j=0	; j<tam_f-sizeof(int); j+=sizeof(int)) { // Itera até o penúltimo elemento
			fread(&num1, sizeof(int), 1, fp);
			fread(&num2, sizeof(int), 1, fp);
			if(num1 > num2) {
				printf("\nTrocar %d(%d) por %d(%d)", num1, i, num2, j);
				fseek(fp, -(sizeof(int)*2), SEEK_CUR); // Volta 2 posições para efetuar a troca
				fwrite(&num2, sizeof(int), 1, fp);		// Escreve os elementos trocados		
				fwrite(&num1, sizeof(int), 1, fp);
				fseek(fp, -sizeof(int), SEEK_CUR);	    // Volta 1 posição para continuar o efeito bolha (subir o elemento maior)
			}
			else {
				fseek(fp, -sizeof(int), SEEK_CUR);		// Volta 1 posição para continuar o efeito bolha (subir o elemento maior)
			}			
		}
		rewind(fp);
	}
	fclose(fp);
}

int main(void) {	
	criaArquivo("teste");
	mostraArquivo("teste");	
	bubbleSort_emArquivo("teste");	
	mostraArquivo("teste");
return 0;
}

