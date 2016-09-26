#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <stdbool.h>

struct Node{
	int numberLeft;
	int numberRight;

	struct Node *left;
	struct Node *right;
} typedef Node;

//variáveis globais - #proxima implementação poderá contar com ponteiros para ponteiros
//Foram selecionadas as variaveis globais por desconhecimento da utilidade de ponteiro para ponteiro
//Neste cenário, não seria possível fazer dois retornos por função (havia sido pensada uma função "pull")
	//qual iria retirar um nó de uma lista e retornar em outra - tendo que atualizar os dois endereços.
Node *playerHand=NULL, *machineHand=NULL, *mesa=NULL, *monte=NULL;

//Função que conta quantos elementos há em uma lista
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



//usado em "criaPecas"
Node *insereInicio (Node *pilha, int left, int right){
	Node *noh = (Node *) malloc (sizeof(Node));
	noh->numberLeft = left;
	noh->numberRight = right;

	//Se estiver vazia
	if (pilha == NULL) {
		noh->right=NULL;
		noh->left=NULL;
		return noh;
	}
	//se não
	else {
		pilha->left = noh;
		noh->right = pilha;
		noh->left = NULL;
		return noh;
	}
}

//Função que inicia o "deck" de peças de dominó
Node *criaPecas () {
	int i, j;

	Node *domino = NULL;

	for (i=0; i<=6; i++){
		for (j=i; j<=6; j++) {
			domino = insereInicio(domino, i, j);
		}
	}
	return domino;
}

//função que limpa a lista por completo
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

//Função que copia uma lista duplamente encadeada para um array
//recebe o cabeçalho da lista e o endereço onde vai ser armazenada a quantidade de elementos
	//e retorna o cabeçalho do array
Node *toArray(Node *noh, int *quantidade) {
	Node *pecas, *temp=noh;
	int i=0, tamanhoDaLista;

	*quantidade = contaLista(temp);
	tamanhoDaLista=contaLista(temp);
	if (quantidade == 0)
		return NULL;


	pecas=(Node *) malloc (tamanhoDaLista * sizeof (Node));

	while (temp->right != NULL ) {
		pecas[i]=*temp;
		temp=temp->right;
		i++;
	}
	pecas[i]=*temp;
	return pecas;
}

//função que embaralha as peças
//recebe o cabeçalho da lista e retorna ela atualizada
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

	pecas=NULL;//inicializa pecas
	for (i=0; i<28; i++) {
		pecas=insereInicio(pecas,vBaralho[i].numberLeft, vBaralho[i].numberRight);
	}
	return pecas;
}
//função que pesca uma peça do monte de dominós
//recebe a lista que vai receber a peça do monte
Node *pescaDoMonte (Node *noh) {
	if (monte==NULL){
		printf("Não Existem peças para pescar!\n");
		return noh;
	}

	Node *aux=monte;
	monte=monte->right;
	if(monte!=NULL)
		monte->left=NULL;
	noh->left = aux;
	aux->right=noh;

	return aux;

}
//função que distribui as peças, seis para o jogador, seis para a máquina e um para a mesa.
//recebe um deck embaralhado e retorna o resto do deck, depois de distribuir
Node *distribui(Node *pecas) {
		int i;

		//distribui para mão do jogador
		for (i=0; i<=6; i++) {
			playerHand=insereInicio(playerHand, pecas->numberLeft, pecas->numberRight);
			pecas=pecas->right;
			free(pecas->left);
			pecas->left=NULL;
		}
		//distribui para a mão da maquina
		for (i=0; i<=6; i++) {
			machineHand=insereInicio(machineHand, pecas->numberLeft, pecas->numberRight);
			pecas=pecas->right;
			free(pecas->left);
			pecas->left=NULL;
		}

		return pecas;
}
//funcao que mostra a mao

//inicializa
//ITS ALIVE
void inicializa () {
	Node *pecas=NULL;
	pecas=criaPecas();
	pecas=embaralha(pecas);
	monte=distribui(pecas);

}

