typedef struct elemento{
    long id;   /*id do utilizador*/
    int count; /*número de posts */
}elem;

typedef struct heap{
    int   size; /* Tamanho alocado para a Heap */
    int   used; /* Número de elementos da Heap */
    elem *array;
}*Heap;

typedef struct elemPosts{
    long id;  /*id do post */
    Date data; /* Data de um post */
}elemP;

typedef struct heapPosts{
    int   size; /* Tamanho alocado para a Heap */
    int   used; /* Número de elementos da Heap */
    elemP *array;
}*HeapPosts;

typedef struct tags{
	long id; /*id da tag*/
	char* tagName; /*nome da tag*/
} Tags;

typedef struct tags **HashTableTags;

typedef struct treeHash{
    long contadorR; /* Número de pots tipo resposta */
    long contadorP; /* Número de posts tipo pergunta */
    int numRespostas; /* Número de posts tipo resposta e tipo pergunta */
    Post* tree; /*Árvore com os posts de cada dia*/
} TreeHash;

typedef struct treeHash **TreeHashData;

typedef struct TCD_community{
	int dataSize;  /* Tamanho da tabela de hash das datas/pots */
	int usersSize; /* Tamanho da tabela de hash dos utilizadores */
	int tagsSize; /* Tamanho da tabela de hash das tags */
	TreeHashData treeHash; /* Tabela de hash com os vários dias/pots */
	HashTableUsers hashUser;  /* Tabela de hash dos utilizadores */
	HashTableTags hashTag; /* Tabela de hash das tags */
	long *topN; /* Apontador para o array com os ids do top N */
	Heap Top; /* Heap com os ids de utilizador organizada pelo número de posts*/
}TCD_community;

int TAD_community_get_usersSize(TAD_community com){
	return com->usersSize;
}

int TAD_community_get_dataSize(TAD_community com){
	return com->dataSize;
}

int TAD_community_get_tagsSize(TAD_community com){
	return com->tagsSize;
}

long get_topN(TAD_community com, int i){
	return(com->topN[i]);
}
