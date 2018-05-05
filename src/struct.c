#include "interface.h"
#include <stdlib.h>
#include "struct.h"
#include "auxiliary.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

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

typedef struct users{
	long ownerUserId; /* id */
	char *displayName; /*nome */
	int reputation; /* reputação */
	int nPosts; /* número de posts */
	char *aboutMe; /*short bio */
	HeapPosts top10; /* heap com os IDs dos posts do utilizador */
} Users;

typedef struct users **HashTableUsers;

typedef struct tags{
	long id; /*id da tag*/
	char* tagName; /*nome da tag*/
} Tags;

typedef struct tags **HashTableTags;

typedef struct post{
	int postTypeId; /* Tipo do post: 1-> tipo resposta e 2-> tipo pergunta */
	long parentId; /* Id do pots ao qual foi feito uma resposta */
	long id; 
    char *tag; 
	char *title; /* Titulo */
	long ownerUserId; /* Id do utilizador */
	Date creationDate; /* Data de criação do post */	
	int answerCount; /* Número de respostas ao post */
	int commentCount; /* Número de comentários ao post */
	int score; 
    struct post *esq,*dir;
} Post;

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
	long *topNR; /* Apontador para o array com os ids do top N dos utilizadore com melhor reputação */
	Heap Top; /* Heap com os ids de utilizador organizada pelo número de posts*/
	Heap TopR; /* Heap com os ids de utilizador organizada pela reputação*/
	
}TCD_community;

/**
 * [Obter o tamanho da hashUser]
 * @param  com     [Estrutura]
 * @return         [Tamanho da hashUser]
 */
int TAD_community_get_usersSize(TAD_community com){
	return com->usersSize;
}

/**
 * [Obter o tamanho da treeHash]
 * @param  com     [Estrutura]
 * @return         [Tamanho da treeHash]
 */
int TAD_community_get_dataSize(TAD_community com){
	return com->dataSize;
}

/**
 * [Obter o tamanho da hashTag]
 * @param  com     [Estrutura]
 * @return         [Tamanho da hashTag]
 */
int TAD_community_get_tagsSize(TAD_community com){
	return com->tagsSize;
}

/**
 * [Devolve o id que se encontra numa posição do array]
 * @param  com     [Estrutura]
 * @param  i       [Posição do array]
 * @return         [Id do utilizador]
 */
long get_topN(TAD_community com, int i){
	return(com->topN[i]);
}

/**
 * [Devolve o id que se encontra numa posição do array]
 * @param  com     [Estrutura]
 * @param  i       [Posição do array]
 * @return         [Id do utilizador]
 */
long get_topNR(TAD_community com, int i){
	return(com->topNR[i]);
}

/**
 * [Devolve o nome de um utilizador]
 * @param  com     [Estrutura]
 * @param  i       [Posição da hashUser]
 * @return         [Nome do utilizador]
 */
char* users_getDisplayName (TAD_community com, int i){
	return com->hashUser[i]->displayName;
}

/**
 * [Devolve a informação do perfil de um utilizador]
 * @param  com     [Estrutura]
 * @param  i       [Posição da hashUser]
 * @return         [Informação do utilizador]
 */
char* users_getAboutMe (TAD_community com, int i){
	return com->hashUser[i]->aboutMe;
}

/**
 * [Devolve a data do post]
 * @param  com     [Estrutura]
 * @param  i       [Posição da hash]
 * @return         [A data de criação]
 */
Date post_getCreationDate (TAD_community com, int i){
	return com->treeHash[i]->tree->creationDate;
}

/**
 * [Obter postTypeId de um post]
 * @param  com     [Estrutura]
 * @param  i       [Posição da treeHash]
 * @param  id      [Id do post]
 * @return         [PostTypeId]
 */
int post_getPostTypeId (TAD_community com, int i, long id){
	Post* a = com->treeHash[i]->tree;
	while (a){
		if (a->id == id) return a->postTypeId;
		else if (a->id > id && a->esq!=NULL ) a=a->esq;
		else a=a->dir; 
	}
	return -1;
}

/**
 * [Obter o título de um post]
 * @param  com     [Estrutura]
 * @param  i       [Posição da hash]
 * @param  id      [Id do post]
 * @return         [Título]
 */
char* post_getTitle (TAD_community com, int i, long id){
	Post* a = com->treeHash[i]->tree;
	while (a){
		if (a->id == id) return a->title;
		else if (a->id > id && a->esq!=NULL ) a=a->esq;
		else a=a->dir; 
	}
	return NULL;
}

/**
 * [Obter a tag de um post]
 * @param  com     [Estrutura]
 * @param  i       [Posição da hash]
 * @param  id      [Id do post]
 * @return         [Tag]
 */
char* post_getTag (TAD_community com, int i, long id){
	Post* a = com->treeHash[i]->tree;
	while (a){
		if (a->id == id) return a->tag;
		else if (a->id > id && a->esq!=NULL ) a=a->esq;
		else a=a->dir; 
	}
	return NULL;
}

/**
 * [Obter o score de um post]
 * @param  com     [Estrutura]
 * @param  i       [Posição da hash]
 * @param  id      [Id do post]
 * @return         [Score]
 */
int post_getScore (TAD_community com, int i, long id){
	Post* a = com->treeHash[i]->tree;
	while (a){
		if (a->id == id) return a->score;
		else if (a->id > id && a->esq!=NULL ) a=a->esq;
		else a=a->dir; 
	}
	return -1;
}

/**
 * [Obter o id do utilizador de um post]
 * @param  com     [Estrutura]
 * @param  i       [posição da hash]
 * @param  id      [Id do post]
 * @return         [Id do utilizador]
 */
long post_getOwnerUserId (TAD_community com, int i, long id){
	Post* a = com->treeHash[i]->tree;
	while (a){
		if (a->id == id) return a->ownerUserId;
		else if (a->id > id && a->esq!=NULL ) a=a->esq;
		else a=a->dir; 
	}
	return -1;
}

/**
 * [Obter parentId do post]
 * @param  com     [Estrutura]
 * @param  i       [Posição da hash]
 * @param  id      [Id do post]
 * @return         [ParentId]
 */
long post_getparentId (TAD_community com, int i, long id){
	Post* a = com->treeHash[i]->tree;
	while (a){
		if (a->id == id) return a->parentId;
		else if (a->id > id && a->esq!=NULL ) a=a->esq;
		else a=a->dir; 
	}
	return -1;
}

/**
 * [Devolve o contador com o número de respostas tipo perguntas mais respostas]
 * @param  com     [Estrutura]
 * @param  i       [Posição da hash]
 * @return         [Contador]
 */
int treeHash_getNumRespostas (TAD_community com, int i){
	return com->treeHash[i]->numRespostas;
}

/**
 * [Devolve o contador com o número de posts tipo resposta]
 * @param  com     [Estrutura]
 * @param  i       [Posição da hash]
 * @return         [Contador]
 */
long treeHash_getContadorR (TAD_community com, int i){
	return com->treeHash[i]->contadorR;
}

/**
 * [Devolve o contador com o número de posts tipo pergunta]
 * @param  com     [Estrutura]
 * @param  i       [Posição da hash]
 * @return         [Contador]
 */
long treeHash_getContadorP (TAD_community com, int i){
	return com->treeHash[i]->contadorP;
}

