#include <stdio.h>
#include <stdlib.h>

typedef struct elemento {
	int dado;
	struct elemento *prox;
} elemento;

typedef struct fila {
	elemento *inicio;
	elemento *fim;
} fila;
//checa se a fila está vazia ~empty file check
int emptfck (fila *p_fila)
{
	if (p_fila->inicio==NULL)
		return 1;
	else
		return 0;
}
//função para criar fila; recebe um ponteiro tipo fila como parametro e atribui valores nulos para o início e o fim
void cria_fila (fila *p_fila)
{
	p_fila->inicio=NULL;
	p_fila->fim=NULL;
}
//adiciona um elemento na fila
void push (fila *p_fila, int dado)
{
	elemento *pushed;
	pushed=malloc(sizeof(elemento));
	pushed->dado=dado;
	pushed->prox = NULL;
	
	if (emptfck(p_fila))
		p_fila->inicio=pushed;
	else
		p_fila->fim->prox=pushed;
	
	p_fila->fim = pushed;
}
//remove o primeiro elemento da fila; retorna 1 se der certo
int pop (fila *p_fila, int dado)
{
	elemento *poped;
	
	if (emptfck(p_fila))
		return 0;
	
	poped = p_fila->inicio;
	dado = poped->dado;
	p_fila->inicio = poped->prox;
	
	if (p_fila->inicio==NULL)
		p_fila->fim=NULL;
	
	free(poped);
	return 1;
}
//verifica quantos elementos tem na fila
int fila_tamanho (fila *p_fila)
{
	elemento *elem;
	int count = 0;
	
	elem = p_fila->inicio;
	while (elem != NULL) 
	{
		count++;
		elem = elem->prox;
	}
	return count;
}

int main(int argc, char **argv)
{
	
	return 0;
}
