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

#include <stdio.h>
#include <stdio.h>

int mdc(int x, int y) {
	int i, maximo;
	if(y <= x && (x % y) == 0) {
		return y;
	}
	if(x > y) {
		i = x;
		maximo = y;
	}
	else {
		i = y;
		maximo = x;
	}
	for(; i>0; i--) {
		if((x % i) == 0 && (y % i) == 0) {
			if(maximo > i) {
				maximo = i;
			}
		}	
	}
	return maximo;
}

int main() {
	int x, y;
	printf("Entre com dois numeros inteiros: ");
	scanf("%d %d", &x, &y);
	printf("O MDC de %d e %d eh: %d", x, y, mdc(x, y));	
	return 0;
}

