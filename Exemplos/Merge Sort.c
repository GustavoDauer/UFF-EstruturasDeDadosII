#include <stdio.h>
#include <stdlib.h>

#define TAM_V 11

void mostra(int v[], int tam_v) {
	int i;
	
	printf("\n");
	for(i=0; i<tam_v; i++)
		printf("%d ", v[i]);		
}

void mescla(int v[], int tam_v) {
	int meio, i, j, k;
	int *temp;
	
	temp = (int*) malloc(tam_v * sizeof(int));
	if(temp == NULL)
		exit(1);
	meio = tam_v / 2;
	i = 0;
	j = meio;
	k = 0;
	while(i < meio && j < tam_v) {
		if(v[i] < v[j])
			temp[k] = v[i++];
		else
			temp[k] = v[j++];
		++k; // ou k++
	}
	if(i == meio)
		while(j < tam_v)
			temp[k++] = v[j++];
	else
		while(i < meio)
			temp[k++] = v[i++];
	for(i=0; i<tam_v; i++)
		v[i] = temp[i];
	free(temp);
}

void mergeSort(int v[], int tam_v) {
	int meio;
	if(tam_v > 1) {
		meio = tam_v / 2;
		mergeSort(v, meio);
		mergeSort(v + meio, tam_v - meio);
		mescla(v, tam_v);
	}
}

int main(void) {
	int v[] = {5, 2, 1, 7, 8, 14, 20, -1, -5, -7, 25};
	
	mostra(v, TAM_V);
	mergeSort(v, TAM_V);
	mostra(v, TAM_V);			
return 0;
}
