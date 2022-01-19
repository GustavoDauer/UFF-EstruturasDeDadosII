//      Arvores.c
//      
//      Copyright 2011 Gustavo <gustavo@gustavo-desktop>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.


#include <stdio.h>
#include <stdlib.h>

typedef struct arvore {
	int dado;
	struct arvore *esq;
	struct arvore *dir;
} BinaryTree;

void imprimeArvore(BinaryTree *t) {
	if(t != NULL)
		printf("%d \n", t->dado);
	if(t->esq != NULL)
		imprimeArvore(t->esq);
	if(t->dir != NULL)
		imprimeArvore(t->dir);
}

void criaArvore(BinaryTree **t) {
	*t = NULL;
}

void criaArvoreAleatoria(BinaryTree *t) {
	BinaryTree *aux;
	srand(time(NULL));
	int qtdd = rand() % 25, n = rand() % 25, n1 = rand() % 25, n2 = rand() % 25, i;
	t = NULL;
	t = (BinaryTree*) malloc(sizeof(BinaryTree));
	aux = t;
	while(i < qtdd) {
		aux->dado = n;
		criaArvore(aux->esq);
		aux->esq = (BinaryTree*) malloc(sizeof(BinaryTree));
		aux->esq->dado = n1;		
		criaArvore(aux->dir);
		aux->dir = (BinaryTree*) malloc(sizeof(BinaryTree));
		aux->dir->dado = n2;	
		i++;
	}
}

int main() {
	BinaryTree *t;	
	criaArvoreAleatoria(t);
	imprimeArvore(t);
	return 0;
}