/**
 * [Alterar o tamanho da hashUser]
 * @param  com          [Estrutura]
 * @param  usersSize    [Novo tamanho da hashUser]            
 */
void TAD_community_set_usersSize(TAD_community com, int usersSize){
	com->usersSize = usersSize;
}

/**
 * [Alterar o tamanho da treeHash]
 * @param  com          [Estrutura]
 * @param  dataSize     [Novo tamanho da treeHash]            
 */
void TAD_community_set_dataSize(TAD_community com, int dataSize){
	com->dataSize = dataSize;
}

/**
 * [Alterar o tamanho da hashTag]
 * @param  com          [Estrutura]
 * @param  tagsSize     [Novo tamanho da hashTag]            
 */
void TAD_community_set_tagsSize(TAD_community com, int tagsSize){
	com->tagsSize = tagsSize;
}

/**
 * [Inicialização da estrutura]
 * @return         [Estrutura]
 */
TAD_community init(){
    TAD_community com = malloc(sizeof(TCD_community));
    TAD_community_set_dataSize(com,-1);
    TAD_community_set_usersSize(com,-1);
    TAD_community_set_tagsSize(com,-1);
    com->topN=NULL;
    com->Top=NULL;
    com->topNR=NULL;
    com->TopR=NULL;
    return com;
}

/**
 * [Inicialização da hashUser]
 * @param  com     [Estrutura]
 * @param  N       [Tamanho da hashUser]
 * @return         [Estrutura]
 */
TAD_community initHashUsers (TAD_community com, int N){
	HashTableUsers user = malloc(N*sizeof(Users*));
	for (int i=0; i<N; i++){
		user[i] = NULL;
	}
	com->hashUser=user;
	com->topNR = malloc((N/2)*sizeof(long));
	com->topN = malloc((N/2)*sizeof(long));
	for(int j=0;j<N/2;j++){
        com->topN[j]=-2;
		com->topNR[j]=-2;
    }
	return com;
}

/**
 * [Inicialização da hashTag]
 * @param  com     [Estrutura]
 * @param  N       [Tamanho da hashTag]
 * @return         [Estrutura]
 */
TAD_community initHashTags (TAD_community com, int N){
	HashTableTags tag = malloc(N*sizeof(Tags*));
	for (int i=0; i<N; i++){
		tag[i] = NULL;
	}
	com->hashTag=tag;
	return com;
}

/**
 * [Inicialização da treeHash]
 * @param  com     [Estrutura]
 * @param  N       [Tamanho da treeHash]
 * @return         [Estrutura]
 */
TAD_community initHashData (TAD_community com, int N){
	TreeHashData tree = malloc(N*sizeof(Post*));
	for (int i=0; i<N; i++){
		tree[i] = NULL;
	}
	com->treeHash=tree;
	return com;
}

/**
 * [Inicialização da HeapPosts]
 * @param  size      [Tamanho da heapPosts]
 * @return           [HeapPosts]
 */
static HeapPosts initHeapPosts(int size){
    HeapPosts h = malloc(sizeof(struct heapPosts));
    if(h != NULL) {
        h->size = size;
        h->used = 0;
        h->array=malloc(size*sizeof(struct elemPosts));
    }
    return h;
}

/** 
 * [Devolve o valor de Hash correspondente a um determinado id]
 * @param i    [Id do utilizador]
 * @param com  [Estrutura]
 * @return     [Valor de Hash]
 */
int userHash (long i, TAD_community com){
	if (i < 0) return (-(i % com->usersSize));
	else return (i % (com->usersSize));
}

/**
 * [Insere a informação de um utilizador]
 * @param  h1             [HashTableUsers]
 * @param  i              [Posição da HashTableUsers] 
 * @param  reputation     [Reputação do utilizador] 
 * @param  id             [Id do utilizador]
 * @param  name           [Nome do utilizador]
 * @param  about          [Short bio do utilizador] 
 */
static void insereTableUsers (HashTableUsers h1, int i, int reputation, long id, char *name, char *about){
	int tam=10;
	Users *new= malloc(sizeof(Users));
	new->ownerUserId = id;  
	new->reputation = reputation; 
	new->displayName = name;
	new->nPosts = 0;
	new->aboutMe = about;
	new->top10=initHeapPosts(tam);
	h1[i]=new;
}

/**
 * [Determina a posição onde se irá inserir a informação de um utilizador]
 * @param  com            [Estrutura]
 * @param  reputation     [Reputação do utilizador] 
 * @param  id             [Id do utilizador]
 * @param  name           [Nome do utilizador]
 * @param  about          [Short bio do utilizador]  
 */
void addUser (TAD_community com,int reputation, long id,char *name,char *about){
	int i = userHash(id,com);
	while (com->hashUser[i]!=NULL && !(com->hashUser[i]->ownerUserId == id)){
		if (i>com->usersSize) i=0;
		else i++;
	}
	insereTableUsers(com->hashUser,i,reputation, id, name, about);
}

/**
 * [Devolve a posição da hashUser onde se encontra um dado utilizador]
 * @param  com     [Estrutura]
 * @param  id      [Id do utilizador]
 * @return         [Posição da hashUser]
 */
int procuraUser (TAD_community com, long id){
	int i, chave = userHash(id,com),c=0;
	for (i=chave; com->hashUser[i]!=NULL && c<com->usersSize && com->hashUser[i]->ownerUserId!=id; i++){
		if (i+1 == com->usersSize) i=0;
		c++;
	}
	if (com->hashUser[i]!=NULL && com->hashUser[i]->ownerUserId==id) return i;
	else return -1;
}

/**
 * [Aumenta o número de posts de um dado utilizador]
 * @param  com     [Estrutura]
 * @param  id      [Id do utilizador]
 */
void incrementaPost(TAD_community com, long id){
	int i = procuraUser(com, id);
	com->hashUser[i]->nPosts++;
}

/**
 * [Devolve o valor de Hash correspondente a uma tag]
 * @param s   	  [Tag]
 * @param com     [Estrutura]
 * @return     	  [Valor de Hash]
*/
int tagHash (char* s, TAD_community com){
	int l = strlen(s),soma = 0;
    for(int i=0; i<l; i++)
        soma += s[i];
	return (soma % com->tagsSize);
}

/**
 * [Insere a informação de uma tag]
 * @param  h1            [HashTableTags]
 * @param  i             [Posição da hash] 
 * @param  id            [Id da tag] 
 * @param  tagName       [Nome da tag] 
 */
static void insereTableTags (HashTableTags h1, int i, long id, char* tagName){
	Tags *new = malloc(sizeof(Tags));
	new->id = id;
	new->tagName = tagName; 	
	h1[i]=new;
}

/**
 * [Determina a posição onde se irá inserir a informação de uma tag]
 * @param  com                [Estrutura]
 * @param  tagName            [Conteúdo da tag]
 * @param  id                 [Id da tag] 
 */
void addTags (TAD_community com,char* tagName, long id){
	int i = tagHash(tagName,com); 
	while (com->hashTag[i]!=NULL){
		if (i>com->tagsSize) i=0;
		else i++;
	}
	insereTableTags(com->hashTag, i, id, tagName);
}

/** 
 * [Devolve o valor de Hash correspondente a uma determinada data]
 * @param data   [Data]
 * @param com    [Estrutura] 
 * @return       [Valor de Hash]
 */