//checa se há peças a serem jogadas.

//quem é o primeiro a jogar?
/*Inicia o jogo quem tiver o duplo-6 (peça com o numero 6 nas suas duas metades)
 Caso esta peça não tenha sido entregue a nenhum jogador, iniciará aquele que tiver a peça dupla maior*/
int primeiraJogada() {
	Node *temp, *maiorM, *maiorP;
	int maiorDuplaPlayer=0, maiorDuplaMaquina=0;

	for (temp=playerHand;temp!=NULL; temp=temp->right){
		if(temp->numberLeft==6 && temp->numberRight==6){
			mesa=temp;
			temp->left->right=temp->right;
			temp->right->left=temp->left;
			temp->right=NULL;
			temp->left=NULL;
			return 1;
		}
		if (temp->numberLeft == temp->numberRight){
		 maiorDuplaPlayer = temp->numberLeft;
		 maiorP=temp;
		}

	}

	for (temp=machineHand;temp!=NULL; temp=temp->right){
		if(temp->numberLeft==6 && temp->numberRight==6){
			mesa=temp;
			temp->left->right=temp->right;
			temp->right->left=temp->left;
			temp->right=NULL;
			temp->left=NULL;
			return 0;
		}

		if (temp->numberLeft == temp->numberRight){
		 maiorDuplaMaquina = temp->numberLeft;
		 maiorM=temp;
		}
	}
	if (maiorDuplaMaquina>maiorDuplaPlayer){
		mesa=maiorM;
		maiorM->left->right=maiorM->right;
		maiorM->right->left=maiorM->left;
		maiorM->right=NULL;
		maiorM->left=NULL;
		return 0;
	}
	else {
		mesa=maiorP;
		maiorP->left->right=maiorP->right;
		maiorP->right->left=maiorP->left;
		maiorP->right=NULL;
		maiorP->left=NULL;
		return 1;
	}

}

void imprimePecas(Node *pecas) {
	Node *temp = pecas;
		while(temp!=NULL) {
		printf("(%d~%d)", temp->numberLeft, temp->numberRight);
			temp=temp->right;
	}
	printf("\n");
}

void jogando(){
	Node *temp=mesa;
	int primeiroNumero=temp->numberLeft, ultimoNumero, jogaOuPesca;//joga = 1, pesca = 0;

	//Salva os dois números das extremidades da lista de dominós na mesa.
	while (temp!=NULL){
		ultimoNumero=temp->numberRight;
		temp=temp->right;
	}

	do{
		for(temp=playerHand; temp!=NULL; temp=temp->right){
			if(temp->numberLeft == primeiroNumero || temp->numberRight == primeiroNumero || temp->numberLeft == ultimoNumero || temp->numberRight == ultimoNumero){
				jogaOuPesca=1;
				break;
			}
			else jogaOuPesca = 0;
		}
	} while (pesca == 0);
	imprimePecas(playerHand);
	printf("fazer o que? :");
	scanf("%d", &jogada);
}

int main() {
	Node *pecas=NULL;
	int joga;

	inicializa();
	joga=primeiraJogada();

	//1 = maquina joga; 0 = Player joga
	do{
		system("clear");
		imprimePecas(mesa);
		if (joga == 0){

			if(contaLista(playerHand)==0){
				system("clear");
				printf("\nVocê Ganhou!");
				break;
			}
			else joga=1;
			//jogando();
		}


		else if (joga == 1){
			
			if(contaLista(machineHand)==0){
				
			}
			else joga = 0;
			//AI();
		}

	} while (1);

	system("clear");


	printf("pecas da mão: %d: ", contaLista(playerHand));
	imprimePecas(playerHand);
	printf("\n\npecas da maquina: %d: ", contaLista(machineHand));
	imprimePecas(machineHand);
	printf("\n\npecas do monte: %d: ", contaLista(monte));
	imprimePecas(monte);
	printf("\n\npecas da mesa: %d: ", contaLista(mesa));
	imprimePecas(mesa);
	
 
 
	return 0;
}
