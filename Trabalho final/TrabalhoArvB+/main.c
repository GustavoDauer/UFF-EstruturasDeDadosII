#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CH 3524 // CARGA HORÁRIA EM HORAS
#define MAX_PERIODO 12

//////////////////////////////////////////////////////////

const int t = 2;

/////////////////////////////////////////////////////////
///////////// ESTRUTURA NOVA (ARVORE B+) ////////////////
/////////////////////////////////////////////////////////
typedef struct aluno{
    int matricula, ch, semestre;
    char nome[31];
}TAluno;

typedef struct ArvBM {
    TAluno **chave;
    int nchaves, folha;
    struct ArvBM **filho, *prox;
    //int *chave;
} TABM;

////////////////////////////////////////////////////////
// FUNCOES DE ARVORE B+ (CONVERTIDAS DA ARVORE B) //////
////////////////////////////////////////////////////////

TABM *Inicializa(){
  return NULL;
}

TABM *Cria(int t){
  TABM* novo = (TABM*) malloc( sizeof(TABM) );
  novo->nchaves = 0;
  novo->chave = (TAluno *) malloc(sizeof(TAluno *)*((t*2)-1));
  novo->folha = 1;
  novo->filho = (TABM**) malloc( sizeof(TABM*) * t*2 );
  novo->prox = NULL; // Modificação para arvore B+
  int i;
  for(i=0; i<(t*2); i++) novo->filho[i] = NULL;
  return novo;
}

TABM *Libera(TABM *a){
  if(a){
    if(!a->folha){
      int i;
      for(i = 0; i <= a->nchaves; i++) Libera(a->filho[i]);
    }
    free(a->chave);
    free(a->filho);
    free(a);
    return NULL;
  }
  return NULL; // Essa linha nao existia no codigo original
}

void Imprime(TABM *a, int andar){
  if (a){
    int i,j;
    for (i=0; i<=a->nchaves-1; i++) {
      Imprime(a->filho[i],andar+1);
      for(j=0; j<=andar; j++) printf("   ");
      printf("%d (%s)\n", a->chave[i]->matricula, a->chave[i]->nome);
    }
    Imprime(a->filho[i],andar+1);
  }
}

TABM *Busca(TABM* x, int ch){ // FUNCAO ROSSETI (NAO MOVER)
  TABM *resp = NULL;
  if(!x) return resp;
  int i = 0;
  while(i < x->nchaves && ch > x->chave[i]->matricula) i++;
  if(x->folha && i < x->nchaves && ch == x->chave[i]->matricula) return x;
  if(x->folha) return resp;
  return Busca(x->filho[i], ch);
}

TABM* buscaVet(TABM* arv, int ch){
    int i= 0;
    TABM* xbusca = Inicializa();
    xbusca = Busca(arv, ch);
    if(xbusca) {
        while(i < xbusca->nchaves && ch > xbusca->chave[i]->matricula) i++;
        printf("Matricula: %d  Nome:  %s  Semestre:  %d  Carga horaria:  %d\n",xbusca ->chave[i]->matricula,xbusca ->chave[i]->nome,xbusca ->chave[i]->semestre, xbusca ->chave[i]->ch);        
    }
    else
        printf("\nNao encontrado\n");
    return arv;
}

// FUNCOES ROSSETI (LEVEMENTE MODIFICADAS)
TABM *Divisao(TABM *x, int i, TABM* y, int t){
  TABM *z=Cria(t);
  z->nchaves= t - 1;
  z->folha = y->folha;
  int j;
  for(j=0;j<t-1;j++) z->chave[j] = y->chave[j+t];
  if(!y->folha){
    for(j=0;j<t;j++){
      z->filho[j] = y->filho[j+t];
      y->filho[j+t] = NULL;
    }
  }
  y->nchaves = t-1;
  for(j=x->nchaves; j>=i; j--) x->filho[j+1]=x->filho[j];
  x->filho[i] = z;
  for(j=x->nchaves; j>=i; j--) x->chave[j] = x->chave[j-1];
  x->chave[i-1] = y->chave[t-1];
  x->nchaves++;
  // INICIO - Modificação para Arvores B+
  if(y->folha) {
	y->nchaves++;
	y->prox = z;
	}
  // FIM
  return x;
}

