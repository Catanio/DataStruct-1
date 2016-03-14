#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
	char string_num[100];
	int count=0, *head=NULL, pointer=0;
	//aloca 5 espaços, primeiramente
	head=(int*)malloc(5*sizeof(int));
	
	//lê uma string de números
	scanf("%s", string_num);
	
	//caso não contenha letra na string
	while (isdigit(string_num[0]))
	{
		if (count==5)
		{
			count = 0;
			//a cada cinco loops, o computador realoca mais 5 espaços
			head=(int*)realloc(head,(pointer+5)*sizeof(int));
		}
		//o pointer atua como uma seta no vetor onde tem  o cabeçalho, andando pra frente
		//nessa linha, é armazenado  o valor (convertido de string para int pelo atoi)
		//em um lugar do vetor
		*(head+pointer)=atoi(string_num);
		count++;
		pointer++;
		
		scanf("%s", string_num);
		
	}
	free(head);
	return 0;
}

