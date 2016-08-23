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

void push(Pilha *pilha, int dado){
	Node *noh=(Node*)malloc(sizeof(Node));//criou o apontamento
	noh->data=dado; 
	if (emptyCheck(pilha)==1){
		pilha->head=noh;//se a pilha estiver vazia, joga o nó para a primeira posição
	}else{
		noh->next=pilha->head;//o novo nó recebe o endereço do nó que estava apontado pelo cabeçalho
		pilha->head=noh;//e o cabelhaço recebe o endereço do novo nó
	}
}


int pop(Pilha *pilha){
	Node *temp=pilha->head;
	if(!emptyCheck(pilha)){
		int dado=temp->data;
		pilha->head=temp->next;
		free(temp);
		return dado;
	}
	else return 0;

}	
void menu(){
	printf("1 - inicia Pilha\n");
	printf("2 - push na Pilha\n");
	printf("3 - pop na Pilha\n");
	printf("5 - mostra a pilha\n");
}

int main(argc, argv){
	
	Pilha pilha;
	int exit, op, data;
	printf("digite um comando invalido para sair\n");
	do{	
	menu();
	exit=scanf("%d", &op);
	if (op==1){
		startPilha(&pilha);
	}
	else if(op==2){
		printf("qual número botar na pilha? ");
		scanf("%d", &data);
		push(&pilha, data);
	}
	else if(op==3){
		if (emptyCheck(&pilha))
			printf("pilha vazia!\n");
		else
			printf("%d tirado da pilha!\n", pop(&pilha));
	}
	else if(op==4){
		printf("ainda não implementado!\n");
	}

	}while(exit || op >4 || op<1);
	return 0;
}
