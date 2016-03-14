#include <stdio.h>
#include <stdlib.h>


//função que retorna a união entre os dois vetores
int* uniao (int n1,int *v1,int n2,int *v2)
{
	int *v3,i=0;
	
	v3=(int*)malloc((n1+n2)*sizeof(int));
	//armazena todo V1 no inicio de V3
	for(i=0;i<n1;i++)
	*(v3+i)=*(v1+i);
	
	
	//armazena V2, logo após o termino de V1
	for(i=0;i<n1+n2;i++)
	*(v3+(n1+i))=*(v2+i);
	
	
	//retorna o endereço de memória de V3
	return v3;
}

int main()
{
	int n1, n2, *v1=NULL, *v2=NULL, *v3=NULL, i=0;
	
	printf("quantos elementos haverão no primeiro vetor? : ");
	scanf("%d", &n1);
	printf("e no segundo? ");
	scanf("%d", &n2);
	//aloca quantidade de memória necessarias para os valores
	v1=(int*)malloc(n1*sizeof(int));
	v2=(int*)malloc(n2*sizeof(int));
	
	//entrada dos números nos vetores
	printf("(separar por espaços)\nV1= ");
	for (i=0; i<n1; i++)
		scanf("%d", &(*(v1+i)));
	printf("V2= ");
	for (i=0; i<n2; i++)
		scanf("%d", &(*(v2+i)));
		
	//chama a função união e retorna um ponteiro do terceiro vetor
	v3=uniao(n1, v1, n2, v2);
	printf("V3= {");
	for (i=0; i<n1+n2; i++)
	{
		printf("%d", *(v3+i));
		if (i==(n1+n2-1))//os dois ifs são para deixar o printf more cool c:
		printf("}");
		if (i<(n1+n2-1))
		printf(",");
	}
	free(v3);
	free(v2);
	free(v1);
	return 0;
}// dois exercicios interessantes: trabalhar com teoria dos conjuntos usando a mesma linha desse codigo.

