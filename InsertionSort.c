#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node {
	int info;
	struct Node *next;
} typedef Node;
int main () {
	int i, j, sel, tamanho;
	srand( (unsigned)time(NULL) );
	do{
		printf("insertion sort com: \n1 - Vetor\n2 - Lista");
		scanf("%d", &sel);
		//Insertion em vetor
		if (sel == 1 ) {
			int *vetor, atual;
			printf("quantas posições o vetor tem de ter?");
			scanf("%d", &tamanho);

			//cria vetor no tamanho desejado
			vetor = (int *) malloc (tamanho*sizeof(int));

			//preenche com valores aleatórios
			for (i=0; i<tamanho; i++)
				vetor[i]=rand()%500;

			//mostra vetor embaralhado 
			printf("vetor embaralhado: %d", vetor[0]);
			for (i=1; i<tamanho; i++)
				printf(",%d ", vetor[i]);

			//faz o insertion sort

			for (i = 1 ; i < tamanho ; i ++ ) {
				atual=vetor[i];
				j=i-1;
				while (atual > vetor[j]) {
					vetor[j+1]=vetor[j];
					j--;
				}
				vetor[j+1]=atual;
			}
			
		}//lista
		else if (sel == 2 ) {



		}
		else continue;
		break;
	} while (1);
	return 0;
}