TABM *Insere_Nao_Completo(TABM *x, TAluno *k, int t){
  int i = x->nchaves-1;
  if(x->folha){
    while((i>=0) && (k->matricula < x->chave[i]->matricula)){
      x->chave[i+1] = x->chave[i];
      i--;
    }
    x->chave[i+1] = k;
    x->nchaves++;
    return x;
  }
  while((i>=0) && (k->matricula < x->chave[i]->matricula)) i--;
  i++;
  if(x->filho[i]->nchaves == ((2*t)-1)){
    x = Divisao(x, (i+1), x->filho[i], t);
    if(k->matricula > x->chave[i]->matricula) i++;
  }
  x->filho[i] = Insere_Nao_Completo(x->filho[i], k, t);
  return x;
}

TABM * Insere(TABM *T, TAluno *k, int t) {
  if (Busca(T, k->matricula)) return T;

  if(!T){
    T=Cria(t);
    T->chave[0] = k;
    T->nchaves=1;
    return T;
  }

  if(T->nchaves == (2*t)-1){
    TABM *S = Cria(t);
    S->nchaves=0;
    S->folha = 0;
    S->filho[0] = T;
    S = Divisao(S,1,T,t);
    S = Insere_Nao_Completo(S,k,t);
    return S;
  }

  T = Insere_Nao_Completo (T,k,t);
  return T;
}