int dataHash (Date data, TAD_community com){
	int i = get_day(data) + get_month(data) + get_year(data);
	return ((i) % com->dataSize); 
}

/** 
 * [Devolve a altura da árvore]
 * @param p    [Árvore dos posts]
 * @return     [Altura]
 */
static int height(Post *p){
	int altura = 0;
	if(p!=NULL){
		altura = 1 + max(height(p->esq),height(p->dir));
	}
	return altura;
}

/** 
 * [Realiza uma rotação à direita na árvore dos posts]
 * @param p    [Árvore de Posts]
 * @return     [Árvore de Posts]
 */
static Post* rotate_right(Post *p){
	Post *q = p->esq;
	p->esq = q->dir;
	q->dir = p;
	return q;
}

/** 
 * [Realiza uma rotação à esquerda na árvore dos posts]
 * @param p    [Árvore de Posts]
 * @return     [Árvore de Posts]
 */
static Post* rotate_left(Post *p){
	Post *q = p->dir;
	p->dir = q->esq;
	q->esq = p;
	return q;
}

/** 
 * [Realiza o balanceamento da árvore dos posts]
 * @param p    [Árvore dos posts]
 * @return     [Árvore dos posts]
 */
static Post* balancaTree (Post *p){
	Post *p1 = p->esq;	
	Post *p2 = p->dir;
	if ( height(p->esq) - height(p->dir) == 2 ){
		if ( height(p1->dir) > height(p1->esq) )
			p->esq = rotate_left(p->esq);
		return rotate_right(p);
	}
	else if ( height(p->dir) - height(p->esq) == 2 ){
		if ( height(p2->esq) > height(p2->dir) )
			p->dir = rotate_right(p->dir);
		return rotate_left(p);
	}
	return p;
}

/** 
 * [Cria um post com a informção existente]
 * @param score           [Score a inserir]
 * @param postTypeId      [PostTypeId a inserir]
 * @param parentId        [ParentId a inserir]
 * @param id              [Id a inserir]
 * @param tag             [Tag a inserir]
 * @param title           [Title a inserir]
 * @param ownUserId       [OwnerUserId a inserir]
 * @param answerCount     [AnswerCount a inserir]
 * @param data            [Data a inserir]
 * @param commentCount    [CommentCount a inserir]
 * @return                [Post já com a informção inserida]
*/
static Post* insereTree(int score, int postTypeId, long parentId, long id, char *tag, char *title, long ownerUserId, int answerCount, Date data, int commentCount){
	Post *p = malloc (sizeof(Post));
	if(p!=NULL){
	    p->postTypeId = postTypeId; 
	    p->creationDate=data;
		p->answerCount = answerCount;
		p->ownerUserId = ownerUserId;
		p->id = id;
		p->score = score;
	    p->title = title;
		p->parentId = parentId;
		p->commentCount = commentCount;
		p->tag = tag;
		p->esq = NULL;
		p->dir = NULL;
	}
	return p;
}

/** 
 * [Insere na árvore dos posts um novo, mantendo as propriedades da árvore, depois de o criar com a informação existente]
 * @param c                  [Árvore binária dos posts]
 * @param score              [Score a inserir]
 * @param postTypeId         [PostTypeId a inserir]
 * @param parentId           [ParentId a inserir]
 * @param id                 [Id a inserir]
 * @param tag                [Tag a inserir]
 * @param title              [Title a inserir]
 * @param ownUserId          [OwnerUserId a inserir]
 * @param answerCount        [AnswerCount a inserir]
 * @param data               [Data a inserir]
 * @param commentCount       [CommentCount a inserir]
 * @return                   [Post já com o novo inserido]
 */
static Post* rec(Post* c,int score, int postTypeId,long parentId, long id, char *tag, char *title, long ownUserId, int answerCount, Date data, int commentCount){
	if(c==NULL){
	    return insereTree(score, postTypeId,parentId,id,tag,title,ownUserId,answerCount,data,commentCount);
	}
    else{
    	if(c->id>id) c->esq=rec(c->esq,score,postTypeId,parentId,id,tag,title,ownUserId,answerCount,data,commentCount);
        else c->dir=rec(c->dir,score,postTypeId,parentId,id,tag,title,ownUserId,answerCount,data,commentCount);
    }
    return balancaTree(c);
}

/** 
 * [Adiciona à estrutura dos posts um novo, atualiza o número de posts realizado pelo utilizador  que o criou e insere na heapPosts associada ao utilizador a informação sobre o post]
 * @param com             [Estrutura]
 * @param score           [Score a inserir]
 * @param postTypeId      [PostTypeId a inserir]
 * @param parentId        [ParentId a inserir]
 * @param id              [Id a inserir]
 * @param tag             [Tag a inserir]
 * @param title           [Title a inserir]
 * @param ownerUserId     [OwnerUserId a inserir]
 * @param answerCount     [AnswerCount a inserir]
 * @param data            [Data a inserir]
 * @param commentCount    [CommentCount a inserir]
*/
void addPost (TAD_community com,int score,int postTypeId,long parentId, long id, char *tag, char *title, long ownerUserId, int answerCount, Date data,int commentCount){
	int i=dataHash(data,com); 
	while (com->treeHash[i]!=NULL && !compareDate(com->treeHash[i]->tree->creationDate,data)){
		if (i>com->dataSize) i=0;
		else i++;
	}
	if(com->treeHash[i]==NULL){
			TreeHash *new= malloc(sizeof(TreeHash));
			new->tree=NULL;
			com->treeHash[i]=new;
		    com->treeHash[i]->contadorR = 0;
        	com->treeHash[i]->contadorP = 0;
        	com->treeHash[i]->numRespostas = 0;
	}
    com->treeHash[i]->tree=rec(com->treeHash[i]->tree,score,postTypeId,parentId,id,tag,title,ownerUserId,answerCount,data,commentCount);
    incrementaPost(com,ownerUserId);
    if (postTypeId ==1 || postTypeId == 2) insere_Heap_Posts(com,ownerUserId,id,data);
    if (postTypeId == 2) com->treeHash[i]->contadorR++;
    if (postTypeId == 1) com->treeHash[i]->contadorP++;
    com->treeHash[i]->numRespostas++;
}

/**
 * [Procura um post na estrutura]
 * @param com  [Estrutura]
 * @param id   [Id do post a procurar]
 * @return     [A posição da hash onde se encontra o post ou -1 caso não exista]
*/
int procuraPost (TAD_community com, long id){
	for(int i=0; i< com->dataSize; i++){
		if (com->treeHash[i]!=NULL){
			Post* a= com->treeHash[i]->tree;
			while (a){
				if (a->id == id) return i;
				else if (a->id > id && a->esq!=NULL ) a=a->esq;
				else a=a->dir;
			}
		}
	}
	return -1;
}

/** 
 * [Verifica se uma determinada posicão da treeHash é nula]
 * @param com  [Estrutura]
 * @param i    [Posição a verificar]
 * @return     [Booleano de comparação] 
 */
int existeTree (TAD_community com, int i){
    if(com->treeHash[i]!=NULL) return 1;
    return 0;
}

