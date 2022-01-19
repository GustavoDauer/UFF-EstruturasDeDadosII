#include <stdio.h>
#include <stdlib.h>

#define TAM_V 11

void mostra(int v[], int tam_v) {
	int i;
	
	printf("\n");
	for(i=0; i<tam_v; i++)
		printf("%d ", v[i]);		
}

void bubbleSort(int v[], int tam_v) {
	int i, j, aux;
		
	for(i=0	; i<tam_v; i++) {
		j = 0;
		while(j<tam_v) {
			if(v[j] > v[j+1]) {
				aux = v[j];
				v[j] = v[j+1];
				v[j+1] = aux;				
			}
			j++;
		}
	}
}

int main(void) {
	int v[] = {5, 2, 1, 7, 8, 14, 20, -1, -5, -7, 25};
	
	mostra(v, TAM_V);
	bubbleSort(v, TAM_V);
	mostra(v, TAM_V);			
return 0;
}

