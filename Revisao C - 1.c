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

#define NUMERO_ATLETAS 7
#define NUMERO_NOTAS 6

#include <stdio.h>
#include <stdio.h>

int main() {
	int i, j, maior, menor, nota, total;
	for(i=1; i<=NUMERO_ATLETAS; i++) {
		printf("\nATLETA %d\n\n", i);
		maior = 0;
		menor = 0;
		total = 0;
		for(j=1; j<=NUMERO_NOTAS; j++) {
			printf("Nota %d: ", j);
			scanf("%d", &nota);			
			if(nota > maior) {
				maior = nota;
			}
			if(nota < menor) {
				menor = nota;
			}
			total += nota;				
		}
		total -= maior;
		total -= menor;
		printf("Media: %d", total/4);
		printf("\n");
	}
	return 0;
}