/** 
 * [Insere o id e data de um post do tipo pergunta nos arrays respetivos caso este contenha a tag pretendida]
 * @param a       [Árvore de posts]
 * @param tag     [Tag a procurar]
 * @param p       [Array para inserir o id]
 * @param c       [Tamanhos dos arrays]
 * @param data    [Array para inserir a data]
*/
static void retornaIdR (Post* a, char* tag, long* p, int c, Date* data){
	int i;
	if (a!=NULL){
		if (a->tag!=NULL && a->postTypeId!=2){
			if (verificaTag(a->tag,tag)==1){
				for (i=0; i<c && p[i]!=-2; i++);
				p[i] = a->id;data[i] = a->creationDate;
			}
		}
	retornaIdR (a->esq,tag,p,c,data);
	retornaIdR (a->dir,tag,p,c,data);
	}
}

/** 
 * [Função que acede à árvore dos posts pretendida]
 * @param com      [Estrutura]
 * @param i        [Posição da treeHash onde se encontra a árvore]
 * @param p        [Array de ids]
 * @param tag      [Tag a verificar]
 * @param c        [Tamanho dos arrays]
 * @param arrayD   [Array de datas]
*/
void retornaId (TAD_community com, int i, long* p, char* tag, int c, Date* arrayD){
	Post* a = com->treeHash[i]->tree;
	retornaIdR (a, tag, p, c, arrayD);
}

/** 
 * [Na eventualidade de o post ser do tipo pergunta insere ordenadamente, com fator de comparação o score, este e o seu id nos arrays respetivos]
 * @param a    [Árvore de posts]
 * @param p    [Array de ids]
 * @param s    [Array de scores]
 * @param N    [Tamanho dos arrays]
*/
static void retornaSIdR (Post* a, long *p, int *s, int N){
	if (a!=NULL){
		if (a->postTypeId!=1){
      		insere(a->score,a->id,p,s,N);
		}
	retornaSIdR (a->esq,p,s,N);
	retornaSIdR (a->dir,p,s,N);}
}

/** 
 * [Função que acede à árvore dos posts pretendida]
 * @param com       [Estrutura]
 * @param p    	    [Array de ids]
 * @param s    	 	[Array de scores]
 * @param N    		[Tamanho dos arrays]
 * @param i    		[Posição da treeHash onde se encontra a árvore]
*/
void retornaSId (TAD_community com,long *p, int *s, int N,int i){
	Post* a = com->treeHash[i]->tree;
	retornaSIdR (a, p, s, N);
}

/** 
 * [Guarda os ids dos posts, de uma posição da treeHash, que contém uma determinada palavra no título, por cronologia inversa]
 * @param a           [Árvore dos posts]
 * @param word        [Palavra]
 * @param data        [Array com as datas de criação dos posts]
 * @param id          [Array com os ids dos posts]
 * @param N           [N pedido no top N]
 */
static void procuraTituloR(Post *a,char *word,Date *data,long *id,int N){
	if(a){
		if(a->title!=NULL && a->postTypeId!=2)
			if(contida(a->title,word)) insereT(a->creationDate,a->id,data,id,N);
		procuraTituloR(a->esq,word,data,id,N);
		procuraTituloR(a->dir,word,data,id,N);
	}
}

/** 
 * [Percorre todas as árvores com posts existentes e para todos verifica se a palavra está contida no título]
 * @param com    [Estrutura]
 * @param word   [Palavra a verificar]
 * @param data   [Array de datas]
 * @param id     [Array de ids]
 * @param N      [Tamanho dos arrays]
*/
void procuraTitulo(TAD_community com,char *word,Date *data,long *id,int N){
	int i;
	for(i=0;i<com->dataSize;i++){
		if(com->treeHash[i]!=NULL){
			Post *a=com->treeHash[i]->tree;
			procuraTituloR(a,word,data,id,N);
		}
	}
}

/** 
 * [Guarda num par dado o valor do calculo da média ponderada para as respostas a um determinado post]
 * @param com         [Estrutura]
 * @param a           [Árvore dos posts]
 * @param id          [Id do post pergunta]
 * @param max         [Maior média pondera até ao momento]
 * @param flag        [Flag]
 * @param p           [Par]
 */
static void guardaRespostas(TAD_community com, Post* a, long id, float max, int flag, NEW_pair p){
	float c = 0;
	if(a!=NULL && get_trd_new(p)!=0){
		if(a->postTypeId==2 && a->parentId == id){
			set_trd_new(p,get_trd_new(p)-1);
			c = (com->hashUser[procuraUser(com,a->ownerUserId)]->reputation)*0.25 + (a->score)*0.65 + (a->commentCount)*0.1;
			if(flag==0) {
				set_snd_new(p,a->id);
				set_fst_new(p,c);
				flag = 1;
			}
			else if(c>max) {
				set_snd_new(p,a->id);
				set_fst_new(p,c);
			}
		}
		guardaRespostas(com,a->esq, id, max, flag,p);
		guardaRespostas(com,a->dir, id, max, flag,p);
	}
}

/** 
 * [Devolve o id da resposta com maior média ponderada de um determinado post do tipo pergunta]
 * @param com         [Estrutura]
 * @param id          [Id do post pergunta]
 * @return            [Id da resposta com maior média ponderada] 
 */
long procuraRespostas(TAD_community com, long id){
	int i,j,flag = 0,local = procuraPost(com,id),nRespostas=0;
	float max = 0,maximo = 0;
	long idM=-1;
	if(local!=-1){
		Post *b = com->treeHash[local]->tree;
		while(b){
			if(b->id==id){
				if(b->postTypeId==1) {nRespostas = b->answerCount;break;}
		    	else return -1;
			}
			else if(b->id>id && b->esq!=NULL) b = b->esq;
				 else b = b->dir;
		}
		NEW_pair p= create_new_pair(0,-2,nRespostas);
		set_trd_new(p,nRespostas);
		for(i=local;i<com->dataSize && nRespostas!=0;i++){
			if(com->treeHash[i]!=NULL){
				Post* a = com->treeHash[i]->tree;
				guardaRespostas(com,a,id,max,0,p);
				nRespostas = get_trd_new(p);
				if(get_snd_new(p)!=-2 && flag==0) {
					maximo = get_fst_new(p);
					idM = get_snd_new(p);
					flag = 1;
				}
				if(get_fst_new(p)>maximo && flag==1) {
					maximo = get_fst_new(p);
					idM = get_snd_new(p);
				}
			}
		}
		if(nRespostas!=0){
			for(j=0;j<i && nRespostas!=0;j++){
				if(com->treeHash[j]!=NULL){
					Post* a = com->treeHash[j]->tree;
					guardaRespostas(com,a,id,max,0,p);
					nRespostas = get_trd_new(p);
					if(get_snd_new(p)!=-2 && flag==0) {
						maximo = get_fst_new(p);
						idM = get_snd_new(p);
	     				flag = 1;				
					}
					if(get_fst_new(p)>maximo && flag==1) {
						maximo = get_fst_new(p);
						idM = get_snd_new(p);	
					}
				}
			}
		}
		free_new_pair(p);
	}
	return idM;
}

/** 
 * [Devolve a posição da treeHash com uma determinada data]
 * @param com         [Estrutura]
 * @param data        [Data]
 * @return            [Posição da treeHash]
 */
int procuraData(TAD_community com, Date data){
	int chave = dataHash(data,com),i,c=0;
	for(i=chave;com->treeHash[i]!=NULL && c<com->dataSize && !compareDate(com->treeHash[i]->tree->creationDate,data);i++){
		if(i+1 == com->dataSize) i=0;
		c++;
	}
	if(com->treeHash[i]!=NULL && compareDate(com->treeHash[i]->tree->creationDate,data)) return i;
	return -1;
}

