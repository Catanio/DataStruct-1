#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node *next;
} node;

node *startNode(){
	return NULL;
}

void imprime(node *noh){
	node *temp=noh;

	do {
		printf("informação: %d\n", temp->data);
		temp = temp->next;
	} while ( temp != noh );

}

node *insereCresc( node *lista, int dado ) {
	node *temp=lista, *anterior=NULL, *ultimo=lista;
	node *novo= (node *) malloc(sizeof(node));
	novo->data = dado;

	//verifica se está vazia a fila;
	if ( temp == NULL ) {
		temp = novo;
		temp->next=temp;
		return temp;
	}
	//move o ponteiro "ultimo" até um passo antes do primeiro objeto
	while (ultimo->next != lista)
		ultimo = ultimo->next;
	
	//verifica
	while ( temp->next != lista && temp->data <= novo->data ) {
		anterior = temp;
		temp = temp->next;
	}
	// a verificação é refeita, caso ele seja o maior numero inserido na lista
	// o "temp" vai parar antes do necessário
	if ( temp->data <= novo->data ) {
	//caso ele seja o último
		temp->next = novo;
		novo->next=lista;
		return lista;
	}
	// caso ele não seja o primeiro nem o ultimo
	else if ( temp->data > novo->data && anterior != NULL) {
		anterior->next = novo;
		novo->next = temp;
		return lista;
	}
	//caso ele seja o primeiro ( o menor, ou seja, anterior == NULL );
	else {
		novo->next = temp;
		ultimo->next = novo;
		return novo;
	}
}
//A implementação é basicamente a mesma da inserção crescente, mas com os indicadores lógicos inversos
node *insereDecresc( node *lista, int dado ) {
	node *temp=lista, *anterior=NULL, *ultimo=lista;
	node *novo= (node *) malloc(sizeof(node));
	novo->data = dado;

	if ( temp == NULL ) {
		temp = novo;
		temp->next=temp;
		return temp;
	}

	while (ultimo->next != lista)
		ultimo = ultimo->next;
	
	while ( temp->next != lista && temp->data >= novo->data ) {
		anterior = temp;
		temp = temp->next;
	}

	if ( temp->data > =novo->data ) {
		temp->next = novo;
		novo->next=lista;
		return lista;
	}
	else if ( temp->data < novo->data && anterior != NULL) {
		anterior->next = novo;
		novo->next = temp;
		return lista;
	}
	else {
		novo->next = temp;
		ultimo->next = novo;
		return novo;
	}
}


int main(){
	node *l;
	l = startNode();
	l = insereDecresc(l, 1);
	l = insereDecresc(l, 3);
	l = insereDecresc(l, 2);
	l = insereDecresc(l, 1);
	l = insereDecresc(l, 3);
	l = insereDecresc(l, 2);
	imprime(l);
	return 0;
}
