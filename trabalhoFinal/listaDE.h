#include <stdio.h>
#include <stdlib.h>

/*
 * Biblioteca voltada à manipulação de listas duplamente encadeadas.
 * O nome das estruturas e funções estão escritos em cammelCase
*/

typedef struct {
	char nome[40];
	char fone[30];
} tipoDado;

typedef struct lista{
	tipoDado dado;
	struct lista *proximo;
	struct lista *anterior;
} tipoLista;

/*
 * Recebe por parametro o topo da lista e o novo dado
 * topoDaLista = insereInicio (topoDaLista, (cast) novoDado)
*/
tipoLista *insereInicio(tipoLista *topoDaLista, tipoDado dado) {
	tipoLista *novo = (tipoLista *) malloc(sizeof(tipoLista));
	novo->dado = dado;
	novo->proximo = topoDaLista;
	novo->proximo->anterior = novo;
	novo->anterior = NULL;
	return novo;
}

/* 
 * imprime os valores int da lista
 * recebe o topo da lista por parametro
*/
void imprimeLista(tipoLista *lista) {
	tipoLista *auxiliar;

	for (auxiliar = lista; auxiliar != NULL; auxiliar = auxiliar->proximo)
		printf("dado: %d\n", auxiliar->dado);
}

/*
 * recebe o topo da lista por parametro e Insere novo nó com dado no fim da lista
 * topoDaLista = insereFim (topoDaLista, (cast) dado )
*/
tipoLista *insereFim (tipoLista *lista, tipoDado dado) {
	tipoLista *auxiliar, *novo = (tipoLista *) malloc (sizeof(tipoLista));
	novo->dado = dado;

	if (lista == NULL)
		return NULL;

	for (auxiliar = lista ; auxiliar->proximo != NULL ; auxiliar = auxiliar->proximo );

	auxiliar->proximo = novo;
	novo->proximo = NULL;
	novo->anterior = auxiliar;

	return lista;
}

int contaLista (tipoLista *lista) {
  tipoLista *auxiliar = lista;
  int count = 1;

  if (lista == NULL)
    return 0;
  else {

    while (auxiliar->proximo != NULL) {
      auxiliar=auxiliar->proximo;
      count++;
    }
    return count;
  }
}

/* recebe o topo da lista e a posição onde o elemento será inserido
 * lista = insereMeio (lista, dado, 4) - o dado inserido será o quarto elemento
*/
tipoLista *insereMeio (tipoLista *lista, tipoDado dado, int posicao) {
	tipoLista *auxiliar, *novo = (tipoLista *) malloc (sizeof(tipoLista));
	int count = 0;

	if (lista == NULL)
		return NULL;

	count = contaLista(lista); // conta quantos elementos há na lista
	
	// se a posição dada for superior à quantidade de elementos que há na lista, retorna ela sem nenhuma modificação
	if (posicao > count+1)
		return lista;

	// caso a posição dada seja a primeira
	else if (count == 1){
		lista = insereInicio (novo, dado);
		return lista;
	}
	else if (count == posicao ) {
		lista = insereFim (novo, dado);
		return lista;
	}
	else {
		count=1;

		while ( count < posicao ) {
			auxiliar = auxiliar->proximo;
			count++;
		}
		novo->anterior = auxiliar->anterior;
		novo->proximo = auxiliar;
		novo->anterior->proximo = novo;
		novo->proximo->anterior = novo;
	}
}