TABM* remover(TABM* arv, int ch, int t){
  if(!arv) return arv;
  int i;
  printf("Removendo %d...\n", ch);
  for(i = 0; i<arv->nchaves && arv->chave[i]->matricula < ch; i++);
  if(i < arv->nchaves && ch == arv->chave[i]->matricula){ //CASOS 1, 2A, 2B e 2C
    if(arv->folha){ //CASO 1
      printf("\nCASO 1\n");
      int j;
      for(j=i; j<arv->nchaves-1;j++) arv->chave[j]->matricula = arv->chave[j+1]->matricula;      
      arv->nchaves--;      
      printf("\nNCHAVES: %d...\n", arv->chave[0]->matricula);
      return arv;
    }
    if(!arv->folha && arv->filho[i]->nchaves >= t){ //CASO 2A
      printf("\nCASO 2A\n");
      TABM *y = arv->filho[i];  //Encontrar o predecessor k' de k na árvore com raiz em y
      while(!y->folha) y = y->filho[y->nchaves];
      int temp = y->chave[y->nchaves-1];
      arv->filho[i] = remover(arv->filho[i], temp, t);
      //Eliminar recursivamente K e substitua K por K' em x
      arv->chave[i] = temp;
      return arv;
    }
    if(!arv->folha && arv->filho[i+1]->nchaves >= t){ //CASO 2B
      printf("\nCASO 2B\n");
      TABM *y = arv->filho[i+1];  //Encontrar o sucessor k' de k na árvore com raiz em y
      while(!y->folha) y = y->filho[0];
      int temp = y->chave[0];
      y = remover(arv->filho[i+1], temp, t); //Eliminar recursivamente K e substitua K por K' em x
      arv->chave[i] = temp;
      return arv;
    }
    if(!arv->folha && arv->filho[i+1]->nchaves == t-1 && arv->filho[i]->nchaves == t-1){ //CASO 2C
      printf("\nCASO 2C\n");
      TABM *y = arv->filho[i];
      TABM *z = arv->filho[i+1];
      y->chave[y->nchaves] = ch;          //colocar ch ao final de filho[i]
      int j;
      for(j=0; j<t-1; j++)                //juntar chave[i+1] com chave[i]
        y->chave[t+j] = z->chave[j];
      for(j=0; j<=t; j++)                 //juntar filho[i+1] com filho[i]
        y->filho[t+j] = z->filho[j];
      y->nchaves = 2*t-1;
      for(j=i; j < arv->nchaves-1; j++)   //remover ch de arv
        arv->chave[j] = arv->chave[j+1];
      for(j=i+1; j <= arv->nchaves; j++)  //remover ponteiro para filho[i+1]
        arv->filho[j] = arv->filho[j+1];
      arv->filho[j] = NULL; //Campello
      arv->nchaves--;
      arv->filho[i] = remover(arv->filho[i], ch, t);
      return arv;
    }
  }

  TABM *y = arv->filho[i], *z = NULL;
  if (y->nchaves == t-1){ //CASOS 3A e 3B
    if((i < arv->nchaves) && (arv->filho[i+1]->nchaves >=t)){ //CASO 3A
      printf("\nCASO 3A: i menor que nchaves\n");
      z = arv->filho[i+1];
      y->chave[t-1] = arv->chave[i];   //dar a y a chave i da arv
      y->nchaves++;
      arv->chave[i] = z->chave[0];     //dar a arv uma chave de z
      int j;
      for(j=0; j < z->nchaves-1; j++)  //ajustar chaves de z
        z->chave[j] = z->chave[j+1];
      //z->chave[j] = 0; Rosseti
      y->filho[y->nchaves] = z->filho[0]; //enviar ponteiro menor de z para o novo elemento em y
      for(j=0; j < z->nchaves; j++)       //ajustar filhos de z
        z->filho[j] = z->filho[j+1];
      z->nchaves--;
      arv->filho[i] = remover(arv->filho[i], ch, t);
      return arv;
    }
    if((i > 0) && (!z) && (arv->filho[i-1]->nchaves >=t)){ //CASO 3A
      printf("\nCASO 3A: i igual a nchaves\n");
      z = arv->filho[i-1];
      int j;
      for(j = y->nchaves; j>0; j--)               //encaixar lugar da nova chave
        y->chave[j] = y->chave[j-1];
      for(j = y->nchaves+1; j>0; j--)             //encaixar lugar dos filhos da nova chave
        y->filho[j] = y->filho[j-1];
      y->chave[0] = arv->chave[i-1];              //dar a y a chave i da arv
      y->nchaves++;
      arv->chave[i-1] = z->chave[z->nchaves-1];   //dar a arv uma chave de z
      y->filho[0] = z->filho[z->nchaves];         //enviar ponteiro de z para o novo elemento em y
      z->nchaves--;
      arv->filho[i] = remover(y, ch, t);
      return arv;
    }
    if(!z){ //CASO 3B
      if(i < arv->nchaves && arv->filho[i+1]->nchaves == t-1){
        printf("\nCASO 3B: i menor que nchaves\n");
        z = arv->filho[i+1];
        y->chave[t-1] = arv->chave[i];     //pegar chave [i] e coloca ao final de filho[i]
        y->nchaves++;
        int j;
        for(j=0; j < t-1; j++){
          y->chave[t+j] = z->chave[j];     //passar filho[i+1] para filho[i]
          y->nchaves++;
        }
        if(!y->folha){
          for(j=0; j<t; j++){
            y->filho[t+j] = z->filho[j];
          }
        }
        for(j=i; j < arv->nchaves-1; j++){ //limpar referências de i
          arv->chave[j] = arv->chave[j+1];
          arv->filho[j+1] = arv->filho[j+2];
        }
        arv->nchaves--;
        arv = remover(arv, ch, t);
        return arv;
      }
      if((i > 0) && (arv->filho[i-1]->nchaves == t-1)){
        printf("\nCASO 3B: i igual a nchaves\n");
        z = arv->filho[i-1];
        if(i == arv->nchaves)
          z->chave[t-1] = arv->chave[i-1]; //pegar chave[i] e poe ao final de filho[i-1]
        else
          z->chave[t-1] = arv->chave[i];   //pegar chave [i] e poe ao final de filho[i-1]
        z->nchaves++;
        int j;
        for(j=0; j < t-1; j++){
          z->chave[t+j] = y->chave[j];     //passar filho[i+1] para filho[i]
          z->nchaves++;
        }
        if(!z->folha){
          for(j=0; j<t; j++){
            z->filho[t+j] = y->filho[j];
          }
        }
        arv->nchaves--;
        arv->filho[i-1] = z;
        arv = remover(arv, ch, t);
        return arv;
      }
    }
  }
  arv->filho[i] = remover(arv->filho[i], ch, t);
  return arv;
  return NULL;
}

