#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
//recebe a lista que vai receber a peça do monte e retorna o novo endereço
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

      if (temp->left!=NULL || temp->right != NULL){
        temp->left->right=temp->right;
        temp->right->left=temp->left;
      }
      else if (temp->left == NULL) {
        playerHand=temp->right;
      }
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
      if (temp->left!=NULL || temp->right != NULL){
        temp->left->right=temp->right;
        temp->right->left=temp->left;
      }
      else if (temp->left == NULL) {
        playerHand=temp->right;
      }

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
    if (maiorM->left!=NULL || maiorM->right != NULL){
      maiorM->left->right=maiorM->right;
      maiorM->right->left=maiorM->left;
    }
    else if (maiorM->left == NULL) {
      playerHand=maiorM->right;
    }
    maiorM->right=NULL;
    maiorM->left=NULL;
    return 0;
  }
  else if(maiorDuplaPlayer>maiorDuplaMaquina){
    mesa=maiorP;
    if (maiorP->left!=NULL || maiorP->right != NULL){
      maiorP->left->right=maiorP->right;
      maiorP->right->left=maiorP->left;
    }
    else if (maiorP->left == NULL) {
      playerHand=maiorP->right;
    }
    maiorP->right=NULL;
    maiorP->left=NULL;
    return 1;
  }
  else {
    for(temp=monte; temp->numberLeft==temp->numberRight; temp=temp->right);
    if (temp->left!=NULL || temp->right != NULL){
      temp->left->right=temp->right;
      temp->right->left=temp->left;
    }
    else if (temp->left == NULL)
      playerHand=temp->right;

    temp->right=NULL;
    temp->left=NULL;
    return 0;
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

void imprimeTela (){
  int i;
  system("clear");
  printf("peças da mesa: "); imprimePecas(mesa);
  printf("peças da mão: "); imprimePecas(playerHand);printf("              ");
  for(i=1; i<=contaLista(playerHand); i++)
    if(i<10)printf(" [%d] ", i);else printf(" [%d]  ", i);
  printf("\n//////////////////////\n/  escolha uma peça  /\n//////////////////////\n");
}

int jogando(){
  Node *temp=mesa;
  int auxI, auxII,primeiroNumero=temp->numberLeft, ultimoNumero,jogada, i;//joga = 1, pesca = 0;

  //Salva os dois números das extremidades da lista de dominós na mesa.
  while (temp!=NULL){
    ultimoNumero=temp->numberRight;
    temp=temp->right;
  }
  imprimeTela();
//esse loop verifica se existe uma peça compativel para a jogada, caso não, pesca e repete a verificação
  do {

    for(temp=playerHand; temp!=NULL; temp=temp->right) {
      if(temp->numberLeft == primeiroNumero || temp->numberRight == primeiroNumero || temp->numberLeft == ultimoNumero || temp->numberRight == ultimoNumero)
        break;
    }
    if(temp == NULL){
      playerHand=pescaDoMonte(playerHand);
          imprimeTela();
          printf("peça pescada por falta de jogadas possíveis!\n");
          return 1;
      }
      break;
  }while (1);

//esse loop pega a peça selecionada
  do{

    scanf("%d", &jogada);

    if(jogada > 0 && jogada <= contaLista(playerHand)){
      i=1;
      for (temp = playerHand; i<jogada; temp=temp->right)
        i++;

      if (temp->numberLeft == primeiroNumero || temp->numberRight == primeiroNumero || temp->numberLeft == ultimoNumero || temp->numberRight == ultimoNumero)
       break;
      else {
        imprimeTela();
        printf("Jogada inválida! Escolha outra peça: \n");
        continue;
      }
    }
    
    else continue;
    break;
  } while (1);

//essa parte faz os reaponteiramentos para dar um "pull" de uma lista pra outra.
  if (temp->left == NULL && temp->right == NULL){
    playerHand=NULL;
    temp->left=NULL;
    temp->right=NULL;
  }
  else if (temp->left == NULL ){
    playerHand=playerHand->right;
    playerHand->left = NULL;
    temp->right=NULL;
  }
  else if (temp->right==NULL) {
    temp->left->right=NULL;
    temp->left=NULL;
  }
  else {
    temp->left->right= temp->right;
    temp->right->left= temp->left;
    temp->left=NULL;
    temp->right=NULL;
  }
//falta excluir o nó da lista da mão
  do {
    printf("onde jogar?(1 - esquerda (%d); 2 - direita (%d)\n", primeiroNumero, ultimoNumero);
    scanf("%d", &jogada);
    if (jogada == 1) {
      if(temp->numberRight==primeiroNumero) {
        temp->right=mesa;
        mesa=temp;
        break;
      }
      else if (temp->numberLeft==primeiroNumero) {
        auxI=temp->numberLeft;
        auxII=temp->numberRight;
        temp->numberLeft=auxII;
        temp->numberRight=auxI;
        temp->right=mesa;
        mesa=temp;
        break;
      }
      else {
        printf("jogada invalida!\n");
        continue;
      }
    }
    else {
      Node *ultimo;
      for (ultimo=mesa; ultimo->right!=NULL; ultimo=ultimo->right);
      if (temp->numberLeft==ultimoNumero){
        ultimo->right=temp;
        temp->left=ultimo;
        break;
      }
      if (temp->numberRight==ultimoNumero) {
        auxI=temp->numberLeft;
        auxII=temp->numberRight;
        temp->numberLeft=auxII;
        temp->numberRight=auxI;
        ultimo->right=temp;
        temp->left=ultimo;
        break;
      }
      else {
        printf("jogada inválida!\n");
        continue;
      }
    }

  } while (1);
  return 1;
}
int AI (){
    Node *temp=mesa;
  int auxI, auxII ,primeiroNumero, ultimoNumero;
  //Salva os dois números das extremidades da lista de dominós na mesa.
  primeiroNumero=temp->numberLeft;
  for (temp=mesa; temp!=NULL; temp=temp->right)
    ultimoNumero=temp->numberRight;

//Verifica se existe uma peça compativel para a jogada. A peça correspondente para
  for(temp=machineHand; temp!=NULL; temp=temp->right) {
    if(temp->numberLeft == primeiroNumero || temp->numberRight == primeiroNumero || temp->numberLeft == ultimoNumero || temp->numberRight == ultimoNumero)
      break;

  }
  //se não tiver a peça, pesca e retorna para o outro jogador jogar;
  if(temp == NULL) {
    machineHand=pescaDoMonte(machineHand);
        return 0;
    }

//essa parte faz os reaponteiramentos para dar um "pull" de uma lista pra outra.
  if (temp->left == NULL && temp->right == NULL){
    machineHand=NULL;
    temp->left=NULL;
    temp->right=NULL;
  }
  else if (temp->left == NULL ){
    machineHand=machineHand->right;
    machineHand->left = NULL;
    temp->right=NULL;
  }
  else if (temp->right==NULL) {
    temp->left->right=NULL;
    temp->left=NULL;
  }
  else {
    temp->left->right= temp->right;
    temp->right->left= temp->left;
    temp->left=NULL;
    temp->right=NULL;
  }

  if(temp->numberRight==primeiroNumero) {
    temp->right=mesa;
    mesa=temp;
    return 0;
  }
  else if (temp->numberLeft==primeiroNumero) {
    auxI=temp->numberLeft;
    auxII=temp->numberRight;
    temp->numberLeft=auxII;
    temp->numberRight=auxI;
    temp->right=mesa;
    mesa=temp;
    return 0;
  }

  Node *ultimo;
  for (ultimo=mesa; ultimo->right!=NULL; ultimo=ultimo->right);
  if (temp->numberLeft==ultimoNumero){
    ultimo->right=temp;
    temp->left=ultimo;
    return 0;
  }
  else if (temp->numberRight==ultimoNumero) {
    auxI=temp->numberLeft;
    auxII=temp->numberRight;
    temp->numberLeft=auxII;
    temp->numberRight=auxI;
    ultimo->right=temp;
    temp->left=ultimo;
    return 0;
  }
  return 0;
}


int main() {
  int joga;
  inicializa();
  joga=primeiraJogada();//buga quando ninguém tem a primeira peça
  //1 = maquina joga; 0 = Player joga
  do{
    system("clear");
    if (joga == 0){
      joga=jogando();
      if(contaLista(playerHand)==0){
        system("clear");
        printf("\nVocê Ganhou!\n");
        break;
      } 
    }


    else if (joga == 1){
      joga=AI();
      if(contaLista(machineHand)==0){
        system("clear");
        printf("você perdeu!\n");
        break;
      }
    }

  } while (1);
 
 
  return 0;
}
