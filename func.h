
//Estrutura do nodo
typedef struct tNodo
{
	struct tNodo *pai;
	struct tNodo *left;
	struct tNodo *right;
	int chave;
	int H;
} nodo;

//Estrutura da arvore
typedef struct tTree
{
	struct tNodo *raiz;
	int tam;
} tree;

//Funcao que busca um nodo e imprime o caminho feito
void busca_nodo_path(tree *AVL, int val);

//Cria um novo nodo
nodo *cria_nodo(int chave);

//Mede altura do nodo
int altura_nodo(nodo *nodox);

//Atualiza a altura dos nodos a partir de uma folha até a raiz
void atualiza_altura(nodo *nodox);

//Insere um nodo na arvore
void insere_nodo(tree *AVL, int chave);

//Opera rotacao a esquerda
void rotac_left(tree *AVL, nodo *nodox);

//Opera rotacao a direita
void rotac_right(tree *AVL, nodo *nodox);

//Faz o balanceamento da arvore a partir de nodo
void balanceamento_AVL (tree *AVL, nodo *nodox);

//Busca nodo em especifico
nodo *busca_nodox(tree *AVL, int val);

//Apaga nodo e libera memoria
void apaga_nodo(tree *AVL, int chave);

//imprime determinado nodo
void imprime_nodo(nodo *nodox);

//imprime toda a arvore
void imprime_AVL(tree *AVL);