TABM* retira(TABM* arv, int k, int t){
  if(!arv || !Busca(arv, k)) return arv;
  return remover(arv, k, t);
  return NULL;
}

//////////////////////////////////////////////////////////

// FUNCOES TRABALHO
TABM* insereAluno(TABM *arvore){
    char nome[31], sobrenome[31];
    int matricula, ch, semestre;
    printf("\nInserindo aluno ... \n");
    printf("\nDigite o nome do aluno: ");
	scanf("%s %s", nome, sobrenome);
    printf("\nDigite a matricula do aluno: ");
    scanf("%d", &matricula);
    printf("\nDigite a CH do aluno: ");
    scanf("%d", &ch);
    printf("\nDigite o numero de semestres do aluno: ");
    scanf("%d", &semestre);
    TAluno* novoAluno = (TAluno*) (malloc(sizeof(TAluno)));
    strcat(nome, " ");
    strcat(nome, sobrenome);
    strcpy(novoAluno->nome, nome);
    novoAluno->matricula = matricula;
    novoAluno->ch = ch;
    novoAluno->semestre = semestre;
    arvore = Insere(arvore, novoAluno, t); // Insercao do novo aluno
    //printf ("\nNOVO ALUNO ADICIONADO (%s)\n", arvore->chave[0]->nome); ERA ASSIM, E Colocquei assim: //MARTELO
    printf ("\nNOVO ALUNO ADICIONADO (%s)\n", nome);
    return arvore;
}

TABM* removeAluno(TABM *arvore){
    int matricula;
    printf("\nRemovendo aluno ... \n");
    printf("Digite a matricula do aluno: ");
    scanf("%d", &matricula);
    arvore = retira(arvore, matricula, t);  
    return arvore;
}

void listaFormandos(TABM *a){
	if (a){
		int i;
		for (i=0; i<=a->nchaves-1; i++) {
		  listaFormandos(a->filho[i]);
		  if( (a->chave[i]->ch >= MAX_CH) && (a ->chave[i]->semestre < 13)//condição de ser formando
         && (a->folha) ) // testa se é folha
			printf("Matricula: %d  Nome:  %s  Semestre:  %d  Carga horaria:  %d\n",a ->chave[i]->matricula,a ->chave[i]->nome,a ->chave[i]->semestre, a ->chave[i]->ch);
		}
		listaFormandos(a->filho[i]);
  }
}

void listaJubilados(TABM *a){
    if (a){
		int i;
		for (i=0; i<=a->nchaves-1; i++) {
			listaJubilados(a->filho[i]);
			if( (((a->chave[i]->ch < MAX_CH) && (a ->chave[i]->semestre == 12) )//1ª condição de ser jubilado
         || ( (a->chave[i]->ch < MAX_CH/2) && (a ->chave[i]->semestre >= 8))) //2ª condição de ser jubilado
       && (a->folha) )// testa se é folha
				printf("Matricula: %d  Nome:  %s  Semestre:  %d  Carga horaria:  %d\n",a ->chave[i]->matricula,a ->chave[i]->nome,a ->chave[i]->semestre, a ->chave[i]->ch);
		}
		listaJubilados(a->filho[i]);
    }
}

void listaTodos(TABM *a){
    if (a){
		int i;
		for (i=0; i<=a->nchaves-1; i++) {
			listaTodos(a->filho[i]);
			if(a->folha) // testa se é folha
				printf("Matricula: %d  Nome:  %s  Semestre:  %d  Carga horaria:  %d\n",a ->chave[i]->matricula,a ->chave[i]->nome,a ->chave[i]->semestre, a ->chave[i]->ch);
		}
		listaTodos(a->filho[i]);
    }
}

