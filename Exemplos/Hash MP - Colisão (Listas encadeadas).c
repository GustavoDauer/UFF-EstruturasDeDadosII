#include <stdio.h>
#include <stdlib.h>

#define MAX_REAL 1001

typedef struct aluno {
	int mat;
	char nome[31], email[31], turma;
} TAluno;

TAluno * vet[MAX_REAL];

int hash(int mat) {
	return mat % MAX_REAL;
}

void inicializa(TAluno *vet[MAX_REAL]) {
	int i;
	for(i=0; i<MAX_REAL; i++)
		vet[i] = NULL;
}

TAluno* busca(TAluno *vet[MAX_REAL], int mat) {
	int h = hash(mat);
	TAluno *p = vet[h];
	while( (p) && (p->mat != mat) ) p = p->prox;
	return p;
}

void insere(TAluno *vet[MAX_REAL], int mat, char t, char *n, char *e) {
	int h = hash(mat);
	TAluno *p = vet[h], *ant = NULL;
	while( (p && p->mat != mat) ) {
		ant = p;
		p = p->prox;
	}
	if(p) {
		TAluno *p = (TAluno*) malloc (sizeof(TAluno));
		p->mat = mat;
		p->prox = NULL;
		if(!vet[h]) vet[h] = p:
		else ant->prox = p;
	}
	strcpy(p->nome, n);
	strcpy(p->email, e);
	p->turma = t;
}

TAluno* retira(TAluno *vet[MAX_REAL], int mat) {
	int h = hash(mat);
	TAluno *p = vet[h], *ant = NULL;
	while( (p && p->mat != mat) ) {
		ant = p;
		p = p->prox;
	}
	if(p) {
		if(!ant) vet[h] = vet[h]>prox;
		else ant->prox = p->prox;
		return p;
	}TAluno *p = (TAluno*) malloc (sizeof(TAluno));
		p->mat = mat;
		p->prox = NULL;
		if(!vet[h]) vet[h] = p:
		else ant->prox = p;
	}
	return NULL;
}
