#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
				  
#define MAX_ELEMS 250 // MAX_ELEMS é o número máximo de elementos a serem sorteados para o arquivo mestre
					  // (o arquivo terá de 0 a MAX_ELEMS elementos)

#define MAX_OPERA 250 // MAX_OPERA é o número máximo de operações a serem sorteadas para o arquivo de transações
					  // (o arquivo terá de 0 a MAX_OPERA transações)

char * nomeAleatorio(char *nome); // Gera um nome aleatório
char * emailAleatorio(char *email); // Gera um email aleatório
void geraMestreAleatorio(char* mestre); // Gera um arquivo mestre aleatório com no máximo MAX_ELEMS elementos
void geraOperacoesAleatorias(char* transa); // Gera um arquivo de transações aleatório com no máximo MAX_ELEMS operações

typedef struct aluno {
  int mat;
  float cr;
  float pcc;				// Porcentagem de curso concluída
  int ai;					// Ano de ingresso
  char nome[31];
  char email[31];
} TAluno;

void balance_line(char* mestre, char *trans){
  FILE *fp_mestre = fopen(mestre, "r");
  if(!fp_mestre) exit(1);

  FILE *fp_trans = fopen(trans, "r");
  if(!fp_trans) exit(1);

  char erro[31], novo_mestre[31];
  strcpy(erro, "erro-");
  strcat(erro, mestre);  
  FILE *fp_erro = fopen(erro, "w");
  if(!fp_erro) exit(1);

  strcpy(novo_mestre, "novo-");
  strcat(novo_mestre, mestre);
  FILE *fp_novo_mestre = fopen(novo_mestre, "w");
  if(!fp_mestre) exit(1);

  int r, s;
  TAluno elem;
  int mat, ai;
  float cr, pcc;
  char acao[2], campo[5], nome[31], email[31];

  r = fscanf(fp_mestre, "%d %f %f %d %s %s", &elem.mat, &elem.cr, &elem.pcc, &elem.ai, elem.nome, elem.email);
  s = fscanf(fp_trans, "%d %s", &mat, acao);
  while((r == 6) && (s == 2)){
    if(elem.mat == mat){
      if(strcmp(acao, "I") == 0){       //erro        
        fscanf(fp_trans, "%f %f %d %s %s", &cr, &pcc, &ai, nome, email);        
        fprintf(fp_novo_mestre, "%d %.1f %.1f %d %s %s\n", elem.mat, elem.cr, elem.pcc, elem.ai, elem.nome, elem.email); 
        fprintf(fp_erro, "%d %s %.1f %.1f %d %s %s\n", mat, acao, cr, pcc, ai, nome, email);  
      }
      else if(strcmp(acao, "M") == 0){
        fscanf(fp_trans, "%s %f %s %f %s %d %s %s %s %s", campo, &cr, campo, &pcc, campo, &ai, campo, nome, campo, email);        
        fprintf(fp_novo_mestre, "%d %.1f %.1f %d %s %s\n", mat, cr, pcc, ai, nome, email);           
      }
      r = fscanf(fp_mestre, "%d %f %f %d %s %s", &elem.mat, &elem.cr, &elem.pcc, &elem.ai, elem.nome, elem.email);     
      s = fscanf(fp_trans, "%d %s", &mat, acao);
    }
    else if (elem.mat < mat){           //copia para o novo mestre
      fprintf(fp_novo_mestre, "%d %.1f %.1f %d %s %s\n", elem.mat, elem.cr, elem.pcc, elem.ai, elem.nome, elem.email);
      r = fscanf(fp_mestre, "%d %f %f %d %s %s", &elem.mat, &elem.cr, &elem.pcc, &elem.ai, elem.nome, elem.email);      
    }
    else{                               //trans e menor que mestre
      if(strcmp(acao, "I") == 0){       //inclusao de elemento
        fscanf(fp_trans, "%f %f %d %s %s", &cr, &pcc, &ai, nome, email);
        fprintf(fp_novo_mestre, "%d %.1f %.1f %d %s %s\n", mat, cr, pcc, ai, nome, email);        
      }
      else if(strcmp(acao, "M") == 0){  //erro
        fscanf(fp_trans, "%s %f", campo, &cr);
        fprintf(fp_erro, "%d %s %s %f ", mat, acao, campo, cr); 
        fscanf(fp_trans, "%s %f", campo, &pcc);
        fprintf(fp_erro, "%s %f", campo, pcc);
        fscanf(fp_trans, "%s %d", campo, &ai);
        fprintf(fp_erro, "%s %d", campo, ai); 
        fscanf(fp_trans, "%s %s", campo, nome);
        fprintf(fp_erro, "%s %s", campo, nome); 
        fscanf(fp_trans, "%s %s", campo, email);
        fprintf(fp_erro, "%s %s\n", campo, email); 
      }
      else fprintf(fp_erro, "%d %s\n", mat, acao); 
      s = fscanf(fp_trans, "%d %s", &mat, acao);
    }
  }  

  if(s == 2){       //acabou o mestre. Resto do trans para erro.
    while(s == 2){
      if(strcmp(acao, "I") == 0){       //inclusao de elemento
        fscanf(fp_trans, "%f %f %d %s %s", &cr, &pcc, &ai, nome, email);
        fprintf(fp_novo_mestre, "%d %.1f %.1f %d %s %s\n", mat, cr, pcc, ai, nome, email);         
      }
      else if(strcmp(acao, "M") == 0){  //erro
        fscanf(fp_trans, "%s %f", campo, &cr);
        fprintf(fp_erro, "%d %s %s %.1f ", mat, acao, campo, cr); 
        fscanf(fp_trans, "%s %f", campo, &pcc);
        fprintf(fp_erro, "%s %.1f", campo, pcc); 
        fscanf(fp_trans, "%s %d", campo, &ai);
        fprintf(fp_erro, "%s %d", campo, ai);
        fscanf(fp_trans, "%s %s", campo, nome);
        fprintf(fp_erro, "%s %s", campo, nome); 
        fscanf(fp_trans, "%s %s", campo, email);
        fprintf(fp_erro, "%s %s\n", campo, email);         
      }
      else fprintf(fp_erro, "%d %s\n", mat, acao); 
      s = fscanf(fp_trans, "%d %s", &mat, acao);
    }
  }

  if(r == 6){  //acabou o trans. Resto do mestre para novo_mestre
    fprintf(fp_novo_mestre, "%d %.1f %.1f %d %s %s\n", elem.mat, elem.cr, elem.pcc, elem.ai, elem.nome, elem.email);
    char lixo = fgetc(fp_mestre);
    while(1){
      char c = fgetc(fp_mestre);
      if(c == EOF) break;
      fputc(c, fp_novo_mestre);
    }
  }

  fclose(fp_mestre);
  fclose(fp_trans);
  fclose(fp_erro);
  fclose(fp_novo_mestre);
}


