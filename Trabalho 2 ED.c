//      Trabalho 2 ED.c
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
#include <ctype.h>
//#include <conio.h>

#define SAIR 's'

////////////// LINUX
#define PAUSA getchar()
//#define PAUSA system("sleep 0.5")
#define LIMPA_TELA system("clear")

///////////// WINDOWS
//#define PAUSA getch();
//#define LIMPA_TELA clrscr()
//#define LIMPA_TELA system("cls")

/////////////////////////////////// REMOVER AO USAR NO BORLAND!!!!!!!!!!!!!!
void gotoxy(int x, int y){}
///////////////////////////////////

#include "comum.h"

void showHeader();
void showMenu();
void showTree(BinaryTree *t);
void showTreeUnion(BinaryTree *t1, BinaryTree *t2);
void showTreeIntersection(BinaryTree *t1, BinaryTree *t2);
void showTreeDifference(BinaryTree *t1, BinaryTree *t2);
void searchInTree(BinaryTree *t);
void insertInTree(BinaryTree* t);
void removeFromTree(BinaryTree* t);

BinaryTree *t1, *t2;

int main() {
    char op;
    showHeader();
	printf("\tCriacao da Arvore AVL T1\n");
	insertTreeNodes(&t1);
	showHeader();
	printf("\tCriacao da Arvore AVL T2\n");
	insertTreeNodes(&t2);
	do {
		switch(op) {
			case '1' : {    showTree(t1); break;  }                     // FUNCIONANDO!
			case '2' : {    showTree(t2); break;  }                     // FUNCIONANDO!
			case '3' : {	showTreeUnion(t1, t2); break;  }            // FUNCIONANDO!
			case '4' : {	showTreeIntersection(t1, t2); break;  }     // PROBLEMAS! O PROGRAMA SIMPLESMENTE FECHA!
			case '5' : {	showTreeDifference(t1, t2); break;  }       // PROBLEMAS! O PROGRAMA SIMPLESMENTE FECHA!
			case '6' : {	searchInTree(t1); break;    }               // PROBLEMAS! O PROGRAMA NAO ENCONTRA NENHUM ELEMENTO!
			case '7' : {	searchInTree(t2); break;    }               // PROBLEMAS! O PROGRAMA NAO ENCONTRA NENHUM ELEMENTO!
			case '8' : {	insertInTree(t1); break;    }               // PROBLEMAS! A FUNCAO DEPENDE DE SEARCH!
			case '9' : {    insertInTree(t2); break;    }               // PROBLEMAS! A FUNCAO DEPENDE DE SEARCH!
			case 'q' : {	removeFromTree(t1); break;  }               // PROBLEMAS! A FUNCAO DEPENDE DE SEARCH!
			case 'w' : {	removeFromTree(t2); break;  }               // PROBLEMAS! A FUNCAO DEPENDE DE SEARCH!
		}
		LIMPA_TELA;
		showHeader();
		showMenu();
		printf("\nEscolha: ");
		op = getchar();
		printf("\n");
	} while(op != SAIR && op != toupper(SAIR));
	return 0;
}

void showTree(BinaryTree *t) {
	LIMPA_TELA;
	printFormatedTree(t, 40, 0, calcHeight(t));
	PAUSA;
}
/////////////////////////////////////////////////////////////////////////////////////////////
// MODIFICACAO: Sao passados como parametros 2 clones de t1 e t2 ao inves de apenas de t1
// NAO TESTADO!
// Ver se os bugs relatados no Switch serao resolvidos!
/////////////////////////////////////////////////////////////////////////////////////////////
void showTreeUnion(BinaryTree *t1, BinaryTree *t2) {
	BinaryTree *aux = getTreeClone(t1), *aux2 = getTreeClone(t2);
	LIMPA_TELA;
	treeUnion(&aux, aux2);
	printFormatedTree(aux, 40, 0, calcHeight(aux));
	PAUSA;
}

void showTreeIntersection(BinaryTree *t1, BinaryTree *t2) {
	BinaryTree *aux = getTreeClone(t1), *aux2 = getTreeClone(t2);
	LIMPA_TELA;
	treeIntersection(&aux, aux2);
	printFormatedTree(aux, 40, 0, calcHeight(aux));
	PAUSA;
}

void showTreeDifference(BinaryTree *t1, BinaryTree *t2) {
	BinaryTree *aux = getTreeClone(t1), *aux2 = getTreeClone(t2);
	LIMPA_TELA;
	treeDifference(&aux, aux2);
	printFormatedTree(aux, 40, 0, calcHeight(aux));
	PAUSA;
}
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

void searchInTree(BinaryTree *t) {
    int e, result;
	LIMPA_TELA;
	printf("\nDigite o elemento que deseja buscar: ");
	e = scanf("%d", &e);
	result = searchNode(t, e);
	if(result > 1)
		printf("\nO elemento nao esta na Arvore!");
	else
		printf("\nO elemento esta na Arvore!");
	PAUSA;
}

void insertInTree(BinaryTree *t) {
    int e;
	LIMPA_TELA;
	printf("\nDigite o elemento que deseja inserir: ");
	e = scanf("%d", &e);
	insertAVL(&t, e);
	PAUSA;
}

void removeFromTree(BinaryTree *t) {
    int e;
	LIMPA_TELA;
	printf("\nDigite o elemento que deseja remover: ");
	e = scanf("%d", &e);
	removeAVL(&t, e);
	PAUSA;
}

void showHeader() {
	printf("\n=============================================================\n\tTrabalho 2 de Estruturas de Dados I\n=============================================================\n\n");
}

void showMenu() {
	printf("\n");
	printf("1 - Mostrar Arvore T1\n");
	printf("2 - Mostrar Arvore T2\n");
	printf("3 - Mostrar T1 u T2\n");
	printf("4 - Mostrar T1 n T2\n");
	printf("5 - Mostrar T1 - T2\n");
	printf("6 - Buscar elemento na Avore T1\n");
	printf("7 - Buscar elemento na Avore T2\n");
	printf("8 - Inserir elemento na Avore T1\n");
	printf("9 - Inserir elemento na Avore T2\n");
	printf("Q - Remover elemento da Avore T1\n");
	printf("W - Remover elemento da Avore T2\n");
	printf("S - Sair\n");
	printf("\n");
}

