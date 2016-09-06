#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
	int info;
	struct lista *prox;
}Tplista;


Tplista *inicializa(){
	return NULL;
}

Tplista *insereini(Tplista *l, int e){
	Tplista *novo = (Tplista *)malloc(sizeof(Tplista));
	novo->info = e;
	novo->prox = l;
	return novo;
}

void imprime(Tplista *l){
	Tplista *p;
	for(p = l; p != NULL; p = p->prox){
		printf("Informacao: %d\n", p->info);
	}
}

Tplista *exclui(Tplista *l, int e){
	Tplista *anterior = NULL;
	Tplista *p = l;
	
	while(p != NULL && p->info != e){
		anterior = p;
		p = p->prox;
	}
	
	if (p == NULL){
		return l;
	}
	
	if (anterior == NULL){
		l = p->prox;
	}else{
		anterior->prox = p->prox;
	}
	
	free(p);
	return l;
}
Tplista *inserecresc ( Tplista *lista, int dado ) {
	Tplista *temp=lista, *anterior=NULL;
	Tplista *novo= (Tplista *) malloc(sizeof(Tplista));
	novo->info = dado;

	//verifica se está vazia a fila;
	if ( temp == NULL ) {
		temp = novo;
		return temp;
	}
	
	while (temp->prox != NULL && temp->info < novo->info ) {
		anterior = temp;
		temp = temp->prox;
	}
	// a verificação é refeita, caso ele seja o maior numero inserido na lista
	// o "temp" vai parar antes do necessário
	if ( temp->info < novo->info ) {
		temp->prox = novo;
		return lista;
	}// caso ele não seja o primeiro
	else if ( temp->info > novo->info && anterior != NULL) {
		anterior->prox = novo;
		novo->prox = temp;
		return lista;
	} //caso ele seja o primeiro ( o menor, ou seja, anterior == NULL );
	else {
		novo->prox = temp;
		return novo;
	}

		
}
Tplista *inseremeio(Tplista *l, int e, int n){
	Tplista *p=l, *anterior = NULL;
	Tplista *novo = (Tplista *)malloc(sizeof(Tplista));
	novo->info = n;
	
	while(p != NULL &&  p->info != e){
		anterior = p;
		p = p->prox;
	}
	
	if(anterior != NULL && anterior->prox != NULL){
		anterior->prox = novo;
		novo->prox = p;
		return l;
	}
	return l;
}

Tplista *inserefim(Tplista *l, int e){
	Tplista *p = l;
	Tplista *novo = (Tplista *)malloc(sizeof(Tplista));
	novo->info = e;
	
	while(p->prox != NULL){
		p = p->prox;
	}
	
	p->prox = novo;
	novo->prox = NULL;
	return l;
}

int main(){
	Tplista *l;
	l = inicializa();
	l = insereini(l, 1);
	l = inserefim(l, 3);
	l = inserecresc(l, 2);
	imprime(l);
	return 0;
}
