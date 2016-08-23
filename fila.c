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
int emptyCheck(Fila *nomeDaFila){
	if(nomeDaFila->fim==NULL)
		return 1; //A fila está vazia
	else return 0;
}

void filaPush(Fila *fila, int dado){
	Node *noh=(Node*)malloc(sizeof(Node));//criou o apontamento
	noh->data=dado; 
	if (emptyCheck(fila)==1){
		fila->fim=noh;
	}else{
		noh->next=fila->fim;
		fila->fim=noh;
	}
}


void filaPop(Fila *fila, int dado){
	Node *temp=fila->fim, *ant;//se só tiver um elemento na fila, tem que tratar (segmentation fault)
	if(temp->next=NULL)
	{
		fila->fim=NULL;
		free(temp);
		return;
	}
	while(temp->next!=NULL){
		ant=temp;		
		temp=temp->next;
	}//implementa no for
	
	free(temp);
	ant->next=NULL;
}	


int main(argc, argv){
	
	return 0;
}
