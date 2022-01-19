#include <stdio.h>
#include <stdlib.h>

typedef struct lista {
	int info;
	struct lista *prox;
} TLSE;

TLSE *ins_ini(TLSE *l, int elem);
TLSE *ins_fim(TLSE *l, int elem);
TLSE *ins_fim_rec(TLSE *l, int elem);
void mostraLista(TLSE *l);

int main(void) {	
	TLSE *l = NULL;
	l = ins_ini(l, 1);
	l = ins_ini(l, 2);
	mostraLista(l);
	l = ins_fim(l, 3);
	l = ins_fim(l, 4);
	mostraLista(l);
	l = ins_fim_rec(l, 5);
	l = ins_fim_rec(l, 7);
	mostraLista(l);
	return 0;
}

TLSE *ins_ini(TLSE *l, int elem) {
	printf("\nInserindo %d no inicio da lista\n", elem);
	TLSE *novo = (TLSE*) (malloc(sizeof(TLSE)));
	novo -> info = elem;
	novo -> prox = l;
	return novo;
}

TLSE *ins_fim(TLSE *l, int elem) {
	printf("\n Inserindo %d no fim da lista\n", elem);
	if(!l)
		return ins_ini(l, elem);		
	TLSE *novo = (TLSE*) (malloc(sizeof(TLSE)));
	novo -> info = elem;
	novo -> prox = NULL;
	TLSE *p = l;
	while(p -> prox) p = p -> prox;
	p -> prox = novo;
	return l;
}

// ERRO
TLSE *ins_fim_rec(TLSE *l, int elem) {
	printf("\n Inserindo recursivamente %d no fim da lista\n", elem);
	if(!l) // Esta entrando indevidamente nesse if e dando erro de segmentação na próxima tentativa de inserção
		return ins_ini(l, elem);
	l -> prox = ins_fim_rec(l -> prox, elem);
	return elem;
}

void mostraLista(TLSE *l) {
	printf("\nLista: ");	
	do {
		if(l != NULL) printf("%d ", l->info);
		l = l->prox;
		if(l != NULL) printf(" -> ");
	} while(l != NULL);
	printf("\n");
}