void alteraCH(TABM* x){
    printf("\nentrou\n ");
    int matricula, novoCh, i=0;
    printf("Digite a matricula do aluno: \n");
    scanf("%d", &matricula);
    TABM *aux = Busca(x,matricula);
    if(aux) {
        while(i < aux->nchaves && matricula > aux->chave[i]->matricula) i++;
		printf("\nO aluno %d possui a CH = %d ",matricula,aux->chave[i]->ch);
		printf("\nDigite a nova CH do aluno: \n");
		scanf("%d",&novoCh);
		aux->chave[i]->ch = novoCh;
		printf("\nCH alterada com sucesso ! \n");
	}
}

void alteraSemestres(TABM* x){
    int matricula, novoSemestre, i=0;
    printf("Digite a matricula do aluno: ");
    scanf("%d", &matricula);
    TABM *aux = Busca(x,matricula);
    if(aux) {
        while(i < aux->nchaves && matricula > aux->chave[i]->matricula) i++;
		printf("\nO aluno %d esta no semestre %d :\n", matricula,aux->chave[i]->semestre);
		printf("\nDigite o novo semestre do aluno: \n");
		scanf("%d", &novoSemestre);
		aux ->chave[i]->semestre = novoSemestre;
		printf("\nSemestre alterado com sucesso !\n");
	}    
}

TABM* carregaArqTeste(char* nomeArq, TABM* a) {
	FILE *fp = fopen(nomeArq, "r");
	int mat, ch, sem;
	char nome[31], sobrenome[31];
	
	if(!fp)
		printf("\nArquivo de teste nao encontrado!\n");
	else {
		while(fscanf(fp, "%d %d %d %s %s", &mat, &ch, &sem, nome, sobrenome) == 5) {					
			TAluno* novoAluno = (TAluno*) (malloc(sizeof(TAluno)));
			strcat(nome, " ");
			strcat(nome, sobrenome);
			strcpy(novoAluno->nome, nome);
			novoAluno->matricula = mat;
			novoAluno->ch = ch;
			novoAluno->semestre = sem;
			a = Insere(a, novoAluno, t); // Insercao do novo aluno		
			printf ("\nNOVO ALUNO ADICIONADO (%s)\n", nome);	
		}	
	}
	fclose(fp);
	return a;

}

int main()
{
    int opcao, ch;
    TABM *arvore = Inicializa(), *xbusca = Inicializa();

    //listar Alunos formados (integralizar 100% da carga horaria em no máximo 12 semestres) (matricula, nome e numero de semestre)
    //listar alunos jubilados ( não integralizar 50% da CH em 8 semestres ou não integralizar 100% da CH em 12 semestres) (matricula, nome, ch, numero de semestre)
    //alterar CH e alterar numero de semestres
    
    arvore = carregaArqTeste("arq_teste.txt", arvore);
    while(1){
        printf("------------------ MENU ------------------ \n\n");
        printf("(1) Inserir aluno. \n");
        printf("(2) Remover aluno. \n");
        printf("(3) Listar formandos. \n");
        printf("(4) Listar jubilados. \n");
        printf("(5) Alterar carga horaria cursada. \n");
        printf("(6) Alterar numero de semestres. \n");
        printf("(7) Mostrar estrutura. \n");
        printf("(8) Buscar aluno. \n");
        printf("(9) Listar todos \n");
        printf("(0) Sair. \n");
        printf("\n\n----------------------------------------- \nEscolha: ");
        scanf("%d",&opcao);
        printf("\n");
        switch(opcao){
            case(1):
                arvore = insereAluno(arvore);
                break;

            case(2):
                arvore = removeAluno(arvore);
                break;

            case(3):
                listaFormandos(arvore);
                break;

            case(4):
                listaJubilados(arvore);
                break;

            case(5):
                alteraCH(arvore);
                break;

            case(6):
                alteraSemestres(arvore);
                break;

            case(7):
                Imprime(arvore, 0);
                break;

            case(8):
            	printf("\nDigite a matricula do aluno: ");
				scanf("%d", &ch);
				xbusca = buscaVet(arvore, ch);				
				break;

			case(9):
				listaTodos(arvore);
				break;

            case(0):
                Libera(arvore);
                exit(1);
                break;
        }
//        system("pause"); DESCOMENTAR AO RODAR NO WINDOWS
//        system("cls");
    }
    return 0;
}
