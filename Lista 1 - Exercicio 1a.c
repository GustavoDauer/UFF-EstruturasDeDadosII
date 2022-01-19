//      Lista 1 - Exercicio 1a.c
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

#define TAMANHO 5

struct no {
	int dado;
	struct no *prox;
};

typedef struct no lista;

void imprime(lista *l) {
	lista *aux = l;
	printf("\nLista: ");
	while(aux != NULL) {
		printf("%d ", aux->dado);
		aux = aux->prox;		
	}
}

lista* criaLista(lista *l) {
	l = (lista*) malloc(sizeof(lista));
	lista *aux = (lista*) malloc(sizeof(lista));
	lista *temp;
	int i;	
	l->dado = (int) rand() % 25;	
	l->prox = aux;
	aux->dado = (int) rand() % 25;
	for(i=1; i<TAMANHO; i++) {
		temp = (lista*) malloc(sizeof(lista));
		temp->dado = (int) rand() % 25;
		aux->prox = temp;
		aux = aux->prox;
	}
	return l;
}

lista* concatena(lista *l1, lista *l2) {
	if(l1 == NULL) {
		return l2;
	}
	else {
		lista* aux = l1;
		while(aux->prox != NULL) {
			aux = aux->prox;
		}
		aux->prox = l2;
		return l1;
	}
	
}


int main() {
	srand(time(NULL));
	lista *l1 = criaLista(l1);
	lista *l2 = criaLista(l2);
	imprime(l1);
	imprime(l2);
	lista *l = concatena(l1, l2);
	imprime(l);
	return 0;
}

