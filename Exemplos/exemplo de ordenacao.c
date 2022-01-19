#include <stdio.h>
#include <stdlib.h>

int compara(const void *p1, const void *p2) {
	int *i1 = (int*) p1,
		*i2 = (int*) p2;
		
	if( (*i1) > (*i2) ) return 1;
	if( (*i1) < (*i2) ) return -1;
	return 0;
}

int main(void) {	
	int n;
	scanf("%d", &n);
	if(n <= 0) return 0;
	int vet[n], i;
	for(i=0; i<n; i++)
		scanf("%d", &vet[i]);
	qsort(vet, n, sizeof(int), compara);		
	for(i=0; i<n; i++) printf("%d", vet[i]);	
	return 0;
}
