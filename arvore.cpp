#include <stdio.h>
#include <stdlib.h>

typedef struct arvore {
   char info;
   struct arvore *esq;
   struct arvore *dir;
} Arvore;


Arvore*  cria_arv_vazia (void);
Arvore*  arv_constroi (char c, Arvore* e, Arvore* d);
int      verifica_arv_vazia (Arvore* a);
Arvore*  arv_libera (Arvore* a);
int      arv_pertence (Arvore* a, char c);
void     arv_imprime (Arvore* a);

Arvore* cria_arv_vazia (void) {
   return NULL;
}

Arvore* arv_constroi (char c, Arvore* e, Arvore* d) {
  Arvore* a = (Arvore*)malloc(sizeof(Arvore));
  a->info = c;
  a->esq = e;
  a->dir = d;
  return a;
}

int verifica_arv_vazia (Arvore* a) {
  return (a == NULL);
}

Arvore* arv_libera (Arvore* a) {
  if (!verifica_arv_vazia(a)) {
    arv_libera (a->esq);
    arv_libera (a->dir);
    free(a);
  }
  return NULL;
}

int arv_conta (Arvore* a){
	if(!a) return(0);

	return(1 + arv_conta(a->esq) + arv_conta(a->dir));
}

int eh_espelho (Arvore* a, Arvore* b){
	int teste = 0;
	if(arv_conta(a) != arv_conta (b)) {
		printf("\nArvore assimetrica\n");
		return 0;
	}
	if(!a && !b) return 1;
	teste += eh_espelho(a->esq, b->dir);         
	teste += eh_espelho(a->dir, b->esq);
	if(a->info == b->info)
		return teste-1;
	else
		return 0;
}

/*Arvore* cria_espelho (Arvore* a) {
	Arvore *nova;
	if(a->dir != 0) 
		cria_espelho(a->dir);
	if(a->dir == 0 && a->esq == 0)
		nova = arv_constroi(a->info, cria_arv_vazia(), cria_arv_vazia());
	if(a->dir == 0 && a->esq != 0)
		nova = arv_constroi(a->info, cria_arv_vazia(), a->esq);
	if(a->dir != 0 && a->esq == 0)
		nova = arv_constroi(a->info, a->dir, cria_arv_vazia());
	if(a->dir != 0 && a->esq != 0)
		nova = arv_constroi(a->info, a->dir, a->esq);
	if(a->esq != 0)
		cria_espelho(a->esq);
	return nova;
}*/

Arvore* cria_espelho (Arvore* a) {
	Arvore *nova, *esq, *dir;
	if(!a) 
		nova = cria_arv_vazia();
	else {
		esq = cria_espelho(a->dir);
		dir = cria_espelho(a->esq);
		nova = arv_constroi(a->info, esq, dir);
	}
	return nova;
}

void arv_imprime (Arvore* a){
	if(!a) return;
	printf("%c ", a->info);    //Pré-ordem        a b d c e f             
	arv_imprime(a->esq);                                            
	//printf("%c ", a->info);      //In-ordem                        
	arv_imprime(a->dir);
	//printf("%c ", a->info);    //Pós-ordem        d b e f c a
}

void arv_imprime_invertida (Arvore* a){
	if(!a) return;
	printf("%c ", a->info);    //Pré-ordem
	arv_imprime_invertida(a->dir);         
	//printf("%c ", a->info);      //In-ordem
	arv_imprime_invertida(a->esq);
	//printf("%c ", a->info);    //Pós-ordem
}

int main (int argc, char *argv[]) {                                         
	Arvore *a, *a1, *a2, *a3, *a4, *a5, *a6;  														    
	Arvore *b, *b1, *b2, *b3, *b4, *b5, *b6;  
	Arvore *arvoreEspelho;  
	a6 = arv_constroi('g',cria_arv_vazia(),cria_arv_vazia());                                                 //           arvore a                     arvore b
	a1 = arv_constroi('d',cria_arv_vazia(),cria_arv_vazia());               //                  a                         a                  
	a2 = arv_constroi('b',a1,cria_arv_vazia());                             //            b          c               c         b 
	a3 = arv_constroi('e',cria_arv_vazia(),cria_arv_vazia());               //         d           e   f           f   e          d
	a4 = arv_constroi('f',cria_arv_vazia(),cria_arv_vazia());
	a5 = arv_constroi('c',a3,a4);
	
	a  = arv_constroi('a',a2,a5);
	
	b6 = arv_constroi('g',cria_arv_vazia(),cria_arv_vazia());                 // Testar valor diferente
	b1 = arv_constroi('d',cria_arv_vazia(),cria_arv_vazia());                                
	//b2 = arv_constroi('b',b6,b1);                             // teste valor diferente
	//b2 = arv_constroi('b',cria_arv_vazia(),cria_arv_vazia());                 // arvore assimetrica
	b2 = arv_constroi('b',cria_arv_vazia(),b1);                               // valor espelho        
	b3 = arv_constroi('e',cria_arv_vazia(),cria_arv_vazia());
	b4 = arv_constroi('f',cria_arv_vazia(),cria_arv_vazia());
	b5 = arv_constroi('c',b4,b3);
	b  = arv_constroi('a',b5,b2);
	
	printf("%d",arv_conta(a));
	printf("\n");
	printf("\nvalor de a:  ");
	arv_imprime(a);
	printf("\nvalor de b:  ");
	arv_imprime(b);
	printf("\nb invertido: ");
	arv_imprime_invertida(b);
	printf("\nb eh espelho de a? ");
	if(eh_espelho(a, b))
		printf("arvore b eh espelho de a\n");
	else
		printf("arvore b NAO eh espelho de a\n");
	printf("criar espelho: ");
	arvoreEspelho = cria_espelho(a);
	arv_imprime(arvoreEspelho);
  return 0;
}