int main(int argc, char** argv){
  //if(argc != 3) exit(1);
  //balance_line(argv[1], argv[2]);
  geraMestreAleatorio("mestre");
  geraOperacoesAleatorias("transa");  
  balance_line("mestre", "transa");
  return 0;
}

char * nomeAleatorio(char *nome) {
	int i, sorteio;		
	for(i=0; i<30; i++) {								
		sorteio = rand() % 140;		
		char c = (char) (sorteio);
		if( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') )
			nome[i] = c;
		else
			--i;			
		if(sorteio < 5) break; // Chance de terminar a geração (para nao gerar sempre strings de tamanho maximo)
	}
	if(i < 2)
		return nomeAleatorio(nome);
	nome[i] = '\0';
	return nome;
}

char * emailAleatorio(char *email) {
	int i, sorteio;		
	for(i=0; i<20; i++) {								
		sorteio = rand() % 140;		
		char c = (char) (sorteio);
		if( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
			email[i] = c;
		else
			--i;			
		if(sorteio < 5) break; // Chance de terminar a geração (para nao gerar sempre strings de tamanho maximo)
	}
	if(i < 2)
		return emailAleatorio(email);
	email[i] = '@';	
	for(i=21; i<28; i++) {								
		sorteio = rand() % 140;		
		char c = (char) (sorteio);
		if( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') )
			email[i] = c;
		else
			--i;			
		//if(sorteio < 2) break; // Chance de terminar a geração (para nao gerar sempre strings de tamanho maximo)
	}	
	
		
	email[i] = '.';
	email[i+1] = 'c';
	email[i+2] = 'o';
	email[i+3] = 'm';
	email[i+4] = '\0';
	return email;
}

void geraMestreAleatorio(char* mestre) {
  FILE *fp_mestre = fopen(mestre, "w");
  if(!fp_mestre) exit(1);   
  
  int i, sorteio, mat, ai, qtd_elems;
  float cr, pcc;
  char *nome, *email;
  nome = (char *) malloc(31*sizeof(char));
  email = (char *) malloc(31*sizeof(char));

  srand(time(NULL));
  qtd_elems = rand() % MAX_ELEMS;  
  for(i=1; i<=qtd_elems; i++) {
	  mat = i;
	  cr = (float) (rand() % 100);
	  pcc = (float) (rand() % 100);
	  ai = (rand() % 14) + 2000;	  
	  nome = nomeAleatorio(nome);
	  email = emailAleatorio(email);
	  //printf("MAT: %d\n", mat);
	  //printf("CR: %.1f\n", cr);
	  //printf("PCC: %.1f\n", pcc);
	  //printf("AI: %d\n", ai);
	  //printf("NOME: %s\n", nome);
	  //printf("EMAIL: %s\n\n", email);
	  sorteio = rand() % 100;
	  if(sorteio < 75) // Chance do elemento ser adicionado
		fprintf(fp_mestre, "%d %.1f %.1f %d %s %s\n", mat, cr, pcc, ai, nome, email); 
  }
  printf("Quantidade de elementos gerados: %d\n", qtd_elems);      
  fclose(fp_mestre);  
}

void geraOperacoesAleatorias(char* transa) {
  FILE *fp_transa = fopen(transa, "w+");
  if(!fp_transa) exit(1);   
  
  int i, sorteio, opera_sorteada, mat, ai, qtd_opera;
  float cr, pcc;
  char *nome, *email, *acao;
  nome = (char *) malloc(31*sizeof(char));
  email = (char *) malloc(31*sizeof(char));

  srand(time(NULL));
  qtd_opera = rand() % MAX_OPERA;    
  for(i=1; i<=qtd_opera; i++) {
	  mat = i;
	  sorteio = rand() % 100;
	  //printf("Operacao sorteada para mat(%d): %s\n", mat, acao);	  	  
	  if(sorteio < 75) {		// Chance da operacao ser adicionada	  		
	  		opera_sorteada = rand() % 3;	  
	  		cr = (float) (rand() % 100);
	  		pcc = (float) (rand() % 100);
	  		ai = (rand() % 14) + 2000;	  
	  		nome = nomeAleatorio(nome);
	  		email = emailAleatorio(email);	  		
	  		if(opera_sorteada == 0) {
				acao = "I";
				fprintf(fp_transa, "%d %s %.1f %.1f %d %s %s\n", mat, acao, cr, pcc, ai, nome, email);				
			}
			else if(opera_sorteada == 1) {
				acao = "M";
				fprintf(fp_transa, "%d %s CR %.1f PCC %.1f AI %d NOME %s EMAIL %s\n", mat, acao, cr, pcc, ai, nome, email);	
			}
			else {
				acao = "E";
				fprintf(fp_transa, "%d %s\n", mat, acao);
			}			
		}
	}
	printf("Quantidade de operacoes geradas: %d\n", qtd_opera);
	fclose(fp_transa);  
}
