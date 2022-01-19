#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct info {
    int mat;
    char nome[51];
    int ch, num_sem;
} TInfo;

typedef struct abm {
    //int *chave;
    //TInfo **info_folha;
    TInfo **chave;
    int nchaves, folha;
    struct abm **filho, *prox;
} TABM;

void mostra_menu () {
    printf ("\n\nCadastro de alunos da UFXX\n\nO que voce deseja fazer?\n\n");
    printf ("\t1- Inserir alunos\n");
    printf ("\t2- Remover alunos\n");
    printf ("\t3- Mostrar alunos jubilados\n");
    printf ("\t4- Mostrar alunos formandos\n");
    printf ("\t5- Mostrar todos os alunos\n");
    printf ("\t6- Sair\n");
}

void Imprime(TABM *a, int andar){
  if (a){
    int i,j;
    for (i=0; i<=a->nchaves-1; i++) {
      Imprime(a->filho[i],andar+1);
      for(j=0; j<=andar; j++) printf("   ");
      printf("%d-%s\n", a->chave[i]->mat, a->chave[i]->nome);
    }
    Imprime(a->filho[i],andar+1);
  }
}

TABM *Busca(TABM* x, int ch){
  TABM *resp = NULL;
  if(!x) return resp;
  int i = 0;
  while(i < x->nchaves && ch > x->chave[i]->mat) i++;
  if(i < x->nchaves && ch == x->chave[i]->mat) return x;
  if(x->folha) return resp;
  return Busca(x->filho[i], ch);
}

void retira () {
}

TABM *Cria(int t) {
  TABM* novo = (TABM *)malloc(sizeof(TABM));
  novo->nchaves = 0;
  novo->chave =(TInfo *)malloc(sizeof(TInfo *)*((t*2)-1));
  novo->folha=1;
  novo->filho = (TABM **)malloc(sizeof(TABM *)*t*2);
  int i;
  for(i=0; i<(t*2); i++) novo->filho[i] = NULL;
  return novo;
}

TABM *Divisao(TABM *x, int i, TABM *y, int t) {
  printf ("Divisao!\n");
  printf ("Imprimindo x:\n");
  Imprime(x, 0);
  printf ("Imprimindo y:\n (y->folha: %d | y->chave[2]->mat: %d)\n", y->folha, y->chave[2]->mat);
  Imprime(y, 0);

  TABM *z=Cria(t);
  z->nchaves= t - 1;
  z->folha = y->folha;
  int j;
  for(j=0; j < t-1; j++) z->chave[j] = y->chave[j+t];
  if(!y->folha){
    for(j=0;j<t;j++){
      z->filho[j] = y->filho[j+t];
      y->filho[j+t] = NULL;
    }
  }
  y->nchaves = t-1;
  for(j = x->nchaves; j >= i; j--) x->filho[j+1]=x->filho[j];
  x->filho[i] = z;
  for(j=x->nchaves; j>=i; j--) x->chave[j] = x->chave[j-1];
  x->chave[i-1] = y->chave[t-1];
  x->nchaves++;

printf ("y->chave[0]->mat: %d\n", y->chave[0]->mat);
printf ("y->chave[1]->mat: %d\n", y->chave[1]->mat);
printf ("y->chave[2]->mat: %d\n", y->chave[2]->mat);
y->nchaves++;

y->prox = z;

printf ("y->prox->chave[0]->mat: %d\n", y->prox->chave[0]->mat);

  return x;
}

TABM *Insere_Nao_Completo(TABM *x, TInfo *k, int t){
  int i = x->nchaves-1;
  if(x->folha){
    while((i>=0) && (k->mat < x->chave[i]->mat)){
      x->chave[i+1] = x->chave[i];
      i--;
    }
    x->chave[i+1] = k;
    x->nchaves++;
    return x;
  }
  while((i>=0) && (k->mat < x->chave[i]->mat)) i--;
  i++;
  if(x->filho[i]->nchaves == ((2*t)-1)){
    x = Divisao(x, (i+1), x->filho[i], t);
    if(k->mat > x->chave[i]->mat) i++;
  }
  x->filho[i] = Insere_Nao_Completo(x->filho[i], k, t);
  return x;
}

TABM * Insere(TABM *T, TInfo *k, int t) {
  if (Busca(T, k->mat)) return T;

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

void mostra_jubilados () {
}

void mostra_formandos () {
}

void mostra_todos () {
}

int main () {
  int t = 2;
  TABM *arvore = NULL;

  int op = 0;
  int mat, ch, num_sem;
  char nome[51];

  while (op != 6) {
    mostra_menu();
    scanf ("%d", &op);

    switch (op) {
      case 1:
        printf ("Digite o nome do aluno: ");
        scanf ("%s", nome);
        printf ("Digite a matricula do aluno: ");
        scanf ("%d", &mat);
        printf ("Digite o numero de semestres do aluno: ");
        scanf ("%d", &num_sem);
        printf ("Digite a carga horaria cursada do aluno: ");
        scanf ("%d", &ch);

        TInfo *aluno = (TInfo *) malloc (sizeof (TInfo));
        strcpy (aluno->nome, nome);
        aluno->mat = mat;
        aluno->num_sem = num_sem;
        aluno->ch = ch;

        arvore = Insere(arvore, aluno, t);

        printf ("Aluno adicionado: %s\n", arvore->chave[0]->nome);
        break;
      case 2:
        retira ();
        break;
      case 3:
        mostra_jubilados ();
        break;
      case 4:
        mostra_formandos ();
        break;
      case 5:
        //mostra_todos ();
        Imprime (arvore, 0);
        break;
      default:
        break;
    }
  }
  printf ("\nAte a proxima!\n");
}
