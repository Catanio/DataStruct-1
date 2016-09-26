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

//variáveis globais
Node *playerHand=NULL, *machineHand=NULL, *mesa=NULL, *monte=NULL;


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


//Estruturas de Pilha
//OK! (checked)
//usado em "criaPecas"
Node *push (Node *pilha, int left, int right){
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
//
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
    pecas=push(pecas,vBaralho[i].numberLeft, vBaralho[i].numberRight);
  }
  return pecas;
}
//função pesca

//função que distribui as peças, seis para o jogador, seis para a máquina e um para a mesa.
//recebe um deck embaralhado e retorna o resto do deck, depois de distribuir
Node *distribui(Node *pecas) {
    int i;

    //distribui para mão do jogador
    for (i=0; i<=6; i++) {
      playerHand=push(playerHand, pecas->numberLeft, pecas->numberRight);
      pecas=pecas->right;
      free(pecas->left);
      pecas->left=NULL;
    }
    //distribui para a mão da maquina
    for (i=0; i<=6; i++) {
      machineHand=push(machineHand, pecas->numberLeft, pecas->numberRight);
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
  Node *temp;
  int maiorDuplaPlayer=0, maiorDuplaMaquina=0;

  for (temp=playerHand;temp!=NULL; temp=temp->right){
    if (temp->numberLeft == temp->numberRight)
     maiorDuplaPlayer = temp->numberLeft;
    if(temp->numberLeft==6 && temp->numberRight==6)
      return 1;
  }

  for (temp=machineHand;temp!=NULL; temp=temp->right){
    if (temp->numberLeft == temp->numberRight)
     maiorDuplaMaquina = temp->numberLeft;
    if(temp->numberLeft==6 && temp->numberRight==6)
      return 0;
  }
  if (maiorDuplaMaquina>maiorDuplaPlayer)
    return 0;
  else return 1;

}

// 0 = máquina, 1 = jogador; rodada while com inversão de i ao final

void imprimePecas(Node *pecas) {
  Node *temp = pecas;
    while(temp!=NULL) {
    printf("(%d~%d)", temp->numberLeft, temp->numberRight);
      temp=temp->right;
  }
  printf("\n");
}

int main() {
  Node *pecas=NULL;
  int i=0;

  inicializa();
  comecaJogo();

do{
  
  if (joga==0)
  //maquina joga

  else if (joga == 1)
  // humano joga

  //se humano ganha, == 3

  //se máquina ganha, == 2
} while (joga <=1);


  imprimePecas(playerHand);
  printf("\npecas da mão: %d\n", contaLista(playerHand));
  imprimePecas(machineHand);
  printf("\n\npecas da maquina %d\n", contaLista(machineHand));
  imprimePecas(monte);
  printf("\n\npecas da mesa: %d\n", contaLista(monte));
 
 
  return 0;
}
