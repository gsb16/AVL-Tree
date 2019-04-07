
#include <stdio.h>
#include <stdlib.h>
#include "func.h"

void busca_nodo_path(tree *AVL, int val)
{
	nodo *prox = AVL->raiz;
	//testa se raiz = nula e se nodo = folha
	if (prox != NULL)
	{
		printf("%d", prox->chave);
	}
	while (prox != NULL)
	{
		if (val < prox->chave)
		{
			prox = prox->left;
		} else if (val > prox->chave)
		{
			prox = prox->right;
		} else
		{
			printf("\n");
			return;
		}
		if (prox != NULL)
		{
		printf(",%d", prox->chave);
		}
	}
	printf("\n");
}

nodo *cria_nodo(int chave)
{
	nodo *novo;
	
	novo = (nodo *) malloc (sizeof(nodo));
	novo->pai = NULL;
	novo->left = NULL;
	novo->right = NULL;
	novo->chave = chave;
	novo->H = 0;
	return novo;
}

int altura_nodo(nodo *nodox)
{
	if (nodox != NULL)
	{
		return nodox->H;
	} else
	{
		return -1;
	}
}

void atualiza_altura(nodo *nodox)
{
	while (nodox != NULL)
	{
		if (altura_nodo(nodox->left) >= altura_nodo(nodox->right))
		{
			nodox->H = altura_nodo(nodox->left) + 1;
		} else
		{
			nodox->H = altura_nodo(nodox->right) + 1;
		}
		nodox = nodox->pai;
	}
}

void insere_nodo(tree *AVL, int chave)
{
	nodo *novo = cria_nodo(chave);
	nodo *prox = NULL;
	nodo *pai = NULL;

	//se a arvore esta vazia, insere na raiz
	if (AVL->raiz == NULL)
	{
		AVL->raiz = novo;
	} else
	{
		prox = AVL->raiz;
		pai = NULL;

		//caminha na arvore ate a folha
		while (prox != NULL)
		{
			pai = prox;
			if (chave <= prox->chave)
			{
				prox = prox->left;
			} else
			{
				prox = prox->right;
			}
		}
		if (chave <= pai->chave)
		{
			pai->left = novo;
		} else
		{
			pai->right = novo;
		}
		novo->pai = pai;
	}

	AVL->tam++;
	atualiza_altura(novo);
	balanceamento_AVL(AVL, novo);
	//imprime_AVL(AVL);

}


void rotac_left(tree *AVL, nodo *nodox)
{
    nodo *nodoy;
    
    nodoy = nodox->right;
    nodoy->pai = nodox->pai;
    if (nodoy->pai == NULL)
    {
        AVL->raiz = nodoy;
    } else 
    {
        if (nodoy->pai->left == nodox)
        {
            nodoy->pai->left = nodoy;
        } else 
        if (nodoy->pai->right == nodox)
        {
            nodoy->pai->right = nodoy;
        }
    }
    nodox->right = nodoy->left;
    if (nodox->right != NULL)
    {
        nodox->right->pai = nodox;
    }
    nodoy->left = nodox;
    nodox->pai = nodoy;
    
    atualiza_altura(nodox);
    atualiza_altura(nodoy);
}

void rotac_right(tree *AVL, nodo *nodox)
{
    nodo *nodoy;
    nodoy = nodox->left;
    nodoy->pai = nodox->pai;
    if (nodoy->pai == NULL)
    {
        AVL->raiz = nodoy;
    } else 
    {
        if (nodoy->pai->right == nodox)
        {
            nodoy->pai->right = nodoy;
        } else 
        if (nodoy->pai->left == nodox)
        {
            nodoy->pai->left = nodoy;
        }
    }
    nodox->left = nodoy->right;
    if (nodox->left != NULL)
    {
        nodox->left->pai = nodox;
    }
    nodoy->right = nodox;
    nodox->pai = nodoy;
    
    atualiza_altura(nodox);
    atualiza_altura(nodoy);
}