/** 
 * [Troca dois elementos da heapPost]
 * @param h       [HeapPosts]
 * @param a       [Elemento para trocar de posição com b]
 * @param b       [Elemento para trocar de posição com a]
 */
static void swapPosts(HeapPosts h, int a, int b){
    elemP t = h->array[a];
    h->array[a] = h->array[b];
    h->array[b] = t;
}

/**
 * [Função que após inserção de um elemento na HeapPosts, coloca esse elemento na posição correta]
 * @param h       [HeapPosts]
 * @param i       [Quantos elementos existem na heap]
 */
static void bubbleUpPosts(HeapPosts h, int i){                
    while (i!=0 && compareDateQ(h->array[i].data,h->array[PARENT(i)].data)==2) {
        swapPosts(h, i, PARENT(i));
        i = PARENT(i);
    }
}

/** 
 * [Função que após remoção de um elemento na HeapPosts, mantém o invariante que os pai é sempre maior que os filhos]
 * @param h       [HeapPosts]
 * @param N       [Número de elementos na HeapPosts]
 */
static void bubbleDownPosts(HeapPosts h, int N){    
    int i = 0, max ;
    while (RIGHT(i) < N && compareDateQ(h->array[max=(compareDateQ(h->array[LEFT(i)].data,h->array[RIGHT(i)].data)==2) ? LEFT(i) : RIGHT(i)].data, h->array[i].data)==2) {
        swapPosts(h, i, max);
        i = max;
    }
    if (LEFT(i) < N && compareDateQ(h->array[LEFT(i)].data,h->array[i].data)==2)
        swapPosts(h, i, LEFT(i));
}

/** 
 * [Insire um elemento (id e data) na HeapPosts mantendo o invariante que o pai é sempre maior que os filhos]
 * @param h        [HeapPosts onde queremos inserir o elemento]
 * @param data     [Data que queremos inserir]
 * @param id       [Id que queremos inserir]
 * @return         [Caso de sucesso]  
 */
static int insertHeapPosts(HeapPosts h,Date data,long id){
    if (h->used == h->size) {
        h->array= realloc(h->array, 2*(h->size)*sizeof(struct elemPosts));
        h->size *= 2;
    }
    assert( h!= NULL);
    h->array[h->used].data= data;
    h->array[h->used].id= id;
    (h->used)++;
    bubbleUpPosts(h, h->used-1);
    return 1;
}

/** 
 * [Remove a cabeça da heap(o maior elemento) mantendo o invariante que o pai é sempre maior que os filhos e insere-o noutra heap]
 * @param h       [HeapPosts a extrair]
 * @param h2      [HeapPosts a inserir]
 * @return        [O id do maior elemento da heap]
 */
static long extractMaxPosts2(HeapPosts h,HeapPosts h2){
    if (h->used > 0) {
        elemP novo= h->array[0];
        long res=novo.id;
        insertHeapPosts(h2,novo.data,res);
        h->array[0] = h->array[h->used-1];
        (h->used)--;
        bubbleDownPosts(h, h->used);
        return res;
    } else return -1;
}

/** 
 * [Remove a cabeça da heap (o maior elemento) mantendo o invariante que o pai é sempre maior que os filhos]
 * @param h       [HeapPosts a extrair]
 * @return        [O id do maior elemento da heap]
 */
static long extractMaxPosts(HeapPosts h){
    if (h->used > 0) {
        elemP novo= h->array[0];
        long res=novo.id;
        h->array[0] = h->array[h->used-1];
        (h->used)--;
        bubbleDownPosts(h, h->used);
        return res;
    } else return -1;
}

/** 
 * [Insere no array passado os ids dos posts, caso seja do tipo resposta insere o id da pergunta correspondente]
 * @param h            [HeapPosts com os ids dos posts a inserir]
 * @param com          [Estrutura] 
 * @param postId       [Array de ids dos posts] 
 * @param h3           [HeapPosts] 
 */
static void procuraId(HeapPosts h, TAD_community com, long* postId, HeapPosts h3){
	int c = h->used, j; 
	long idP;
	for(j=0;j<c;j++){
		Date data = h->array[0].data;
		idP = extractMaxPosts2(h,h3);
		int chave = procuraData(com,data);
		if(post_getPostTypeId(com,chave,idP)==1){
			postId[j]=idP; 
		}
		else if (post_getPostTypeId(com,chave,idP)==2){
			long id = post_getparentId(com,chave,idP); 
			postId[j] = id; 
		}
	}
}

/** 
 * [Coloca no array os ids dos posts tipo pergunta em que dois dados utilizadores participam]
 * @param h1        [HeapPosts com os posts de um utilizador]
 * @param h2        [HeapPosts com os posts de um utilizador]
 * @param N         [N pedido no top N]
 * @param id        [Array com os ids dos posts]
 * @param com       [Estrutura]
 * @param chave1    [Local da hashUser onde se encontra a informação de determinado utilizador]
 * @param chave2    [Local da hashUser onde se encontra a informação de determinado utilizador]
 * @return          [Número de posts em que ambos os utilizadores participam]
 */
static int extraiId(HeapPosts h1,HeapPosts h2,int N,long* id,TAD_community com,int chave1,int chave2){
	int k=0; 
	if(h1->used<h2->used) {
		int c = h2->used,j;
		int a = h1->used;
		HeapPosts h3 = initHeapPosts(c);
		HeapPosts h4 = initHeapPosts(a);
		long* ID = malloc(c*sizeof(long));
		procuraId(h2,com,ID,h3);
		for(j=0;j<a && k<N;j++){
			Date data = h1->array[0].data;
			long postId;
			postId = extractMaxPosts2(h1,h4);
			if(post_getPostTypeId(com,procuraData(com,data),postId)==1 && procuraArray(ID,postId,c) && procuraArray(id,postId,N)==0){
				id[k] = postId; k++;
			}
			else {
				long idP = post_getparentId(com,procuraData(com,data),postId);
				if(procuraArray(ID,idP,c)!=0 && procuraArray(id,idP,N)==0){
					id[k] = idP ;
					k++;
				 }
			}
		}
		com->hashUser[chave2]->top10=h3;com->hashUser[chave1]->top10=h4;free(ID);
	}
	else{
		int c = h1->used,j;
		int a = h2->used;
		HeapPosts h3 = initHeapPosts(c);
		HeapPosts h4 = initHeapPosts(a);
		long* ID = malloc(c*sizeof(long));
		procuraId(h1,com,ID,h3);
		for(j=0;j<a && k<N;j++){
			Date data = h2->array[0].data;
			long postId = extractMaxPosts2(h2,h4);
			if(post_getPostTypeId(com,procuraData(com,data),postId)==1 && procuraArray(ID,postId,c)!=0 && procuraArray(id,postId,N)==0){
				id[k] = postId; 
				k++;
			}
			else {
				long idP = post_getparentId(com,procuraData(com,data),postId);
				if(procuraArray(ID,idP,c)!=0  && procuraArray(id,idP,N)==0){
					id[k] = idP ;
					k++;
				 }
			}
		}
		com->hashUser[chave1]->top10=h3;
	    com->hashUser[chave2]->top10=h4;free(ID);
	}
	return k;
}

