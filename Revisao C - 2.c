//      Revisao C - 1.c
//      
//      Copyright 2011 Gustavo <gustavo@gustavo-HP-Pavilion-dv4-Notebook-PC>
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
//      
//      

#define TAMANHO 700

#include <stdio.h>
#include <stdio.h>
#include <string.h>

int estaContido(char p[], char f[]) {
	int i, j;
	char teste[TAMANHO];
	for(i=0; i<TAMANHO; i++) {
		teste[i] = ' ';
	}
	for(i=0; i<strlen(p); i++) {
		for(j=0; j<strlen(f); j++) {
			if(p[i] == f[j]) {
				teste[i] = p[i];
			}
		}
	}
	printf("\n\nResultado: %s", teste);
	for(i=0; i<strlen(p); i++) {		
		if(p[i] != teste[i]) {
			return 0;
		}		
	}
	return 1;
}

int main() {
	char palavra[TAMANHO];
	char frase[TAMANHO];
	printf("\nEntre com a palavra: ");
	gets(palavra);
	printf("\nEntre com a frase: ");
	gets(frase);
	printf("\nVerificando se:\n\"%s\" esta contido em:\n\"%s\"", palavra, frase);
	if(estaContido(palavra, frase)) {
		printf("\nA palavra esta contida");
	}
	else {
		printf("\nA palavra nao esta contida");
	}		
	return 0;
}

