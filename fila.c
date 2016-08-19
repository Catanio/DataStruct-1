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
} Fila;

//inicia fila
void startFila(Fila *nomeDaFila){
	nomeDaFila->fim=NULL;
}

//checa se está vazia
int emptyCheck(Fila nomeDaFila){
	if(nomeDaFila.fim==NULL)
		return 1; //A fila está vazia
	else return 0;
}

void filaPop(Fila *fila, int dado){
	Node *temp=fila->fim;//se só tiver um elemento na fila, tem que tratar (segmentation fault)
	if(temp->next=NULL)
	{
		fila->fim=NULL;
		free(temp);
		return;
	}
	while(temp->next->next!=NULL){
		temp=tempnext;
	}//implementa no for
	free(temp->next);
	temp->next=NULL;
}	

void filaPush(Fila *fila, int dado){
	Node *noh;//criou o apontamento
	noh=(Node*)malloc(sizeof(Node));//cria a estrutura a partir do endereço
	noh.data=dado; 
	if (emptyCheck(fila)==1){
		fila->fim=&noh;
	}else{
		noh->next=fila->fim;
		fila->fim=noh;
	}
}

int main(argc, argv){
	
	
	return 0;
}
