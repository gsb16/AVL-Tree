
#include <stdio.h>
#include <stdlib.h>
#include "func.h"

char com;
int val;

int main()
{
	tree *AVL;

	//cria árvore
	AVL = (tree *) malloc (sizeof(tree));
	AVL->raiz = NULL;
	AVL->tam = 0;

	// ERRADO scanf("%c %d", &com, &val);
	//faz a leitura do arquivo de entrada inteiro
	while (scanf("%c", &com) != EOF)
	{
		scanf("%d", &val);
		
		switch (com)
		{
			//caso de busca
			case 'b':
				printf("%c %d\n", com, val);
				busca_nodo_path(AVL, val);
				break;
			//caso de insercao
			case 'i':
				printf("%c %d\n", com, val);
				insere_nodo(AVL, val);
				imprime_AVL(AVL);
				break;
			//caso de remocao
			case 'r':
				printf("%c %d\n", com, val);
				apaga_nodo(AVL, val);
				imprime_AVL(AVL);
				break;	
		}
		scanf("%c %d", &com, &val);
	}

	return 0;
}