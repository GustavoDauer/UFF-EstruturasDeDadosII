#include <stdio.h>
#include <stdlib.h>

int main(void) {	
	FILE *fp = fopen("exemplo_de_abertura_de_arquivo_teste.txt", "a");
	if(!fp) {
		printf("Erro");
		exit(1);
	}
	
	return 0;
}