/**
 * [Inicialização da Heap]
 * @param  size      [Tamanho da heap]
 * @return           [Heap]
 */
static Heap initHeap(int size){
    Heap h = malloc(sizeof(struct heap));
    if(h != NULL) {
        h->size = size;
        h->used = 0;
        h->array=malloc(size*sizeof(struct elemento));
    }
    return h;
}

/**
 * [Faz o swap de dois elementos da heap]
 * @param h       [Heap]
 * @param a       [Elemento para trocar de posição com b]
 * @param b       [Elemento para trocar de posição com a]
 */
static void swap(Heap h, int a, int b){
    elem t = h->array[a];
    h->array[a] = h->array[b];
    h->array[b] = t;
}

/**
 * [Função que após inserção de um elemento na Heap, coloca esse elemento na posição correta]
 * @param h       [Heap]
 * @param i       [Quantos elementos existem na heap]
 */
static void bubbleUp(Heap h, int i){
    while (i!=0 && h->array[i].count > h->array[PARENT(i)].count) {
        swap(h, i, PARENT(i));
        i = PARENT(i);
    }
}

/** 
 * [Função que após remoção de um elemento na Heap, mantém o invariante que os pai é sempre maior que os filhos]
 * @param h       [Heap]
 * @param N       [Número de elementos na heap]
*/
static void bubbleDown(Heap h, int N){
    int i = 0, max ;
    while (RIGHT(i) < N && h->array[max = h->array[LEFT(i)].count > h->array[RIGHT(i)].count ? LEFT(i) : RIGHT(i)].count > h->array[i].count) {
        swap(h, i, max);
        i = max;
    }
    if (LEFT(i) < N && h->array[LEFT(i)].count > h->array[i].count)
        swap(h, i, LEFT(i));
}

/** 
 * [Insire um elemento (id e count) na Heap mantendo o invariante que o pai é sempre maior que os filhos]
 * @param h        [Heap onde queremos inserir o elemento]
 * @param count    [Paramentro a inserir]
 * @param id       [Id relacionado com o count que queremos inserir]
 * @return         [Caso de sucesso] 
 */
static int insertHeap(Heap h,int count,long id){
    if (h->used == h->size) {
        h->array= realloc(h->array, 2*(h->size)*sizeof(struct elemento));
        h->size *= 2;
    }
    assert( h!= NULL);
    h->array[h->used].count= count;
    h->array[h->used].id= id;
    (h->used)++;
    bubbleUp(h, h->used-1);
    return 1;
}

/**
 * [Remover a cabeça da heap(o maior elemento) mantendo o invariante que o pai é sempre maior que os filhos]
 * @param h       [Heap]
 * @return        [O id do maior elemento da heap] 
 */
static long extractMax(Heap h){
    if (h->used > 0) {
        elem novo= h->array[0];
        long res=novo.id;
       
        h->array[0] = h->array[h->used-1];
        (h->used)--;
        bubbleDown(h, h->used);
        return res;
    } 
    else return -1;
}

/** 
 * [Inicializa a heap e insere os utilizadores]
 * @param com   [Estrutura]
 */
void insere_Heap(TAD_community com){
    int i,tam=com->usersSize/2;
    com->Top=initHeap(tam);
    for(i=0;i<com->usersSize;i++){
  		if(com->hashUser[i]!=NULL && com->hashUser[i]->nPosts!=0)
   		 	insertHeap((com->Top),com->hashUser[i]->nPosts,com->hashUser[i]->ownerUserId);
    }
}

/** 
 * [Insere na heap da posição da hashUser de um determinado utilizador]
 * @param com             [Estrutura]
 * @param ownerUserId     [Id do utilizador]
 * @param id              [Id do post]
 * @param data            [Data de criação do post]
 */
void insere_Heap_Posts(TAD_community com,long ownerUserId, long id, Date data){
	int i = procuraUser(com, ownerUserId);
	insertHeapPosts(com->hashUser[i]->top10,data,id);
}

/**
 * [Devolve o valor de Hash correspondente ao id de uma tag]
 * @param i   	   [Id]
 * @param size     [Tamanho da HashTableQuery7]
 * @return     	   [Valor de Hash]
*/
int q7Hash (long i, int size){
	if (i < 0) return (-(i % size));
	else return (i % size);
}

/**
 * [Devolve a posição da HashTableQuery7 onde se encontra um dado post]
 * @param com        [Estrutura]
 * @param id         [Id do post a procurar] 
 * @param chave      [Valor de hash]
 * @param h          [HashTableQuery7]  
 * @param size       [Tamanho da HashTableQuery7] 
 * @return           [Posição da HashTableQuery7]
 */
static int procuraQ7 (TAD_community com, long id,int chave,HashTableQuery7 h, int size){
	int i,c=0;
	for (i=chave; existeQ7(h,i) && c<size && get_id_Q7(h,i)!=id; i++){
		if (i+1 == size) i=0;
		c++;
	}
	if (existeQ7(h,i) && get_id_Q7(h,i)==id) return i;
	else return -1;
}

/**
 * [Insere na HashTableQuery7 os ids dos posts tipo pergunta e o número de respostas de cada]
 * @param a          [Árvore dos posts] 
 * @param com        [Estrutura]
 * @param h          [HashTableQuery7]  
 * @param size       [Tamanho da HashTableQuery7] 
 */
static void retornaAIdR (Post* a,TAD_community com,HashTableQuery7 h,int size){
	int chave,local;
	if (a!=NULL){
		if (a->postTypeId==1){
			chave = q7Hash(a->id,size);
			local = procuraQ7(com,a->id,chave,h,size);
			if(local==-1){
				while (existeQ7(h,chave)){
					if (chave+1==size) chave=0;
					else chave++;
				}
			insereTQ7(h,chave,1,0,a->id);
			}
			else set_flag_Q7(h,1,local);
		}
		if(a->postTypeId==2){
			chave = q7Hash(a->parentId,size);
			local = procuraQ7(com,a->parentId,chave,h,size);
			if(local==-1){
				while (existeQ7(h,chave)){
					if (chave+1==size) chave=0;
					else chave++;
				}
			insereTQ7(h,chave,0,1,a->parentId);
			}
			else set_contador_Q7(h,get_contador_Q7(h,local)+1,local);
		}
	retornaAIdR (a->esq,com,h,size);
	retornaAIdR (a->dir,com,h,size);
	}
}

/**
 * [Função que acede à árvore dos posts pretendida]
 * @param com        [Estrutura]
 * @param i          [Posição da treeHash]
 * @param h          [HashTableQuery7]  
 * @param size       [Tamanho da HashTableQuery7] 
 */
void retornaAId (TAD_community com,int i,HashTableQuery7 h,int size){
	Post* a = com->treeHash[i]->tree;
	retornaAIdR (a, com, h,size);
}

/** 
 * [Liberta uma heapPosts]
 *  @param r   [HeapPosts]
 */
static void freeHeapPosts(HeapPosts r){
    if(r != NULL) {
        free(r->array);
        free(r);
    }
}

/** 
 * [Liberta uma heap]
 * @param r     [Heap]
 */
static void freeHeap(Heap r){
	if(r!=NULL){
		free(r->array);
		free(r);
	}
}

