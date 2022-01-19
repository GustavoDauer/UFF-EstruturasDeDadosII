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
	while(vet[h]) {
		if(vet[h]->mat == mat)	return vet[h];
		h = (h+1) % MAX_REAL;
	}
	return NULL;
}

void insere(TAluno *vet[MAX_REAL], int mat, char *nome, char *email, char turma) {
	int h = hash(mat);
	while( (vet[h] && vet[h]->mat != mat) ) h = (h+1) % MAX_REAL;
	if(!vet[h]) {
		vet[h] = (TAluno *) malloc (sizeof(TAluno));
		vet[h]->mat = mat;
	}
	strcpy(vet[h]->nome, nome);
	strcpy(vet[h]->email, email);
	vet[h]->turma = turma;
}

TAluno* retira(TAluno *vet[MAX_REAL], int mat) {
	int h = hash(mat);
	while(vet[h]) {
		if(vet[h]->mat == mat) {
			TAluno *resp = (TAluno *) malloc(sizeof(TAluno));
			resp->mat = mat;
			strcpy(resp->nome, vet[h]->nome);
			strcpy(resp->email, vet[h]->email);
			resp->turma = vet[h]->turma;
			free(vet[h]);
			vet[h] = NULL;
			return resp;
		}
		h = (h + 1) % MAX_REAL;
	}
	return NULL;
}