void balanceamento_AVL (tree *AVL, nodo *nodox)
{
	while (nodox != NULL)
	{
		atualiza_altura(nodox);
		if (altura_nodo(nodox->left) >= 2 + altura_nodo(nodox->right))
		{
			if (altura_nodo(nodox->left->left) >= altura_nodo(nodox->left->right))
			{
				rotac_right(AVL, nodox);
			} else
			{
				rotac_left(AVL, nodox->left);
				rotac_right(AVL, nodox);
			}
		}
		else if (altura_nodo(nodox->right) >= 2 + altura_nodo(nodox->left))
		{
			if (altura_nodo(nodox->right->right) >= altura_nodo(nodox->right->left))
			{
				rotac_left(AVL, nodox);
			} else
			{
				rotac_right(AVL, nodox->right);
				rotac_left(AVL, nodox);
			}
		}
		nodox = nodox->pai;
	}
}

void apaga_nodo(tree *AVL, int chave)
{
	nodo *nodox;
	nodox = busca_nodox(AVL, chave);

	if (nodox != NULL)
	{
        if ((nodox->right != NULL) && (nodox->left != NULL))
        {
			nodo *ntemp = nodox->left;
            if (ntemp->right != NULL)
            {
                while (ntemp->right != NULL)
                {
                    ntemp = ntemp->right;
                }
                ntemp->pai->right = ntemp->left;
                if (ntemp->left != NULL)
                {
                    ntemp->left->pai = ntemp->pai;
                }
            } else if (ntemp->left != NULL)
            {
                nodox->left = ntemp->left;
                nodox->left->pai = nodox;
            } else 
            {
                nodox->left = NULL;
            }
            nodox->chave = ntemp->chave;
            balanceamento_AVL(AVL, ntemp->pai);
            //Libera a memoria do nodo apagado
            free(ntemp);
        } else if ((nodox->right != NULL) || (nodox->left != NULL))
        {
            nodo *ntemp = (nodox->right != NULL) ? nodox->right : nodox->left;
            nodox->chave = ntemp->chave;
            nodox->right = ntemp->right;
            nodox->left = ntemp->left;
            if(ntemp->right != NULL)
            {
                ntemp->right->pai = nodox;
            } else if (ntemp->left != NULL) 
            {
                ntemp->left->pai = nodox;
            }
            balanceamento_AVL(AVL, ntemp->pai);
            //Libera a memoria do nodo apagado
            free(ntemp);
        } else 
        {
            if (nodox->pai != NULL)
            {
                if (nodox->pai->right == nodox)
                {
                    nodox->pai->right = NULL;
                } else 
                {
                    nodox->pai->left = NULL;
                }
            } else 
            {
                AVL->raiz = NULL;
            }
            balanceamento_AVL(AVL, nodox);
            //Libera a memoria do nodo apagado
            free(nodox);
        }
    }

    //imprime_AVL(AVL);
}

nodo *busca_nodox(tree *AVL, int val)
{
	nodo *prox; 
	prox = AVL->raiz;
	//testa se raiz = nula e se nodo = folha
	if (prox == NULL)
	{
		return NULL;
	}
	while (prox != NULL)
	{
		if (val < prox->chave)
		{
			prox = prox->left;
		} else if (val > prox->chave)
		{
			prox = prox->right;
		} else if (val == prox->chave)
		{
			return prox;
		}
	}
	return NULL;
}

void imprime_nodo(nodo *nodox)
{
	if (nodox != NULL)
	{
		printf("(%d,", nodox->chave);
        imprime_nodo(nodox->left);
        printf(",");
        imprime_nodo(nodox->right);
        printf(")");
	} else
	{
		printf("()");
	}
}

void imprime_AVL(tree *AVL)
{
	if (AVL->raiz != NULL)
	{
		printf("(%d,", AVL->raiz->chave);
		imprime_nodo(AVL->raiz->left);
		printf(",");
		imprime_nodo(AVL->raiz->right);
		printf(")\n");
	} else
	{
		printf("()\n");
	}
}

