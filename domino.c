#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct Node{
	int numberLeft;
	int numberRight;

	struct Node *left;
	struct Node *right;
	//O right é usado como "next" em caso de implementação de estrutura em pilhas
	//Caso contrário, funciona normalmente como lista duplamente encadeada
} typedef Node;


//Ok!
//usada na função toArray e desenhaMao
int contaLista (Node *lista) {
	Node *temp = lista;
	int count = 1;

	if (lista == NULL)
		return 0;
	else {

		while (temp->right != NULL) {
			temp=temp->right;
			count++;
		}
		return count;
	}
}

//NOTK
void desenhaMao (Node *mao) {
	int i, j, count, qtd;
	qtd = 10;//contaLista(mao)//desenha no maximo 18

//2,3,4- j (left), 6,7,8 - (right)
	for(i=0 ; i <=4 ; i++) {
		for (count = 1; count <= qtd ; count ++) {
			for (j = 0; j<= 8 ; j++ ) {
				if( ( i==0 || i==4 ) && j != 0 && j != 8 )
					printf("-");
				else if ( (i == 1 || i == 2 || i == 3) && (j == 0 || j == 4 || j == 8) )
					printf("|");
				else printf(" ");//substituir por impressão de peças

			}
		}
		if(count <= qtd )//falta arrumar o condicional pra pular a linha
			printf(":");
		else
			printf("\n");
	}
}
/*
if ( (domino[count-1]->numberLeft > 1 && domino[count-1]->numberLeft < 7) || if ( domino[count-1]->numberRight > 1 && domino[count-1]->numberRight < 7 )){
	if (j == 1 || j == 3 || j == 5 || j == 7)
		printf("o");
}
else ( j>0 && j<8 || j!=4 ) 
	printf(" ");
*/

//OK
//Checa se vazio; Caso sim retorna 1
int emptyCheck(Node *node){
	if (node == NULL )
		return 1;
	else return 0;
}

//Estruturas de Pilha
//OK! (checked)
//usado em "criaPecas"
Node *push (Node *pilha, int left, int right){
	Node *noh = (Node *) malloc (sizeof(Node));
	noh->numberLeft = left;
	noh->numberRight = right;

	if (pilha == NULL)
		return noh;
	else {
		pilha->left = noh;
		noh->right = pilha;
		noh->left = NULL;
		return noh;
	}
}

//OK!
//Função que inicia o "deck" de peças de dominó
Node *criaPecas () {
	int i, j;

	Node *domino = NULL;

	for (i=0; i<=6; i++){
		for (j=i; j<=6; j++) {
			domino = push(domino, i, j);
		}
	}
	return domino;
}
//É pra estar OK..
void limpaLista (Node *temp) {
	Node *anterior=NULL;
	
	while (temp->right != NULL) {
		anterior=temp;
		temp=temp->right;
		anterior=NULL;
		free(anterior);
	}
	free(temp);

}

//função to array
//AE CARALHO FUNCIONANDO ITS ALIVE ITS ALIVE ITS ALIVE
Node *toArray(Node *noh, int *quantidade) {
	Node *pecas, *temp=noh;
	int i=0, gambiarra;

	*quantidade = contaLista(temp);//tá chow
	gambiarra=contaLista(temp);
	if (quantidade == 0)
		return NULL;


	pecas=(Node *) malloc (gambiarra * sizeof (Node));

	while (temp->right != NULL ) {
		pecas[i]=*temp;
		temp=temp->right;
		i++;
	}
	pecas[i]=*temp;
	return pecas;
}

//função que embaralha as peças
//quase OK, falta transformar o array em LISTA
Node *embaralha(Node *pecas) {
	srand( (unsigned)time(NULL));
	Node *vPecas, *vBaralho=(Node *)malloc(28*(sizeof(Node)));
	int i, ri, count=0;

	vPecas = toArray(pecas, &i);
	limpaLista(pecas);

	// esse while vai distribuir do vetor ordenado para um vetor aleatório
	while (count <28) {
		ri = rand()%28;
		if (vPecas[ri].numberRight != -1) {
			vBaralho[count]=vPecas[ri];
			vPecas[ri].numberRight=-1;
			count++;
		}
	}

	pecas=NULL;
	for (i=0; i<28; i++) {
		pecas=push(pecas,vBaralho[i].numberLeft, vBaralho[i].numberRight);
	}
	//ao final dele, espera-se que haja um vetor (vBaralho) com dominós aleatoriamente
	return pecas;

}

//função que distribui as peças
	
//funcao que mostra a mao

Node *playerHand=NULL, *machineHand=NULL, *board=NULL;
int main() {
	//Node *noh = (Node *) malloc (sizeof(Node));
	Node *pecas=NULL;
	int i=0;



	pecas=criaPecas();
	Node *temp = pecas;
	i=contaLista(pecas);
	printf("quantidade: %d\n", i);
	while(temp->right!=NULL) {
		printf("(%d~%d)", temp->numberLeft, temp->numberRight);
		temp=temp->right;
	}
	printf("(%d~%d)\n", temp->numberLeft, temp->numberRight);

	printf("depois de embaralhar: \n");
	pecas=embaralha(pecas);
	i=contaLista(pecas);
	printf("quantidade: %d\n", i);
	temp=pecas;
	while(temp->right!=NULL) {
		printf("(%d~%d)", temp->numberLeft, temp->numberRight);
			temp=temp->right;
	}
	printf("(%d~%d)\n", temp->numberLeft, temp->numberRight);


	return 0;
}
