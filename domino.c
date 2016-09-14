#include <stdio.h>
#include <stdlib.h>

struct Node{
	int numberLeft;
	int numberRight;

	struct Node *left;
	struct Node *right;
	//O right é usado como "next" em caso de implementação de estrutura em pilhas
	//Caso contrário, funciona normalmente como lista duplamente encadeada
} typedef Node;

int contaLista (Node *lista) {
	Node *temp = lista;
	int count = 1;

	if (lista == NULL)
		return 0;

	while (temp->right != NULL) {
		temp=temp->right;
		count++;
	}
	return count;
}

void desenhaMao (Node *mao) {
	int i, j, count, qtd;
	qtd = 1;//contaLista(mao)//desenha no maximo 18

//2,3,4- j (left), 6,7,8 - (right)
	for(i=0 ; i <=4 ; i++) {
		for (count = 1; count <= qtd ; count ++) {
			for (j = 0; j<= 8 ; j++ ) {
				if( ( i==0 || i==4 ) && j != 0 && j != 8 )
					printf("-");
				else if ( (i == 1 || i == 2 || i == 3) && (j == 0 || j == 4 || j == 8) )
					printf("|");
				//else printf(" ");

				//Desenha as bolinhas primeira linha
				if ( (i == 1) ) {
					if ( j == 1) {
						if ( domino[count-1]->numberLeft > 1 && domino[count-1]->numberLeft < 7 )
							printf("o");
						else printf(" ");
					}

					else if ( j == 3 ) {
						if ( domino[count-1]->numberLeft > 3 && domino[count-1]->numberLeft < 7 )
							printf("o");
						else printf(" ");
					}
					if ( j == 5) {
						if ( domino[count-1]->numberLeft > 1 && domino[count-1]->numberLeft < 7 )
							printf("o");
						else printf(" ");
					}

					else if ( j == 7 ) {
						if ( domino[count-1]->numberLeft > 3 && domino[count-1]->numberLeft < 7 )
							printf("o");
						else printf(" ");
					}
				}
				//segunda linha
				else if ( (i == 2) ) {

				}
				//terceira linha
				else if ( (i == 3) ) {

				}
			}
		}
		if(count < qtd && count != 18)//como o max por lin
			printf("  ");
		else
			printf("\n");
	}
}

if ( (domino[count-1]->numberLeft > 1 && domino[count-1]->numberLeft < 7) || if ( domino[count-1]->numberRight > 1 && domino[count-1]->numberRight < 7 )){
	if (j == 1 || j == 3 || j == 5 || j == 7)
		printf("o");
}
else ( j>0 && j<8 || j!=4 ) 
	printf(" ");


//Checa se vazio; Caso sim retorna 1
int emptyCheck(Node *node){
	if (node == NULL )
		return 1;
	else return 0;
}

//Estruturas de Pilha
Node *push (Node *pilha, int left, int right){
	Node *noh = (Node *) malloc (sizeof(Node));
	noh->numberLeft = left;
	noh->numberRight = right;

	if (emptyCheck(pilha))
		return noh;
	else {
		noh->right = pilha;
		return noh;
	}
}

Node *pop(Node *pilha) {
	Node *noh;

	if(emptyCheck(pilha))
		return NULL;
	else {
		noh = pilha->right;
		free(pilha);
		return noh;
	}
}


//Função que inicia o "deck" de peças de dominó
Node *criaPecas () {
	int i, j;

	Node *domino = NULL;

	for (i=0; i<=6; i++){
		for (j=0; j<=6; j++) {
			domino = push(domino, i, j);
		}
	}
	return domino;
}
//função que embaralha as peças

//função que distribui as peças
	
//funcao que mostra a mao

Node *playerHand=NULL, *machineHand=NULL, *board=NULL;
int main() {
	Node *noh = (Node *) malloc (sizeof(Node));
	desenhaMao(noh);

	return 0;
}
