#include <stdio.h>
#include <stdlib.h>

//estrutura do nó
typedef struct {
	int data;
	struct Node *next;
} Node;

//estrutura da fila
typedef struct{
	Node *fim;
	Node *inicio;
} Fila;

//inicia fila
void startFila(Fila nomeDaFila){
	nomeDaFila.fim=NULL;
	nomeDaFila.inicio=NULL;
}

//checa se está vazia
int emptyCheck(Fila nomeDaFila){
	if(nomeDaFila.fim==NULL)
		return 1; //A fila está vazia
	else return 0;
}

int filaPop(Fila fila, int dado){
	int *noh, dado;
	noh=&fila.inicio;
	dado=noh.data;

	noh.next=&(fila.fim);
	fila.fim=&noh;

	if (emptyCheck(fila)==1)
		return 1;
	free(noh)
	return dado;
}	

void filaPush(Fila fila, int dado){
	Node noh;
	noh.data=dado;
	noh.next=&(fila.inicio);
	fila.inicio=&noh;

	if (emptyCheck(fila)==1)
		fila.fim=&noh;

}

int main(argc, argv){
	
	return 0;
}