/** 
 * [Devolve os ids das N perguntas com mais respostas]
 * @param com        [Estrutura]
 * @param N          [N pedido no top N]
 * @param h          [HashTableQuery7]
 * @param size       [Tamanho da HashTableQuery7] 
 * @return           [Lista com os ids das N perguntas]
 */
LONG_list carregaListaQ(TAD_community com,int N,HashTableQuery7 h,int size){
	Heap tag;
	tag = NULL;
	tag = initHeap(size);
	for(int i=0;i<size;i++)
			if(existeQ7(h,i) && get_flag_Q7(h,i)!=0) insertHeap(tag,get_contador_Q7(h,i),get_id_Q7(h,i));
	if(tag->used<N) N=tag->used;
	LONG_list l=create_list(N);
	for(int k=0;k<N;k++)
		set_list(l, k, extractMax(tag)); 
	freeHeap(tag);
    return l;
}

/** 
 * [Devolve os ids dos posts com uma determinada tag por cronologia inversa]
 * @param com     [Estrutura]
 * @param id      [Array com os ids dos posts]
 * @param d       [Array com as datas dos posts]
 * @return        [Lista com os ids dos posts ordenada por cronologia inversa]
 */
LONG_list carregaListaT(TAD_community com,long* id,Date* d){
	HeapPosts tag;
	int size=com->dataSize/2,i;
	tag = NULL;
	tag = initHeapPosts(size);
	for(i=0;i<size && id[i]!=-2;i++){
			 insertHeapPosts(tag,d[i],id[i]);}
	LONG_list l=create_list(i);
	for(int k=0;k<i;k++)
		set_list(l, k, extractMaxPosts(tag)); 
	freeHeapPosts(tag);
    return l;
}

/** 
 * [Devolve os ids das tags mais usadas pelos N utilizadores com melhor reputação]
 * @param com     [Estrutura]
 * @param N       [N pedido no top N]
 * @param h       [HashTableQuery11]
 * @param size    [Tamanho da HashTableQuery11]
 * @return        [Lista com os ids das N tags mais usadas]
 */
LONG_list carregaListaTag(TAD_community com,int N,HashTableQuery11 h,int size){
	Heap tag;
	tag = NULL;
	tag = initHeap(size);
	for(int i=0;i<size;i++)
			if(existeQ11(h,i)) insertHeap(tag, get_contador(h,i), get_id(h,i));
	if(tag->used<N) N=tag->used;
	LONG_list l=create_list(N);
	for(int k=0;k<N;k++)
		set_list(l, k, extractMax(tag)); 
	freeHeap(tag);
    return l;
}

/** 
 * [Retorna o array com os id dos últimos 10 posts]
 * @param com         [Estrutura]
 * @param i           [Posição da hashUser]
 * @return            [O array com os id]
 */
long* retornaTop10(TAD_community com, int i){
	long* id = malloc(10*sizeof(long));
	int c=com->hashUser[i]->top10->used,j;
	HeapPosts b = com->hashUser[i]->top10;
	HeapPosts h=initHeapPosts(c);
	for(j=0;j<10 && j<c;j++){
		id[j] = extractMaxPosts2(com->hashUser[i]->top10,h);
	}
	for(int k=j;k<c;k++)
		extractMaxPosts2(com->hashUser[i]->top10,h);
	com->hashUser[i]->top10=h;
	freeHeapPosts(b);
	return id;
}

/** 
 * [Devolve a lista com os ids dos top N utilizadores com maior número de posts de sempre]
 * @param com          [Estrutura]
 * @param N            [Número de ids pedidos]
 * @param nOrdenados   [Número de posições do array ocupadas]
 * @return             [Lista com os ids dos N utilizadores com maior número de posts]
*/
LONG_list contaPosts(TAD_community com, int N, int nOrdenados){
	int b = com->Top->used;
	if(N>0){
		int a=nOrdenados;
		for(int h=0; h<N && h<b; h++){
	    	com->topN[a] = extractMax(com->Top);
	    	a++;
		}
	}
	LONG_list list = create_list(N+nOrdenados);
	if(N>b) N = b;
	for (int i=0; i<N+nOrdenados; i++){
		set_list(list, i, com->topN[i]); 
	}
	return list;
}

/** 
 * [Obtém as heaps dos utilizadores pretendidos para verificar os posts em que ambos participam]
 * @param com         [Estrutura]
 * @param chave1      [Posição de um utilizador hashUser]
 * @param chave2      [Posição de um utilizador hashUser]
 * @param N           [Tamanho do array com os ids]
 * @param id          [Array com os ids]
 * @return            [O número de posts em que ambos participam]
 */
int extraiHeaps(TAD_community com,int chave1,int chave2,int N,long* id){
	int a = 0;
	HeapPosts h1 = com->hashUser[chave1]->top10; 
	HeapPosts h2 = com->hashUser[chave2]->top10;
	if (h1!=NULL && h2!=NULL){
		a = extraiId(h1,h2,N,id,com,chave1,chave2);
		freeHeapPosts(h1);freeHeapPosts(h2);
	}
	return a;
}

/** 
 * [Liberta o array topN e o array topNR]
 * @param com     [Estrutura]
 */
void freeTopN(TAD_community com){
	free(com->topN);
	free(com->topNR);
}

/** 
 * [Devolve o valor de Hash correspondente a um determinado id]
 * @param i    [Id]
 * @param N    [Tamanho da HashTableTopN]
 * @return     [Valor de Hash]
 */
int topNHash (long i, int N){
	if (i < 0) return (-(i % N));
	else return (i % (N));
}

/** 
 * [Verifica se um utilizador pertence ao top N]
 * @param com           [Estrutura]
 * @param ownerUserId   [Id do utilizador a verificar]
 * @param N             [N pedido no top N] 
 * @param h             [HashTableTopN]
 * @return              [Booleano de comparação]
 */
int pertenceU (TAD_community com, long ownerUserId, int N, HashTableTopN h){
	int i, tam=N*2,chave = topNHash(ownerUserId,tam),c=0;
	for (i=chave; c<tam && existeHashTopN(h,i)==1 &&  get_id_HashTopN(h,i)!=ownerUserId; i++){
		if (i+1==tam) i=0;
		c++;
	}
	if (existeHashTopN(h,i) && get_id_HashTopN(h,i)==ownerUserId) return 1;
	return -1;
}

/**
 * [Devolve a posição da HashTableQuery11 onde se encontra uma dada tag]
 * @param  com        [Estrutura]
 * @param  chave      [Valor de hash]
 * @param  tag        [Tag a procurar]
 * @param  h          [HashTableQuery11]  
 * @param  size       [Tamanho da HashTableQuery11]   
 * @return            [Posição da HashTableQuery11]
 */
static int procuraQ11(TAD_community com,int chave,char* tag,HashTableQuery11 h, int size){
  int i,c=0;
  for(i=chave;existeQ11(h,i) && c<size && strcmp(get_tag(h,i),tag);i++){
    if (i+1 == size) i=0;
    c++;
  }
  if(existeQ11(h,i) && !strcmp(get_tag(h,i),tag)) return i;
  return -1;
}

/**
 * [Procura uma tag na hashTag]
 * @param  com       [Estrutura]
 * @param  chave     [Valor da hash]
 * @param  tag       [Tag a procurar]
 * @return           [Posição da hash]
 */
