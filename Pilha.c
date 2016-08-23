#include <stdio.h>
#include <stdlib.h>

//estrutura do nó
typedef struct {
	int data;
	struct Node *next;
} Node;

//estrutura da pilha
typedef struct{
	Node *head;
} Pilha;

//inicia pilha
void startPilha(Pilha *nomeDaPilha){
	nomeDaPilha->head=NULL;
}

//checa se está vazia
int emptyCheck(Pilha *nomeDaPilha){
	if(nomeDaPilha->head==NULL)
		return 1; //A pilha está vazia
	else return 0;
}

void Push(Pilha *pilha, int dado){
	Node *noh=(Node*)malloc(sizeof(Node));//criou o apontamento
	noh->data=dado; 
	if (emptyCheck(pilha)==1){
		pilha->head=noh;//se a pilha estiver vazia, joga o nó para a primeira posição
	}else{
		noh->next=pilha->head;//o novo nó recebe o endereço do nó que estava apontado pelo cabeçalho
		pilha->head=noh;//e o cabelhaço recebe o endereço do novo nó
	}
}


int Pop(Pilha *pilha){
	Node *temp=pilha->head;
	if(!emptyCheck(pilha)){
		int dado=temp->data;
		pilha->head=temp->next;
		free(temp);
		return dado;
	}
	else{
		printf("a pilha está vazia! o retorno é 0");
		return 0;
	}
}	


int main(argc, argv){
	
	return 0;
}
