#include <stdio.h>
#include <stdlib.h>
//eu percebi que vou escrevendo no automático em português, então decidi parar de deixar meu codigo meio inglês ahueuaehua

typedef struct node {
	int info;
	struct node *ant;
	struct node *prox;
} node;

node *inicializa () {
	return NULL;
}

void imprime (node *lista){
	node *temp;
	
	for (temp = lista; temp->prox != NULL; temp = temp->prox)
		printf("Info: %d\n", temp->info);

}

node *insere(node *lista, int info){
	node *novo = ( node * ) malloc ( sizeof ( node ) );
	node *temp = lista;
	novo->info = info;
	
	if ( temp == NULL ) {
		temp = novo;
		return temp;
	}
	//percorre a lista
	while(temp->prox != NULL && temp->info >= novo->info) {
		novo->ant = temp;
		temp = temp->prox;
	}
	//verifica se o temp parou na ultima posição
	if ( temp->info >= novo->info ) {
		novo->ant = temp;
		temp->prox = novo;
		return lista;
	}
	//verifica se ele foi inserido no meio da lista
	else if ( temp->info < novo->info && novo->ant != NULL) {
		novo->ant->prox = novo;
		temp->ant = novo;
		novo->prox = temp;
		return lista;
	}
	//caso anterior não seja diferente de null (^) então, temp parou no primeiro >
	else {
		temp->ant=novo;
		novo->prox = temp;
		return novo;
	}
}
int main (){
	node *l;
	l = inicializa();
	l = insere ( l, 2);
	l = insere ( l, 3);
	l = insere ( l, 1);
	l = insere ( l, 4);

	imprime(l);
	return 0;
}