int procuraTag(TAD_community com,int chave,char* tag){
	int i,c=0;
	for(i=chave;com->hashTag[i]!=NULL && c<com->tagsSize && strcmp(com->hashTag[i]->tagName,tag);i++){
		if (i+1==com->tagsSize) i=0;
		c++;
	}
	if(com->hashTag[i]!=NULL && !strcmp(com->hashTag[i]->tagName,tag)) return i;
	return -1;
}

/** 
 * [Determina a posição da hashTag onde se encontra uma tag, fazendo a sua insersão]
 * @param com             [Estrutura]
 * @param tag             [Tag]
 * @param h               [HashTableQuery11]
 * @param size            [Tamanho da HashTableQuery11] 
 */
void buscaId (TAD_community com, char* tag, HashTableQuery11 h, int size){
	int chave = tagHash(tag, com),local = procuraQ11(com,chave,tag,h,size);
	if(local==-1){
		while(existeQ11(h,chave)){
			if(chave+1==size) chave=0;
			else chave++;
		}
		int idTag = procuraTag(com,chave,tag);
		if(idTag!=-1) insereTQuery11(h,chave,tag,1,com->hashTag[idTag]->id);
	}
	else set_contador(h,get_contador(h,local)+1,local);
}

/** 
 * [Verifica se uma tag está presente num conjunto de tags e caso esteja insere na HashTableQuery11]
 * @param com             [Estrutura]
 * @param s               [Tag]
 * @param h               [HashTableQuery11]
 * @param size            [Tamanho da HashTableQuery11] 
 */
int buscaTag(TAD_community com, char *s, HashTableQuery11 h, int size){
  int a=0,i=0,k=0,j; 
  char *tag=malloc(strlen(s)*sizeof(char));
  while(s[k]){
    i=k;
    while(s[i] && s[i]=='<') i++;
    for(j=i,a=0;s[j] && s[j]!='>';j++,a++){
        tag[a]=s[j];
    }
    tag[a]=0; 
      buscaId(com,tag,h,size);
      if(s[j] && s[j]=='>') {j++;}
      k=j;
  }
  free(tag);
  return 0;
}

/** 
 * [Para todos os nodos de uma árvore verifica se o criador desse post está no topR para inserir as tags usadas na HashTableQuery11]
 * @param com             [Estrutura]
 * @param a               [Árvore dos posts]
 * @param N               [Número de ids pedidos no top N]
 * @param h               [HashTableQuery11] 
 * @param h1              [HashTableTopN]  
 * @param size            [Tamanho da HashTableQuery11] 
 */
static void retornaTIdR (TAD_community com, Post* a, int N,HashTableQuery11 h,HashTableTopN h1,int size){
	if (a!=NULL){
		if (a->tag!=NULL && pertenceU(com,a->ownerUserId,N,h1)==1)
			buscaTag(com,a->tag,h,size);
		retornaTIdR (com,a->esq,N,h,h1,size);
		retornaTIdR (com,a->dir,N,h,h1,size);
	}
}

/** 
 * [Preenche o array topNR com os N utilizadores com melhor reputação]
 * @param com             [Estrutura]
 * @param tam             [Número de ids que falta preencher no topNR]
 * @param z               [Número de ids inseridos no topNR]
 * @param N               [Número de ids pedidos no top N]
 */
void preencheTopNR (TAD_community com, int tam, int z, int N){
	int b = com->TopR->used;
	if (tam>0){
		for (int k=0; k<tam && k<b; k++){
			com->topNR[z] = extractMax(com->TopR);
			z++;
		}
	}
	else{
		for (int k=0; k<N && k<b; k++){
			com->topNR[z] = extractMax(com->TopR);
			z++;
		}
	}
}

/** 
 * [Função que insere na HashTableTopN o id dos N melhores utilizdores]
 * @param com       [Estrutura]
 * @param N         [N pedido no top N]
 * @param h         [HashTableTopN]
 * @return          [HashTableTopN]
 */
HashTableTopN transfere(TAD_community com, int N, HashTableTopN h){
	int chave, tam = N*2;
	for(int i=0;i<N;i++){
		chave = topNHash(com->topNR[i],tam);
		while (existeHashTopN(h,chave)){
			if (chave+1 == tam) chave=0;
			else chave++;
		}
		insereHashTopN(h,chave,com->topNR[i]);
	}
	return h;
}

/** 
 * [Função que acede à árvore dos posts pretendida]
 * @param com             [Estrutura]
 * @param i               [Posição da treeHash onde se encontra a árvore]
 * @param N               [Número de ids pedidos no top N]
 * @param h               [HashTableQuery11]
 * @param h1              [HashTableTopN]
 * @param size            [Tamanho da HashTableQuery11]
 */
void retornaTId(TAD_community com, int i, int N, HashTableQuery11 h,HashTableTopN h1,int size){
	Post* a = com->treeHash[i]->tree;
	retornaTIdR (com,a,N,h,h1,size);
}

/** 
 * [Inicializa a TopR de modo a inserir os ids e a reputação dos utilizadores]
 * @param com     [Estrutura]
 */
void insere_Heap_Reputation(TAD_community com){
    int i,tam=com->usersSize/2;
    com->TopR=initHeap(tam);
    for(i=0;i<com->usersSize;i++){
  		if(com->hashUser[i]!=NULL && com->hashUser[i]->nPosts!=0)
   		 	insertHeap((com->TopR),com->hashUser[i]->reputation,com->hashUser[i]->ownerUserId);
    }
}

/** 
 * [Liberta a heap Top e TopR]
 * @param com     [Estrutura]
 */
void freeTop(TAD_community com){
	freeHeap(com->Top);
	freeHeap(com->TopR);
}

/** 
 * [Liberta a hashUser]
 * @param com     [Estrutura]
 * @param size    [Tamanho da hashUser]
 */
void freeHashTableUsers  (TAD_community com, int size){
	int i;
	Users *cur;
	for (i=0; i<size; i++){
		if (com->hashUser[i]!=NULL){
		cur = com->hashUser[i];
		free(cur->displayName);
		free(cur->aboutMe);
		freeHeapPosts(cur->top10);
		free(cur);}
	}	
	free(com->hashUser);
}

/** [Liberta a HashTag]
 * @param com     [Estrutura]
 * @param size    [Tamanho da hashTag]
 */
void freeHashTableTags (TAD_community com, int size){
	int i;
	Tags *cur;
	for (i=0; i<size; i++){
		if (com->hashTag[i]!=NULL){
			cur = com->hashTag[i];
			free(cur->tagName);
			free(cur);
		}
	}	
	free(com->hashTag);
}

/** 
 * [Liberta um post]
 * @param p2     [Árvore dos posts]
 */
static void freeP(Post* p2){
	if(p2!=NULL){
		free(p2->title);
		free(p2->tag);
		free_date(p2->creationDate);
		freeP((p2->esq));
		freeP((p2->dir));
		free(p2);
	}
}

/** 
 * [Liberta a treeHash]
 * @param com     [Estrutura]
 * @param size    [Tamanho da treeHash]
 */
void freeTreeHashData (TAD_community com,int size){
	int i;
	TreeHash *cur, *prev;
	for(i=0;i<size;i++){
		if(com->treeHash[i]!=NULL){
			cur = com->treeHash[i];
			prev = cur;
			Post *a = prev->tree;
			if(a!=NULL){
				Post* a2 = a;
				freeP(a2);		
			}
			free(prev);
		}
	}
	free(com->treeHash);
}
